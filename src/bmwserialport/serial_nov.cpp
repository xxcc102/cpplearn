#include "serial.h"
#include <string.h>
#define CRC32_POLYNOMIAL 0xEDB88320L
const int sysconvert[4] = { 0,6,1,5 };

void swap(unsigned char &base, unsigned char &ref)
{
	if (base != ref)
	{
		base ^= ref;
		ref ^= base;
		base ^= ref;
	}
}

int ConstructLogHeader(unsigned char *header, const LogMessHerderBin& headermsg,int len)
{
	//同步位

	setbits(header, len, 8, headermsg.sync1); len += 8;
	setbits(header, len, 8, headermsg.sync2); len += 8;
	setbits(header, len, 8, headermsg.sync3); len += 8;
	//头长度
	setbits(header, len, 8, headermsg.headLen); len += 8;
	//MsgId
	setbitshort(header, len, headermsg.msgID); len += 16;
	//reserved1
	setbitu(header, len, 8, headermsg.reserved1); len += 8;
	//port
	setbitu(header, len, 8, headermsg.port); len += 8;
	//msglen
	setbitshort(header, len, headermsg.msgLen); len += 16;
	//reserved2
	setbitshort(header, len, headermsg.reserved2); len += 16;
	//reserved3
	setbitu(header, len, 8, headermsg.reserved3); len += 8;
	//reserved4
	setbitu(header, len, 8, headermsg.reserved4); len += 8;
	//gpsweek
	setbitshort(header, len, headermsg.gpsWeek); len += 16;
	//gpssow
	setbitint(header, len, headermsg.gpsSow); len += 32;
	//reserved5
	setbitint(header, len, headermsg.reserved5); len += 32;
	//reserved6
	setbitshort(header, len, headermsg.reserved6); len += 16;
	//reserved7
	setbitshort(header, len, headermsg.reserved7); len += 16;

	return len;
}

int ConstructDop(unsigned char *buffer, 
	const LogMessHerderBin& headermsg, const LOG_DOP& podmsg, int len)
{
	int sat_num;
	unsigned long CRC32;
	len += ConstructLogHeader(buffer, headermsg, len);

	setbitfloat(buffer, len, podmsg.gdop); len += 32;

	setbitfloat(buffer, len, podmsg.pdop); len += 32;

	setbitfloat(buffer, len, podmsg.hdop); len += 32;

	setbitfloat(buffer, len, podmsg.htdop); len += 32;

	setbitfloat(buffer, len, podmsg.tdop); len += 32;

	setbitfloat(buffer, len, podmsg.elev_mask); len += 32;

	setbitu_r(buffer, len, 32, podmsg.nsats); len += 32;

	for (sat_num = 0; sat_num < podmsg.nsats; sat_num++)
	{
		setbitu_r(buffer, len, 32, podmsg.cal_sats[sat_num]);
		len += 32;
	}

	CRC32 = CalculateBlockCRC32(len/8, buffer);
	//cout << "ConstructDop CRC32:" << CRC32 << endl;
	setbitint(buffer, len, CRC32); len += 32;

	return len;
}

int ConstructTraceBack(unsigned char *buf, 
	const LogMessHerderBin& hdmsg, const LOG_TRACKSTAT& tbmsg,
	int len)
{
	unsigned long CRC32;
	int chan_num;
	len += ConstructLogHeader(buf, hdmsg, len);

	//solStatus
	setbitint(buf, len, tbmsg.solStatus); len += 32;
	//posType
	setbitint(buf, len, tbmsg.posType); len += 32;
	//cutoff
	setbitfloat(buf, len, tbmsg.solStatus); len += 32;
	//chanNum
	setbitint(buf, len, tbmsg.chanNum); len += 32;
	//chan
	for (chan_num = 0 ; chan_num < tbmsg.chanNum; chan_num++)
	{
		//prn
		setbitshort(buf, len, tbmsg.chan[chan_num].prn); len += 16;
		//glofreq
		setbitshort(buf, len, tbmsg.chan[chan_num].glofreq); len += 16;
		//chTrStatus
		setbits(buf, len, 16, 0); len += 16;
		setbits(buf, len, 3, 0); len += 3;
		setbits(buf, len, 2, 0); len += 2;
		setbits(buf, len, 5, 0); len += 5;
		setbits(buf, len, 6, 0); len += 6;
		//psr
		setbitdouble(buf, len, tbmsg.chan[chan_num].psr); len += 64;
		//doppler
		setbitfloat(buf, len, tbmsg.chan[chan_num].doppler); len += 32;
		//cno
		setbitfloat(buf, len, tbmsg.chan[chan_num].cno); len += 32;
		//locktime
		setbitfloat(buf, len, tbmsg.chan[chan_num].locktime); len += 32;
		//psrRes
		setbitfloat(buf, len, tbmsg.chan[chan_num].psrRes); len += 32;
		//reject
		setbitint(buf, len, tbmsg.chan[chan_num].reject); len += 32;
		//psrWeight
		setbitfloat(buf, len, tbmsg.chan[chan_num].psrWeight); len += 32;
	}


	CRC32 = CalculateBlockCRC32(len, buf);
	setbitint(buf, len, CRC32); len += 32;

	return len;
}

int ConstructBestPos(unsigned char *buf, 
	const LogMessHerderBin& hdmsg, const LOG_BESTPOS& bposmsg, int len)
{
	unsigned long CRC32;
	int stnID_num;
	len += ConstructLogHeader(buf, hdmsg,len);

	//solStatus
	setbitint(buf, len, bposmsg.solStatus); len += 32;
	//posType
	setbitint(buf, len, bposmsg.posType); len += 32;
	//lat
	setbitdouble(buf, len, bposmsg.lat); len += 64;
	//lon
	setbitdouble(buf, len, bposmsg.lon); len += 64;
	//hgt
	setbitdouble(buf, len, bposmsg.hgt); len += 64;
	//dulation
	setbitfloat(buf, len, bposmsg.dulation); len += 32;
	//datumID
	setbitint(buf, len, bposmsg.datumID); len += 32;
	//latSigma
	setbitfloat(buf, len, bposmsg.latSigma); len += 32;
	//lonSigma
	setbitfloat(buf, len, bposmsg.lonSigma); len += 32;
	//hgtSigma
	setbitfloat(buf, len, bposmsg.hgtSigma); len += 32;
	//stnID
	for (stnID_num = 0; stnID_num < 4 ; stnID_num++)
	{
		setbits(buf, len, 8, bposmsg.stnID[stnID_num]); len += 8;
	}
	//diffAge
	setbitfloat(buf, len, bposmsg.diffAge); len += 32;
	//solAge
	setbitfloat(buf, len, bposmsg.solAge); len += 32;
	//nSVs
	setbits(buf, len, 8, bposmsg.nSVs); len += 8;
	//nSolSvs
	setbits(buf, len, 8, bposmsg.nSolSvs); len += 8;
	//nL1SVs
	setbits(buf, len, 8, bposmsg.nL1SVs); len += 8;
	//nL1L2Svs
	setbits(buf, len, 8, bposmsg.nL1L2Svs); len += 8;
	//reserved1
	setbits(buf, len, 8, bposmsg.reserved1); len += 8;
	//reserved2
	setbits(buf, len, 8, bposmsg.reserved2); len += 8;
	//reserved3
	setbits(buf, len, 8, bposmsg.reserved3); len += 8;
	//solSignal
	setbits(buf, len, 8, bposmsg.solSignal); len += 8;
	
	CRC32 = CalculateBlockCRC32(len/8, buf);
	setbitint(buf, len, CRC32); len += 32;

	return len;
}

int ConstructBestSats(unsigned char *buf,
	const LogMessHerderBin& hdmsg, const LOG_BESTSAT& bsatsmsg, int len)
{
	unsigned long CRC32;
	int best_num;
	len += ConstructLogHeader(buf, hdmsg, len);

	setbitint(buf, len, bsatsmsg.entries); len += 32;

	for (best_num = 0; best_num < bsatsmsg.entries; best_num++)
	{
		setbitint(buf, len, bsatsmsg.sat[best_num].sys); len += 32;
		setbitshort(buf, len, bsatsmsg.sat[best_num].sat_id_low); len += 16;
		setbitshort(buf, len, bsatsmsg.sat[best_num].sat_id_high); len += 16;
		setbitint(buf, len, bsatsmsg.sat[best_num].status); len += 32;
		setbitint(buf, len, bsatsmsg.sat[best_num].signal_mask); len += 32;
	}

	CRC32 = CalculateBlockCRC32(len/8, buf);
	setbitint(buf, len, CRC32); len += 32;

	return len/8;
}

int ConstructSatVis2(unsigned char *buf,
	const LogMessHerderBin& hdmsg, const LOG_SATVIS2& bsatmsg, int len)
{
	unsigned long CRC32;
	int sat_num;
	len = ConstructLogHeader(buf, hdmsg, len);

	//sat_sys
	setbitint(buf, len, bsatmsg.sat_sys); len += 32;
	//sat_vis
	setbitint(buf, len, bsatmsg.sat_vis); len += 32;
	//comp_alm
	setbitint(buf, len, bsatmsg.comp_alm); len += 32;
	//sat_number
	setbitint(buf, len, bsatmsg.sat_number); len += 32;
	//
	for (sat_num = 0; sat_num < bsatmsg.sat_number; sat_num++)
	{
		//sat_id_low
		setbitshort(buf, len, bsatmsg.sat[sat_num].sat_id_low); len += 16;
		//sat_id_high
		setbitshort(buf, len, bsatmsg.sat[sat_num].sat_id_high); len += 16;
		//health
		setbitint(buf, len, bsatmsg.sat[sat_num].health); len += 32;
		//elev
		setbitdouble(buf, len, bsatmsg.sat[sat_num].health); len += 64;
		//az
		setbitdouble(buf, len, bsatmsg.sat[sat_num].az); len += 64;
		//true_dop
		setbitdouble(buf, len, bsatmsg.sat[sat_num].true_dop); len += 64;
		//app_dop
		setbitdouble(buf, len, bsatmsg.sat[sat_num].app_dop); len += 64;
	}

	CRC32 = CalculateBlockCRC32(len/8, buf);
	setbitint(buf, len, CRC32); len += 32;
	len += 32;

	return len/8;
}

/* set sign-magnitude bits ---------------------------------------------------*/
void setbitg(unsigned char *buff, int pos, int len, int value)
{
	setbitu(buff, pos, 1, value < 0 ? 1 : 0);
	setbitu(buff, pos + 1, len - 1, value < 0 ? -value : value);
}

/* set unsigned/signed bits ----------------------------------------------------
* set unsigned/signed bits to byte data
* args   : unsigned char *buff IO byte data
*          int    pos    I      bit position from start of data (bits)
*          int    len    I      bit length (bits) (len<=32)
*         (unsigned) int I      unsigned/signed data
* return : none
*-----------------------------------------------------------------------------*/

void setbitu_r(unsigned char *buff, int pos, int len, unsigned int data)
{
	setbitu(buff, pos, len, data);
	reversal(buff, pos + len, len);
}

void reversal(unsigned char *buff, int pos, int len)
{
	int i = 0;
	int inputlen = len / 8;
	int bufflen = pos / 8;
	if (inputlen > 1)
	{
		for (i = 1; i <= inputlen / 2; i++)
		{
			swap(buff[bufflen - i], buff[bufflen - inputlen]);
			inputlen--;
		}
	}
}

/**********************************************/

int getbitu(const unsigned char *buff, int pos, int len)
{
	unsigned int bits = 0;
	int i;
	for (i = pos; i < pos + len; i++) bits = (bits << 1) + ((buff[i / 8] >> (7 - i % 8)) & 1u);
	return bits;
}

/**********************************************************************/
int convertsys(const int& orlsys)
{
	int sys = 0;
	switch (orlsys)
	{
	case 0:sys = 0; break;
	case 1:sys = 1; break;
	case 5:sys = 3; break;
	case 6:sys = 4; break;
	default:sys = 7; break;
	}
	return sys;
}

int conversnrfre(const int sys, const int frenum)
{
	if (frenum == 0)
	{
		if (sys == 5)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
	else if (frenum == 1)
	{
		if (sys == 0)
		{
			return 17;
		}
		else if (sys == 5)
		{
			return 12;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

unsigned long CRC32Value(int i)
{
	unsigned long ulCRC = i;
	for (int j = 8; j > 0; j--)
	{
		if (ulCRC & 1)
		{
			ulCRC = (ulCRC >> 1) ^ CRC32_POLYNOMIAL;
		}
		else
		{
			ulCRC >>= 1;
		}
	}
	return ulCRC;
}

unsigned long CalculateBlockCRC32(unsigned long ulCount, /* Number of bytes in the data block */
	unsigned char *ucBuffer) /* Data block */
{
	unsigned long ulTemp1;
	unsigned long ulTemp2;
	unsigned long ulCRC = 0;

	while (ulCount-- != 0)
	{
		ulTemp1 = (ulCRC >> 8) & 0x00FFFFFFL;
		ulTemp2 = CRC32Value(((int)ulCRC ^ *ucBuffer++) & 0xff);
		ulCRC = ulTemp1 ^ ulTemp2;
	}
	return(ulCRC);
}


void setbitchar(unsigned char *buff, int pos, const char num)
{
	Char2Bin num_unit8;
	num_unit8.int_unit8 = num;
	memcpy(buff + pos / 8, num_unit8.char_num, 2);
}

void setbitfloat(unsigned char *buff, int pos, const float num)
{
	Float2Bin num_float;
	num_float.float_num = num;
	memcpy(buff + pos / 8, num_float.char_num, 4);
}

void setbitulong(unsigned char *buff, int pos, const unsigned long num)
{
	ULONG2Bin num_ulong;
	num_ulong.ulong_num = num;
	memcpy(buff + pos / 8, num_ulong.char_num, 4);
}

void setbitint(unsigned char *buff, int pos, const int num)
{
	INT2Bin num_int;
	num_int.int_num = num;
	memcpy(buff + pos / 8, num_int.char_num, 4);
}

void setbitshort(unsigned char *buff, int pos, const short num)
{
	SHORT2Bin num_short;
	num_short.int_num = num;
	memcpy(buff + pos / 8, num_short.char_num, 2);
}

void setbitdouble(unsigned char *buff, int pos, const double num)
{
	Double2Bin num_double;
	num_double.double_num = num;
	memcpy(buff + pos / 8, num_double.char_num, 8);
}

void setbitu_m(unsigned char *buff, int pos, int len, unsigned int data)
{
	unsigned int mask = 1u;// << (len - 1);
	int i;
	if (len <= 0 || 32 < len)
		return;
	for (i = pos; i < pos + len; i++, mask <<= 1)
	{
		if (data&mask)
			buff[i / 8] |= 1u << (i % 8);
		//buff[i / 8] |= 1u << (7 - i % 8);
		else
			buff[i / 8] &= ~(1u << (i % 8));
		//buff[i / 8] &= ~(1u << (7 - i % 8));
	}
}

void setbitu(unsigned char *buff, int pos, int len, unsigned int data)
{
	unsigned int mask = 1u << (len - 1);
	int i;
	if (len <= 0 || 32 < len)
		return;
	for (i = pos; i < pos + len; i++, mask >>= 1)
	{
		if (data&mask)
			buff[i / 8] |= 1u << (7 - i % 8);
		else
			buff[i / 8] &= ~(1u << (7 - i % 8));
	}
}

void setbits(unsigned char *buff, int pos, int len, int data)
{
	if (data < 0)
		data |= 1 << (len - 1);
	else
		data &= ~(1 << (len - 1)); /* set sign bit */
	setbitu(buff, pos, len, (unsigned int)data);
}

int ConstructLogHeader(unsigned char *header, const novatel *msg, int len)
{
	//同步位

	//setbitchar(header, 2,-86); len += 8;
	//setbitchar(header, 2, 68); len += 8;
	//setbitchar(header, 2, 18); len += 8;
	setbits(header, len, 8, -86); len += 8;
	setbits(header, len, 8, 68); len += 8;
	setbits(header, len, 8, 18); len += 8;
	//头长度
	setbits(header, len, 8, 28); len += 8;
	//MsgId
	setbitshort(header, len, msg->msg_id); len += 16;
	//reserved1
	setbitu(header, len, 8, 0); len += 8;
	//port
	setbitu(header, len, 8, 64); len += 8;
	//msglen
	setbitshort(header, len, msg->msg_len); len += 16;
	//reserved2
	setbitshort(header, len, 0); len += 16;
	//reserved3
	setbitu(header, len, 8, 0); len += 8;
	//reserved4
	setbitu(header, len, 8, 0); len += 8;
	//gpsweek
	setbitshort(header, len, msg->gpsWeek); len += 16;
	//gpssow
	setbitint(header, len, msg->gpsSow); len += 32;
	//reserved5
	setbitint(header, len, 0); len += 32;
	//reserved6
	setbitshort(header, len, 0); len += 16;
	//reserved7
	setbitshort(header, len, 0); len += 16;

	return len;
}

int ConstructDop(unsigned char *buf, const novatel* msg, int len)
{
	unsigned long CRC32;
	int sat_num, crclen = len;

	len = ConstructLogHeader(buf, msg, len);

	setbitfloat(buf, len, msg->gdop); len += 32;

	setbitfloat(buf, len, 0); len += 32;

	setbitfloat(buf, len, msg->hdop); len += 32;

	setbitfloat(buf, len, 0); len += 32;

	setbitfloat(buf, len, 0); len += 32;

	setbitfloat(buf, len, 0); len += 32;

	setbitint(buf, len, msg->nSVs); len += 32;

	for (sat_num = 0; sat_num < msg->nSVs; sat_num++)
	{
		setbitint(buf, len, 0);
		len += 32;
	}

	CRC32 = CalculateBlockCRC32((len - crclen) / 8, buf + crclen/8);
	setbitulong(buf, len, CRC32); len += 32;

	return len;
}

int ConstructTraceBack(unsigned char *buf, const novatel* msg, int len)
{
	unsigned long CRC32;
	int chan_num, fre_num,sys_type,prn, crclen =len;

	len = ConstructLogHeader(buf, msg, len);

	//solStatus
	setbitint(buf, len, 0); len += 32;
	//posType
	setbitint(buf, len, 0); len += 32;
	//cutoff
	setbitfloat(buf, len, 0); len += 32;
	//chanNum
	setbitint(buf, len, msg->nSVs * 2); len += 32;
	//chan
	for (sys_type = 0 ; sys_type < 4 ; sys_type++)
	{
		for (chan_num = 0; chan_num < msg->satnum[sys_type]; chan_num++)
		{
			for (fre_num = 0; fre_num < 2; fre_num++)
			{
				//prn
				if (sys_type == 2)
				{
					prn = msg->sat[sys_type][chan_num].prn + 37;
				}
				else
				{
					prn = msg->sat[sys_type][chan_num].prn;
				}
				setbitshort(buf, len, prn); len += 16;
				//glofreq
				setbitshort(buf, len, 10); len += 16;
				//chTrStatus
				setbitu_m(buf, len, 16, 0); len += 16;
				setbitu_m(buf, len, 3, convertsys(msg->sat[sys_type][chan_num].sys)); len += 3;
				setbitu_m(buf, len, 2, 0); len += 2;
				setbitu_m(buf, len, 5, conversnrfre(msg->sat[sys_type][chan_num].sys, fre_num)); len += 5;
				setbitu_m(buf, len, 6, 0); len += 6;
				//psr
				setbitdouble(buf, len, 0); len += 64;
				//doppler
				setbitfloat(buf, len, 0); len += 32;
				//cno
				setbitfloat(buf, len, msg->sat[sys_type][chan_num].cno[fre_num]); len += 32;
				//locktime
				setbitfloat(buf, len, 0); len += 32;
				//psrRes
				setbitfloat(buf, len, 0); len += 32;
				//reject
				setbitint(buf, len, 0); len += 32;
				//psrWeight
				setbitfloat(buf, len, 0); len += 32;
			}
		}
	}


	CRC32 = CalculateBlockCRC32((len - crclen) / 8, buf + crclen / 8);
	setbitulong(buf, len, CRC32); len += 32;

	return len;
}

int ConstructBestPos(unsigned char *buf, const novatel* msg, int len)
{
	unsigned long CRC32;
	int stnID_num, crclen = len;
	
	len = ConstructLogHeader(buf, msg, len);

	//solStatus
	setbitint(buf, len, 0x99); len += 32;
	//posType
	setbitint(buf, len, 0x1234); len += 32;
	//lat
	setbitdouble(buf, len, msg->lat); len += 64;
	//lon
	setbitdouble(buf, len, msg->lon); len += 64;
	//hgt
	setbitdouble(buf, len, msg->hgt); len += 64;
	//dulation
	setbitfloat(buf, len, msg->dulation); len += 32;
	//datumID
	setbitint(buf, len, 0); len += 32;
	//latSigma
	setbitfloat(buf, len, 0); len += 32;
	//lonSigma
	setbitfloat(buf, len, 0); len += 32;
	//hgtSigma
	setbitfloat(buf, len, 0); len += 32;
	//stnID
	for (stnID_num = 0; stnID_num < 4; stnID_num++)
	{
		setbits(buf, len, 8, 0); len += 8;
	}
	//diffAge
	setbitfloat(buf, len, 0); len += 32;
	//solAge
	setbitfloat(buf, len, 0); len += 32;
	//nSVs
	setbits(buf, len, 8, msg->nSVs); len += 8;
	//nSolSvs
	setbits(buf, len, 8, msg->nSolSvs); len += 8;
	//nL1SVs
	setbits(buf, len, 8, 0); len += 8;
	//nL1L2Svs
	setbits(buf, len, 8, 0); len += 8;
	//reserved1
	setbits(buf, len, 8, 0); len += 8;
	//reserved2
	setbits(buf, len, 8, 0); len += 8;
	//reserved3
	setbits(buf, len, 8, 0); len += 8;
	//solSignal
	setbits(buf, len, 8, 0); len += 8;

	CRC32 = CalculateBlockCRC32((len - crclen) / 8, buf + crclen / 8);
	setbitint(buf, len, CRC32); len += 32;

	return len;
}

int ConstructBestSats(unsigned char *buf, const novatel* msg, int len)
{
	unsigned long CRC32;
	int best_num, sys_type, crclen = len;

	len = ConstructLogHeader(buf, msg, len);
	//entries
	setbitint(buf, len, msg->nSVs); len += 32;

	for (sys_type = 0 ; sys_type < 4 ; sys_type++)
	{
		for (best_num = 0; best_num < msg->satnum[sys_type]; best_num++)
		{
			//sys
			setbitint(buf, len, msg->sat[sys_type][best_num].sys); len += 32;
			//sat_id_low
			setbitshort(buf, len, msg->sat[sys_type][best_num].prn); len += 16;
			//sat_id_high
			setbitshort(buf, len, 0); len += 16;
			//status
			setbitint(buf, len, msg->sat[sys_type][best_num].status); len += 32;
			//signal_mask
			setbitint(buf, len, 0); len += 32;
		}
	}

	CRC32 = CalculateBlockCRC32((len - crclen) / 8, buf + crclen / 8);
	setbitulong(buf, len, CRC32); len += 32;

	return len;
}

int ConstructSatVis2(unsigned char *buf, const novatel* msg, int len, int sysnum)
{
	unsigned long CRC32;
	int sat_num;
	int sys_type;
	int crclen = len;
	len = ConstructLogHeader(buf, msg, len);

	//sat_sys
	setbitint(buf, len, sysconvert[sysnum]); len += 32;
	//sat_vis
	setbitint(buf, len, 0); len += 32;
	//comp_alm
	setbitint(buf, len, 0); len += 32;
	//sat_number
	setbitint(buf, len, msg->satnum[sysnum]); len += 32;
	//
	for (sat_num = 0; sat_num < msg->satnum[sysnum]; sat_num++)
	{
		//sat_id_low
		setbitshort(buf, len, msg->sat[sysnum][sat_num].prn); len += 16;
		//sat_id_high
		setbitshort(buf, len, 0); len += 16;
		//health
		setbitint(buf, len, msg->sat[sysnum][sat_num].status); len += 32;
		//elev
		setbitdouble(buf, len, msg->sat[sysnum][sat_num].elev); len += 64;
		//az
		setbitdouble(buf, len, msg->sat[sysnum][sat_num].az); len += 64;
		//true_dop
		setbitdouble(buf, len, 0); len += 64;
		//app_dop
		setbitdouble(buf, len, 0); len += 64;
	}

	

	CRC32 = CalculateBlockCRC32((len - crclen) / 8, buf + crclen / 8);
	setbitulong(buf, len, CRC32); len += 32;

	return len;
}