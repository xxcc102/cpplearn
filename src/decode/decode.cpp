#include "decode.h"
//gtime_t dc_time = { 0 };


int glonass_freq_num[NSATGLO] = { //glonass∆µµ¿∫≈
	1,-4, 5, 6, 1,  -4, 5, 6,-2,-7,
	0,-1,-2,-7, 0,  -1, 4,-3, 3, 2,
	4,-3, 3, 2,-5,  -5,-5 };


/* msm signal id table -------------------------------------------------------*/
const char *msm_sig_gps[32] = {
	/* GPS: ref [13] table 3.5-87, ref [14][15] table 3.5-91 */
	""  ,"1C","1P","1W","1Y","1M",""  ,"2C","2P","2W","2Y","2M", /*  1-12 */
	""  ,""  ,"2S","2L","2X",""  ,""  ,""  ,""  ,"5I","5Q","5X", /* 13-24 */
	""  ,""  ,""  ,""  ,""  ,"1S","1L","1X"                      /* 25-32 */
};
const char *msm_sig_glo[32] = {
	/* GLONASS: ref [13] table 3.5-93, ref [14][15] table 3.5-97 */
	""  ,"1C","1P",""  ,""  ,""  ,""  ,"2C","2P",""  ,"3I","3Q",
	"3X",""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,
	""  ,""  ,""  ,""  ,""  ,""  ,""  ,""
};
const char *msm_sig_gal[32] = {
	/* Galileo: ref [15] table 3.5-100 */
	""  ,"1C","1A","1B","1X","1Z",""  ,"6C","6A","6B","6X","6Z",
	""  ,"7I","7Q","7X",""  ,"8I","8Q","8X",""  ,"5I","5Q","5X",
	""  ,""  ,""  ,""  ,""  ,""  ,""  ,""
};
const char *msm_sig_qzs[32] = {
	/* QZSS: ref [15] table 3.5-103 */
	""  ,"1C",""  ,""  ,""  ,""  ,""  ,""  ,"6S","6L","6X",""  ,
	""  ,""  ,"2S","2L","2X",""  ,""  ,""  ,""  ,"5I","5Q","5X",
	""  ,""  ,""  ,""  ,""  ,"1S","1L","1X"
};
const char *msm_sig_sbs[32] = {
	/* SBAS: ref [13] table 3.5-T+005 */
	""  ,"1C",""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,
	""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,"5I","5Q","5X",
	""  ,""  ,""  ,""  ,""  ,""  ,""  ,""
};
const char *msm_sig_cmp[32] = {
	/* BeiDou: ref [15] table 3.5-106 */
	""  ,"1I","1Q","1X",""  ,""  ,""  ,"6I","6Q","6X",""  ,""  ,
	""  ,"7I","7Q","7X",""  ,""  ,""  ,""  ,""  ,""  ,""  ,""  ,
	""  ,""  ,""  ,""  ,""  ,""  ,""  ,""
};

//
//unsigned int getbitu(const unsigned char *buff, int pos, int len)
//{
//	unsigned int bits = 0;
//	int i;
//	for (i = pos; i < pos + len; i++) bits = (bits << 1) + ((buff[i / 8] >> (7 - i % 8)) & 1u);
//	return bits;
//}
//
//

int initnav(nav_t *nav)
{
	/* reallocate memory for observation and ephemris buffer */
	if (!(nav->eph = (eph_t  *)malloc(sizeof(eph_t)*MAXSAT)) ||
		!(nav->geph = (geph_t *)malloc(sizeof(geph_t)*MAXPRNGLO))) {
		free(nav->eph);
		free(nav->geph);
		return 0;
	}
	nav->n = nav->nmax = MAXSAT;

	return 1;
}

unsigned int calCrc24(const unsigned char *buff, long long len)
{
	unsigned int crc = 0;
	int i;

	for (i = 0; i < len; i++)
		crc = ((crc << 8) & 0xffffff) ^ kTableCrc24[(crc >> 16) ^ (unsigned char)buff[i]];
	return crc;
}

/* adjust daily rollover of glonass time -------------------------------------*/
void adjday_glot(gtime_t *time, double tod)
{
	gtime_t timein;
	double tow, tod_p;
	int week;

	if (time->time == 0) 
		*time = utc2gpst(timeget());
	
timein = timeadd(gpst2utc(*time), 10800.0); /* glonass time */

	tow = time2gpst(timein, &week);
	tod_p = fmod(tow, 86400.0); tow -= tod_p;
	if (tod < tod_p - 43200.0) 
		tod += 86400.0;
	else if (tod > tod_p + 43200.0) 
		tod -= 86400.0;
	timein = gpst2time(week, tow + tod);
	*time = utc2gpst(timeadd(timein, -10800.0));
}

/* adjust weekly rollover of gps time ----------------------------------------*/
static void adjweek(gtime_t *time, double tow)
{
	double tow_p;
	int week;

	/* if no time, get cpu time */
	if (time->time == 0) 
		*time = utc2gpst(timeget());
	tow_p = time2gpst(*time, &week);

	if (tow < tow_p - 302400.0) 
		tow += 604800.0;
	else if (tow > tow_p + 302400.0) 
		tow -= 604800.0;
	*time = gpst2time(week, tow);
}



/* decode type msm message header --------------------------------------------*/
int decode_msm_head(const unsigned char *buff, int len, int sys, int *sync, int *iod,
	msm_h_t *h, int *hsize, MsmData *md)
{
	msm_h_t h0 = { 0 };
	double tow, tod;
	char *msg, tstr[64];
	int i = 24, j, dow, mask, staid, type, ncell = 0;

	type = getbitu(buff, i, 12); i += 12;

	*h = h0;
	if (i + 157 <= len * 8) {
		staid = getbitu(buff, i, 12);       i += 12;

		if (sys == SYS_GLO) {
			dow = getbitu(buff, i, 3);       i += 3;
			tod = getbitu(buff, i, 27)*0.001; i += 27;
			adjday_glot(&md->time, tod);
		}
		else if (sys == SYS_CMP) {
			tow = getbitu(buff, i, 30)*0.001; i += 30;
			tow += 14.0; /* BDT -> GPST */
			adjweek(&md->time, tow);
		}
		else {
			tow = getbitu(buff, i, 30)*0.001; i += 30;
			adjweek(&md->time, tow);
		}
		*sync = getbitu(buff, i, 1);       i += 1;
		*iod = getbitu(buff, i, 3);       i += 3;
		h->time_s = getbitu(buff, i, 7);       i += 7;
		h->clk_str = getbitu(buff, i, 2);       i += 2;
		h->clk_ext = getbitu(buff, i, 2);       i += 2;
		h->smooth = getbitu(buff, i, 1);       i += 1;
		h->tint_s = getbitu(buff, i, 3);       i += 3;
		for (j = 1; j <= 64; j++) {
			mask = getbitu(buff, i, 1); i += 1;
			if (mask) h->sats[h->nsat++] = j;
		}
		for (j = 1; j <= 32; j++) {
			mask = getbitu(buff, i, 1); i += 1;
			if (mask) h->sigs[h->nsig++] = j;
		}
	}
	else {
		return -1;
	}
	if (h->nsat*h->nsig > 64)
	{
		return -1;
	}
	
	if (i + h->nsat*h->nsig > len * 8) 
	{
		return -1;
	}
	
	for (j = 0; j < h->nsat*h->nsig; j++)
	{
		h->cellmask[j] = getbitu(buff, i, 1); i += 1;
		if (h->cellmask[j]) ncell++;
	}
	*hsize = i;

	return ncell;
}


/* get signal index ----------------------------------------------------------*/
static void sigindex(int sys, const unsigned char *code, const int *freq, int n, int *ind)
{
	int i, nex, pri, pri_h[8] = { 0 }, index[8] = { 0 }, ex[32] = { 0 };

	/* test code priority */
	for (i = 0; i < n; i++) {
		if (!code[i]) continue;

		if (freq[i] > NFREQ) { /* save as extended signal if freq > NFREQ */
			ex[i] = 1;
			continue;
		}
		/* code priority */
		pri = getcodepri(sys, code[i]);

		/* select highest priority signal */
		if (pri > pri_h[freq[i] - 1]) {
			if (index[freq[i] - 1]) ex[index[freq[i] - 1] - 1] = 1;
			pri_h[freq[i] - 1] = pri;
			index[freq[i] - 1] = i + 1;
		}
		else ex[i] = 1;
	}
	/* signal index in obs data */
	for (i = nex = 0; i < n; i++) {
		if (ex[i] == 0) ind[i] = freq[i] - 1;
		else if (nex < NEXOBS) ind[i] = NFREQ + nex++;
		else
		{ /* no space in obs data */
			ind[i] = -1;
		}
	}
}

/* get observation data index ------------------------------------------------*/
int obsindex(obs_t *obs, gtime_t time, int sat)
{
	int i, j;

	for (i = 0; i < obs->n; i++) {
		if (obs->data[i].sat == sat) return i; /* field already exists */
	}
	if (i >= MAXOBS) return -1; /* overflow */

	/* add new field */
	obs->data[i].time = time;
	obs->data[i].sat = sat;
	for (j = 0; j < NFREQ + NEXOBS; j++) {
		obs->data[i].L[j] = obs->data[i].P[j] = 0.0;
		obs->data[i].D[j] = 0.0;
		obs->data[i].SNR[j] = obs->data[i].LLI[j] = obs->data[i].code[j] = 0;
	}
	obs->n++;
	return i;
}

/* loss-of-lock indicator ----------------------------------------------------*/
int lossoflock(rtcm_t *rtcm, int sat, int freq, int lock)
{
	int lli = (!lock && !rtcm->lock[sat - 1][freq]) || lock < rtcm->lock[sat - 1][freq];
	rtcm->lock[sat - 1][freq] = (unsigned short)lock;
	return lli;
}


/* save obs data in msm message ----------------------------------------------*/
static void save_msm_obs(const unsigned char *buff, int sys, msm_h_t *h, MsmData *md, obs_t *obs)
{
	const char *sig[32];
	double tt, wl;
	unsigned char code[32];
	int i, j, k, type, prn, sat, fn, index = 0, freq[32], ind[32];

	type = getbitu(buff, 24, 12);


	/* id to signal */
	for (i = 0; i < h->nsig; i++) {
		switch (sys) {
		case SYS_GPS: sig[i] = msm_sig_gps[h->sigs[i] - 1]; break;
		case SYS_GLO: sig[i] = msm_sig_glo[h->sigs[i] - 1]; break;
		case SYS_GAL: sig[i] = msm_sig_gal[h->sigs[i] - 1]; break;
		case SYS_QZS: sig[i] = msm_sig_qzs[h->sigs[i] - 1]; break;
		case SYS_SBS: sig[i] = msm_sig_sbs[h->sigs[i] - 1]; break;
		case SYS_CMP: sig[i] = msm_sig_cmp[h->sigs[i] - 1]; break;
		default: sig[i] = ""; break;
		}
		/* signal to rinex obs type */
		code[i] = obs2code(sig[i], freq + i);

		/* freqency index for beidou and galileo */
		if (sys == SYS_CMP) {
			if (freq[i] == 5) freq[i] = 2; /* B2 */
			else if (freq[i] == 4) freq[i] = 3; /* B3 */
		}
		else if (sys == SYS_GAL) {
			if (freq[i] == 5) freq[i] = 2; /* E5b */
		}
	}

	/* get signal index */
	sigindex(sys, code, freq, h->nsig, ind);

	for (i = j = 0; i < h->nsat; i++) {

		prn = h->sats[i];
		if (sys == SYS_QZS) 
			prn += MINPRNQZS - 1;
		else if (sys == SYS_SBS) 
			prn += MINPRNSBS - 1;

		if ((sat = satno(sys, prn))) {
			tt = timediff(obs->data[0].time, md->time);
			if (md->obsflag || fabs(tt) > 1E-9) {
				obs->n = md->obsflag = 0;
			}
			index = obsindex(obs, md->time, sat);
		}
		else 
		{
			trace(2, "rtcm3 %d satellite error: prn=%d\n", type, prn);
		}


		for (k = 0; k < h->nsig; k++) {
			if (!h->cellmask[k + i * h->nsig]) 
				continue;

			if (sat&&index >= 0 && ind[k] >= 0) {

				/* satellite carrier wave length */
				wl = satwavelen(sat, freq[k] - 1, glonass_freq_num[sat - 1]);

				/* glonass wave length by extended info */
				if (sys == SYS_GLO && md->ex&&md->ex[i] <= 13) {
					fn = md->ex[i] - 7;
					wl = CLIGHT / ((freq[k] == 2 ? FREQ2_GLO : FREQ1_GLO) +
						(freq[k] == 2 ? DFRQ2_GLO : DFRQ1_GLO)*fn);
				}
				/* pseudorange (m) */
				if (md->r[i] != 0.0&&md->pr[j] > -1E12) 
				{
					obs->data[index].P[ind[k]] = md->r[i] + md->pr[j];
				}
				/* carrier-phase (cycle) */
				if (md->r[i] != 0.0&&md->cp[j] > -1E12&&wl > 0.0)
				{
					obs->data[index].L[ind[k]] = (md->r[i] + md->cp[j]) / wl;
				}
				/* doppler (hz) */
				if (md->rr&&md->rrf&&md->rrf[j] > -1E12&&wl > 0.0)
				{
					obs->data[index].D[ind[k]] = (float)(-(md->rr[i] + md->rrf[j]) / wl);
				}
				obs->data[index].LLI[ind[k]] = (md->lock[j] ? 0 : 1) + (md->half[j] ? 3 : 0);
				obs->data[index].SNR[ind[k]] = (unsigned char)(md->cnr[j] * 4.0);
				obs->data[index].code[ind[k]] = code[k];
			}
			j++;
		}
	}
}








///1046
/* decode type 1046: galileo I/NAV satellite ephemerides (ref [17]) ----------*/
int decode_type1046(const unsigned char *buff,const int len,nav_t *nav)
{
	eph_t eph = { 0 };
	double toc, sqrtA;
	char *msg;
	int i = 24 + 12, prn, sat, week, e5b_hs, e5b_dvs, e1_hs, e1_dvs, sys = SYS_GAL;

	if (i + 492 <= len * 8) {
		prn = getbitu(buff, i, 6);              i += 6;
		week = getbitu(buff, i, 12);              i += 12;
		eph.iode = getbitu(buff, i, 10);              i += 10;
		eph.sva = getbitu(buff, i, 8);              i += 8;
		eph.idot = getbits(buff, i, 14)*P2_43*SC2RAD; i += 14;
		toc = getbitu(buff, i, 14)*60.0;         i += 14;
		eph.f2 = getbits(buff, i, 6)*P2_59;        i += 6;
		eph.f1 = getbits(buff, i, 21)*P2_46;        i += 21;
		eph.f0 = getbits(buff, i, 31)*P2_34;        i += 31;
		eph.crs = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.deln = getbits(buff, i, 16)*P2_43*SC2RAD; i += 16;
		eph.M0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cuc = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.e = getbitu(buff, i, 32)*P2_33;        i += 32;
		eph.cus = getbits(buff, i, 16)*P2_29;        i += 16;
		sqrtA = getbitu(buff, i, 32)*P2_19;        i += 32;
		eph.toes = getbitu(buff, i, 14)*60.0;         i += 14;
		eph.cic = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.OMG0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cis = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.i0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.crc = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.omg = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.OMGd = getbits(buff, i, 24)*P2_43*SC2RAD; i += 24;
		eph.tgd[0] = getbits(buff, i, 10)*P2_32;        i += 10; /* E5a/E1 */
		eph.tgd[1] = getbits(buff, i, 10)*P2_32;        i += 10; /* E5b/E1 */
		e5b_hs = getbitu(buff, i, 2);              i += 2; /* E5b OSHS */
		e5b_dvs = getbitu(buff, i, 1);              i += 1; /* E5b OSDVS */
		e1_hs = getbitu(buff, i, 2);              i += 2; /* E1 OSHS */
		e1_dvs = getbitu(buff, i, 1);              i += 1; /* E1 OSDVS */
	}
	else {
		return -1;
	}

	if (!(sat = satno(sys, prn))) {
		return -1;
	}
	eph.sat = sat;
	eph.week = week + 1024; /* gal-week = gst-week + 1024 */
	eph.toe = gpst2time(eph.week, eph.toes);
	eph.toc = gpst2time(eph.week, toc);
	eph.ttr = eph.toe;
	eph.A = sqrtA * sqrtA;
	eph.svh = (e5b_hs << 7) + (e5b_dvs << 6) + (e1_hs << 1) + (e1_dvs << 0);
	eph.code = (1 << 0) | (1 << 9); /* data source = i/nav e1b + af0-2,toc,sisa for e5b-e1 */

	nav->eph[sat - 1] = eph;
	return 2;
}



///1019
/* decode type 1019: gps ephemerides -----------------------------------------*/
int decode_type1019(const unsigned char *buff, const int len, nav_t *nav)
{
	eph_t eph = { 0 };
	double toc, sqrtA;
	char *msg;
	int i = 24 + 12, prn, sat, week, sys = SYS_GPS;

	if (i + 476 <= len * 8) {
		prn = getbitu(buff, i, 6);              i += 6;
		week = getbitu(buff, i, 10);              i += 10;
		eph.sva = getbitu(buff, i, 4);              i += 4;
		eph.code = getbitu(buff, i, 2);              i += 2;
		eph.idot = getbits(buff, i, 14)*P2_43*SC2RAD; i += 14;
		eph.iode = getbitu(buff, i, 8);              i += 8;
		toc = getbitu(buff, i, 16)*16.0;         i += 16;
		eph.f2 = getbits(buff, i, 8)*P2_55;        i += 8;
		eph.f1 = getbits(buff, i, 16)*P2_43;        i += 16;
		eph.f0 = getbits(buff, i, 22)*P2_31;        i += 22;
		eph.iodc = getbitu(buff, i, 10);              i += 10;
		eph.crs = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.deln = getbits(buff, i, 16)*P2_43*SC2RAD; i += 16;
		eph.M0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cuc = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.e = getbitu(buff, i, 32)*P2_33;        i += 32;
		eph.cus = getbits(buff, i, 16)*P2_29;        i += 16;
		sqrtA = getbitu(buff, i, 32)*P2_19;        i += 32;
		eph.toes = getbitu(buff, i, 16)*16.0;         i += 16;
		eph.cic = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.OMG0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cis = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.i0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.crc = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.omg = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.OMGd = getbits(buff, i, 24)*P2_43*SC2RAD; i += 24;
		eph.tgd[0] = getbits(buff, i, 8)*P2_31;        i += 8;
		eph.svh = getbitu(buff, i, 6);              i += 6;
		eph.flag = getbitu(buff, i, 1);              i += 1;
		eph.fit = getbitu(buff, i, 1) ? 0.0 : 4.0; /* 0:4hr,1:>4hr */
	}
	else {
		return -1;
	}
	if (prn >= 40) {
		sys = SYS_SBS; prn += 80;
	}

	if (!(sat = satno(sys, prn))) {
		return -1;
	}
	eph.sat = sat;
	eph.week = adjgpsweek(week);
	eph.toe = gpst2time(eph.week, eph.toes);
	eph.toc = gpst2time(eph.week, toc);
	eph.ttr = eph.toe;
	eph.A = sqrtA * sqrtA;
	nav->eph[sat - 1] = eph;
	
	return 2;
}

///1044
/* decode type 1044: qzss ephemerides (ref [15]) -----------------------------*/
int decode_type1044(const unsigned char *buff, const int len, nav_t *nav)
{
	eph_t eph = { 0 };
	double toc, sqrtA;
	char *msg;
	int i = 24 + 12, prn, sat, week, sys = SYS_QZS;

	if (i + 473 <= len * 8) {
		prn = getbitu(buff, i, 4) + 192;          i += 4;
		toc = getbitu(buff, i, 16)*16.0;         i += 16;
		eph.f2 = getbits(buff, i, 8)*P2_55;        i += 8;
		eph.f1 = getbits(buff, i, 16)*P2_43;        i += 16;
		eph.f0 = getbits(buff, i, 22)*P2_31;        i += 22;
		eph.iode = getbitu(buff, i, 8);              i += 8;
		eph.crs = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.deln = getbits(buff, i, 16)*P2_43*SC2RAD; i += 16;
		eph.M0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cuc = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.e = getbitu(buff, i, 32)*P2_33;        i += 32;
		eph.cus = getbits(buff, i, 16)*P2_29;        i += 16;
		sqrtA = getbitu(buff, i, 32)*P2_19;        i += 32;
		eph.toes = getbitu(buff, i, 16)*16.0;         i += 16;
		eph.cic = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.OMG0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cis = getbits(buff, i, 16)*P2_29;        i += 16;
		eph.i0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.crc = getbits(buff, i, 16)*P2_5;         i += 16;
		eph.omg = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.OMGd = getbits(buff, i, 24)*P2_43*SC2RAD; i += 24;
		eph.idot = getbits(buff, i, 14)*P2_43*SC2RAD; i += 14;
		eph.code = getbitu(buff, i, 2);              i += 2;
		week = getbitu(buff, i, 10);              i += 10;
		eph.sva = getbitu(buff, i, 4);              i += 4;
		eph.svh = getbitu(buff, i, 6);              i += 6;
		eph.tgd[0] = getbits(buff, i, 8)*P2_31;        i += 8;
		eph.iodc = getbitu(buff, i, 10);              i += 10;
		eph.fit = getbitu(buff, i, 1) ? 0.0 : 2.0; /* 0:2hr,1:>2hr */
	}
	else 
	{
		return -1;
	}

	if (!(sat = satno(sys, prn))) 
	{
		return -1;
	}
	eph.sat = sat;
	eph.week = adjgpsweek(week);
	eph.toe = gpst2time(eph.week, eph.toes);
	eph.toc = gpst2time(eph.week, toc);
	eph.ttr = eph.toe;
	eph.A = sqrtA * sqrtA;

	nav->eph[sat - 1] = eph;

	return 2;
}


/* adjust weekly rollover of bdt time ----------------------------------------*/
static int adjbdtweek(int week)
{
	int w;
	(void)time2bdt(gpst2bdt(utc2gpst(timeget())), &w);
	if (w < 1) w = 1; /* use 2006/1/1 if time is earlier than 2006/1/1 */
	return week + (w - week + 512) / 1024 * 1024;
}

/* decode type 1042/63: beidou ephemerides -----------------------------------*/
int decode_type1042(const unsigned char *buff, const int len, nav_t *nav)
{
	eph_t eph = { 0 };
	double toc, sqrtA;
	char *msg;
	int i = 24 + 12, prn, sat, week, sys = SYS_CMP;

	if (i + 499 <= len * 8) {
		prn = getbitu(buff, i, 6);              i += 6;
		week = getbitu(buff, i, 13);              i += 13;
		eph.sva = getbitu(buff, i, 4);              i += 4;
		eph.idot = getbits(buff, i, 14)*P2_43*SC2RAD; i += 14;
		eph.iode = getbitu(buff, i, 5);              i += 5; /* AODE */
		toc = getbitu(buff, i, 17)*8.0;          i += 17;
		eph.f2 = getbits(buff, i, 11)*P2_66;        i += 11;
		eph.f1 = getbits(buff, i, 22)*P2_50;        i += 22;
		eph.f0 = getbits(buff, i, 24)*P2_33;        i += 24;
		eph.iodc = getbitu(buff, i, 5);              i += 5; /* AODC */
		eph.crs = getbits(buff, i, 18)*P2_6;         i += 18;
		eph.deln = getbits(buff, i, 16)*P2_43*SC2RAD; i += 16;
		eph.M0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cuc = getbits(buff, i, 18)*P2_31;        i += 18;
		eph.e = getbitu(buff, i, 32)*P2_33;        i += 32;
		eph.cus = getbits(buff, i, 18)*P2_31;        i += 18;
		sqrtA = getbitu(buff, i, 32)*P2_19;        i += 32;
		eph.toes = getbitu(buff, i, 17)*8.0;          i += 17;
		eph.cic = getbits(buff, i, 18)*P2_31;        i += 18;
		eph.OMG0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.cis = getbits(buff, i, 18)*P2_31;        i += 18;
		eph.i0 = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.crc = getbits(buff, i, 18)*P2_6;         i += 18;
		eph.omg = getbits(buff, i, 32)*P2_31*SC2RAD; i += 32;
		eph.OMGd = getbits(buff, i, 24)*P2_43*SC2RAD; i += 24;
		eph.tgd[0] = getbits(buff, i, 10)*1E-10;        i += 10;
		eph.tgd[1] = getbits(buff, i, 10)*1E-10;        i += 10;
		eph.svh = getbitu(buff, i, 1);              i += 1;
	}
	else {
		return -1;
	}
	trace(4, "decode_type1042: prn=%d iode=%d toe=%.0f\n", prn, eph.iode, eph.toes);

	if (!(sat = satno(sys, prn))) {
		trace(2, "rtcm3 1042 satellite number error: prn=%d\n", prn);
		return -1;
	}
	eph.sat = sat;
	eph.week = adjbdtweek(week);
	eph.toe = bdt2gpst(bdt2time(eph.week, eph.toes)); /* bdt -> gpst */
	eph.toc = bdt2gpst(bdt2time(eph.week, toc));      /* bdt -> gpst */
	eph.ttr = eph.toe;
	eph.A = sqrtA * sqrtA;

	nav->eph[sat - 1] = eph;
	return 2;
}


/* decode msm 4: full pseudorange and phaserange plus cnr --------------------*/
int decode_msm4(const unsigned char *buff, int len, int type, int sys, obs_t *obs)
{
	msm_h_t h = { 0 };
	MsmData md = { 0 };
	//double r[64], pr[64], cp[64], cnr[64];
	int i, j, sync, iod, ncell, rng, rng_m, prv, cpv/*, lock[64], half[64]*/;

	//type = getbitu(buff, 24, 12);

	/* decode msm header */
	if ((ncell = decode_msm_head(buff, len, sys, &sync, &iod, &h, &i,&md)) < 0) return -1;

	if (i + h.nsat * 18 + ncell * 48 > len * 8) {
		return -1;
	}
	for (j = 0; j < h.nsat; j++) md.r[j] = 0.0;
	for (j = 0; j < ncell; j++) md.pr[j] = md.cp[j] = -1E16;

	/* decode satellite data */
	for (j = 0; j < h.nsat; j++) { /* range */
		rng = getbitu(buff, i, 8); i += 8;
		if (rng != 255)
			md.r[j] = rng * RANGE_MS;
	}
	for (j = 0; j < h.nsat; j++) {
		rng_m = getbitu(buff, i, 10); i += 10;
		if (md.r[j] != 0.0)
			md.r[j] += rng_m * P2_10*RANGE_MS;
	}
	/* decode signal data */
	for (j = 0; j < ncell; j++) { /* pseudorange */
		prv = getbits(buff, i, 15); i += 15;
		if (prv != -16384) md.pr[j] = prv * P2_24*RANGE_MS;
	}
	for (j = 0; j < ncell; j++) { /* phaserange */
		cpv = getbits(buff, i, 22); i += 22;
		if (cpv != -2097152) md.cp[j] = cpv * P2_29*RANGE_MS;
	}
	for (j = 0; j < ncell; j++) { /* lock time */
		md.lock[j] = getbitu(buff, i, 4); i += 4;
	}
	for (j = 0; j < ncell; j++) { /* half-cycle ambiguity */
		md.half[j] = getbitu(buff, i, 1); i += 1;
	}
	for (j = 0; j < ncell; j++) { /* cnr */
		md.cnr[j] = getbitu(buff, i, 6)*1.0; i += 6;
	}
	/* save obs data in msm message */
	save_msm_obs(buff, sys, &h, &md, obs);

	//rtcm->obsflag = !sync;
	return sync ? 0 : 1;
}



/* decode msm 7: full pseudorange, phaserange, phaserangerate and cnr (h-res) */
int decode_msm7(const unsigned char *buff, int len, int sys, obs_t *obs)
{
	msm_h_t h = { 0 };
	MsmData md = { 0 };
	int i, type, j, sync, iod, ncell, rng, rng_m, rate, prv, cpv, rrv;

	type = getbitu(buff, 24, 12);

	/* decode msm header */
	if ((ncell = decode_msm_head(buff, len, sys, &sync, &iod, &h, &i,&md)) < 0)
		return -1;


	if (i + h.nsat * 36 + ncell * 80 > len * 8) {
		return -1;
	}
	for (j = 0; j < h.nsat; j++) {
		md.r[j] = md.rr[j] = 0.0; md.ex[j] = 15;
	}
	for (j = 0; j < ncell; j++) md.pr[j] = md.cp[j] = md.rrf[j] = -1E16;

	/* decode satellite data */
	for (j = 0; j < h.nsat; j++) { /* range */
		rng = getbitu(buff, i, 8); i += 8;
		if (rng != 255) md.r[j] = rng * RANGE_MS;
	}
	for (j = 0; j < h.nsat; j++) { /* extended info */
		md.ex[j] = getbitu(buff, i, 4); i += 4;
	}
	for (j = 0; j < h.nsat; j++) {
		rng_m = getbitu(buff, i, 10); i += 10;
		if (md.r[j] != 0.0) md.r[j] += rng_m * P2_10*RANGE_MS;
	}
	for (j = 0; j < h.nsat; j++) { /* phaserangerate */
		rate = getbits(buff, i, 14); i += 14;
		if (rate != -8192) md.rr[j] = rate * 1.0;
	}
	/* decode signal data */
	for (j = 0; j < ncell; j++) { /* pseudorange */
		prv = getbits(buff, i, 20); i += 20;
		if (prv != -524288) md.pr[j] = prv * P2_29*RANGE_MS;
	}
	for (j = 0; j < ncell; j++) { /* phaserange */
		cpv = getbits(buff, i, 24); i += 24;
		if (cpv != -8388608) md.cp[j] = cpv * P2_31*RANGE_MS;
	}
	for (j = 0; j < ncell; j++) { /* lock time */
		md.lock[j] = getbitu(buff, i, 10); i += 10;
	}
	for (j = 0; j < ncell; j++) { /* half-cycle amiguity */
		md.half[j] = getbitu(buff, i, 1); i += 1;
	}
	for (j = 0; j < ncell; j++) { /* cnr */
		md.cnr[j] = getbitu(buff, i, 10)*0.0625; i += 10;
	}
	for (j = 0; j < ncell; j++) { /* phaserangerate */
		rrv = getbits(buff, i, 15); i += 15;
		if (rrv != -16384) md.rrf[j] = rrv * 0.0001;
	}

	/* save obs data in msm message */
	save_msm_obs(buff, sys, &h, &md, obs);
	
	//*obsflag = !sync;
	return sync ? 0 : 1;
}