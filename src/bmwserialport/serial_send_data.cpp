#include <iostream>
#include "serial_send_data.h"

void GetHeaderDOP(LogMessHerderBin& hd_msg)
{
	hd_msg.sync1 = -86;
	hd_msg.sync2 = 68;
	hd_msg.sync3 = 18;
	hd_msg.headLen = 28;
	//
	hd_msg.msgID = 174;
	hd_msg.reserved1 = 0;
	hd_msg.port = 64;
	//
	hd_msg.msgLen = 164;
	hd_msg.reserved2 = 0;
	hd_msg.reserved3 = 0;// -113;
	hd_msg.reserved4 = 0;// -76;
	//
	hd_msg.gpsWeek = 2061;
	hd_msg.gpsSow = 439878000;

	hd_msg.reserved5 = 0;// 33554464;
	hd_msg.reserved6 = 0;// 6009;
	hd_msg.reserved7 = 0;// 15340;
}


void GetHeaderSatvis2(LogMessHerderBin& hd_msg)
{
	memset(&hd_msg, 0, sizeof(LogMessHerderBin));
	hd_msg.sync1 = -86;
	hd_msg.sync2 = 68;
	hd_msg.sync3 = 18;

	hd_msg.headLen = 28;
	hd_msg.msgID = 1194;
	hd_msg.port = 64;

	hd_msg.msgLen = 724;
}


void GetHeaderBestsats(LogMessHerderBin& hd_msg)
{
	memset(&hd_msg, 0, sizeof(LogMessHerderBin));
	hd_msg.sync1 = -86;
	hd_msg.sync2 = 68;
	hd_msg.sync3 = 18;

	hd_msg.headLen = 28;
	hd_msg.msgID = 1194;
	hd_msg.port = 64;

	hd_msg.msgLen = 756;
}


void GetHeaderTrackstat(LogMessHerderBin& hd_msg)
{
	memset(&hd_msg, 0, sizeof(LogMessHerderBin));
	hd_msg.sync1 = -86;
	hd_msg.sync2 = 68;
	hd_msg.sync3 = 18;

	hd_msg.headLen = 28;
	hd_msg.msgID = 83;
	hd_msg.port = 64;

	hd_msg.msgLen = 724;
}


void GetHeaderBestpos(LogMessHerderBin& hd_msg)
{
	memset(&hd_msg, 0, sizeof(LogMessHerderBin));
	hd_msg.sync1 = -86;
	hd_msg.sync2 = 68;
	hd_msg.sync3 = 18;

	hd_msg.headLen = 28;
	hd_msg.msgID = 42;
	hd_msg.port = 64;

	hd_msg.msgLen = 72;
	hd_msg.gpsWeek = 2062;
	hd_msg.gpsSow = 26400000;
}


/************************************************************************/

void GetDop(LOG_DOP& dop_msg)
{
	memset(&dop_msg, 0, sizeof(LOG_DOP));

	dop_msg.nsats = 34;
	dop_msg.gdop = 1.618;

	dop_msg.hdop = 0.558;
}

void GetBestsats(LOG_BESTSAT& bestsats_msg)
{
	memset(&bestsats_msg, 0, sizeof(LOG_BESTSAT));
	bestsats_msg.entries = 47;
	//gps
	for (int i = 0 ; i < 10 ; i++)
	{
		bestsats_msg.sat[i].sys = 0;
		bestsats_msg.sat[i].status = 0;
	}
	bestsats_msg.sat[0].sat_id_low = 1;
	bestsats_msg.sat[1].sat_id_low = 30;
	bestsats_msg.sat[2].sat_id_low = 22;
	bestsats_msg.sat[3].sat_id_low = 3;
	bestsats_msg.sat[4].sat_id_low = 7;
	bestsats_msg.sat[5].sat_id_low = 8;
	bestsats_msg.sat[6].sat_id_low = 28;
	bestsats_msg.sat[7].sat_id_low = 11;
	bestsats_msg.sat[8].sat_id_low = 18;
	bestsats_msg.sat[9].sat_id_low = 17;

	//QZSS
	for (int i = 10 ; i < 13 ; i++)
	{
		bestsats_msg.sat[i].sys = 7;
		bestsats_msg.sat[i].status = 0;
	}
	bestsats_msg.sat[10].sat_id_low = 199;
	bestsats_msg.sat[11].sat_id_low = 194;
	bestsats_msg.sat[12].sat_id_low = 193;
	
	//GLONASS
	for (int i = 13; i < 20; i++)
	{
		bestsats_msg.sat[i].sys = 1;
		bestsats_msg.sat[i].status = 0;
	}
	bestsats_msg.sat[13].sat_id_low = 14;
	bestsats_msg.sat[14].sat_id_low = 1;
	bestsats_msg.sat[15].sat_id_low = 18;
	bestsats_msg.sat[16].sat_id_low = 16;
	bestsats_msg.sat[17].sat_id_low = 15;
	bestsats_msg.sat[18].sat_id_low = 24;
	bestsats_msg.sat[19].sat_id_low = 17;

	
	//GAL
	for (int i = 20; i < 27; i++)
	{
		bestsats_msg.sat[i].sys = 5;
		bestsats_msg.sat[17].sat_id_low = i;
		bestsats_msg.sat[i].status = 0;
	}


	//BDS
	for (int i = 27; i < 47; i++)
	{
		bestsats_msg.sat[i].sys = 6;
		bestsats_msg.sat[i].status = 0;
	}

	//
}

void GetSatvis2(LOG_SATVIS2& satvis2_msg)
{
	memset(&satvis2_msg, 0, sizeof(LOG_SATVIS2));


}

void GetTrackstat(LOG_TRACKSTAT& bestsats_msg)
{
	memset(&bestsats_msg, 0, sizeof(LOG_TRACKSTAT));


}

void GetBestpos(LOG_BESTPOS& bestsats_msg)
{
	memset(&bestsats_msg, 0, sizeof(LOG_BESTPOS));
	bestsats_msg.lat = 40.0717278310214;
	bestsats_msg.lon = 116.238933820636;
	bestsats_msg.hgt = 104.114352928475;
	bestsats_msg.solAge = 0;
	bestsats_msg.dulation = -9.7;
	bestsats_msg.nSVs = 48;
	bestsats_msg.nSolSvs = 33;
}


/***********************************************************************/

int GenerateDop(unsigned char *buf)
{
	LogMessHerderBin hd_msg;
	GetHeaderDOP(hd_msg);

	LOG_DOP dop;
	GetDop(dop);
	return 0;

	//return ConstructDop(buf, hd_msg, dop);
}


int GenerateBestsats(unsigned char *buf)
{
	LogMessHerderBin hd_msg;
	GetHeaderBestsats(hd_msg);

	LOG_BESTSAT bestsats;
	GetBestsats(bestsats);

	return 0;
	//return ConstructBestSats(buf, hd_msg, bestsats);
}


int GenerateSatvis2(unsigned char *buf)
{
	LogMessHerderBin hd_msg;
	GetHeaderSatvis2(hd_msg);

	LOG_SATVIS2 satvis2;
	GetSatvis2(satvis2);
	return 0;

	//return ConstructSatVis2(buf, hd_msg, satvis2);
}


int GenerateBestpos(unsigned char *buf)
{
	LogMessHerderBin hd_msg;
	GetHeaderBestpos(hd_msg);

	LOG_BESTPOS bestpos;
	GetBestpos(bestpos);
	return 0;

	//return ConstructBestPos(buf, hd_msg, bestpos);
}


int GenerateTrackstat(unsigned char *buf)
{
	LogMessHerderBin hd_msg;
	GetHeaderTrackstat(hd_msg);

	LOG_TRACKSTAT trackstat;
	GetTrackstat(trackstat);
	return 0;

	//return ConstructTraceBack(buf, hd_msg, trackstat);
}



/*************************************************/

int GetNovetal_data(novatel& nov_data)
{
	memset(&nov_data,0,sizeof(novatel));

	nov_data.gpsWeek = 2062;
	nov_data.gpsSow = 26400000;
	nov_data.lat = 116.23892094777;
	nov_data.lon = 40.0716995459126;
	nov_data.hgt = 95.7294904096052;
	nov_data.solAge = 0;
	nov_data.dulation = -9.7;
	nov_data.nSVs = 12;
	nov_data.nSolSvs = 9;
	nov_data.gdop = 1.618;
	nov_data.hdop = 0.558;
	//for (int i = 0 ; i < 4 ; i++)
	//{
	//	nov_data.satnum[i] = 3;
	nov_data.satnum[0] = 12;
	//}
	//nov_data.satnum{ 3,3,3,3 };
	nov_data.sat[0][0] = { 0, 2, 34.6372730011833, 225.640252593772, { 39.5, 42.25 }, 0 };
	nov_data.sat[0][1] = { 0, 6, 77.3984730793249, 267.095155694842, { 46.75, 47.25 }, 0 };
	nov_data.sat[0][2] = { 0, 8, 53.2593668754983, 171.664507944766, { 43.5, 46.75 }, 0 };
	nov_data.sat[0][3] = { 0, 9, 51.6759634850639, 243.057296942193, { 43, 46.25 }, 0 };
	nov_data.sat[0][4] = { 0, 11, 22.3445142304509, 201.302476403359, { 41.5, 44.75 }, 0 };
	nov_data.sat[0][5] = { 0, 13, 69.8757589652236, 207.873093547424, { 47.25, 46 }, 0 };
	nov_data.sat[0][6] = { 0, 14, 64.4069616620136, 40.8532251296003, { 47.75, 50.5 }, 0 };
	nov_data.sat[0][7] = { 0, 16, 72.6348135453727, 263.101312235957, { 48, 48.25 }, 0 };
	nov_data.sat[0][8] = { 0, 21, 20.8283010548542, 77.9153966145236, { 42, 0 }, 0 };
	nov_data.sat[0][9] = { 0, 28, 32.6820137840001, 290.792834577465, { 46.25, 0 }, 0 };
	nov_data.sat[0][10] = { 0, 33, 43.0044142863587, 288.913129584893, { 46.25, 0 }, 0 };
	nov_data.sat[0][11] = { 0, 34, 6.03341772438872, 183.318204786055, { 38.5, 0 }, 0 };


#if 0 
	//gps
	nov_data.sat[0][0].sys = 0;
	nov_data.sat[0][0].prn = 5;
	nov_data.sat[0][0].elev = 73.12229;
	nov_data.sat[0][0].az = 169.78654;
	nov_data.sat[0][0].cno[0] = 42;
	nov_data.sat[0][0].cno[1] = 43;
	nov_data.sat[0][0].status = 0;

	
	nov_data.sat[0][1].sys = 0;
	nov_data.sat[0][1].prn = 10;
	nov_data.sat[0][1].elev = 62.9172;
	nov_data.sat[0][1].az = 289.63823;
	nov_data.sat[0][1].cno[0] = 34;
	nov_data.sat[0][1].cno[1] = 13;
	nov_data.sat[0][1].status = 1;

	
	nov_data.sat[0][2].sys = 0;
	nov_data.sat[0][2].prn = 15;
	nov_data.sat[0][2].elev = 29.0078;
	nov_data.sat[0][2].az = 46.82777;
	nov_data.sat[0][2].cno[0] = 22;
	nov_data.sat[0][2].cno[1] = 20;
	nov_data.sat[0][2].status = 0;

	//bds
	nov_data.sat[1][0].sys = 6;
	nov_data.sat[1][0].prn = 5;
	nov_data.sat[1][0].elev = 5.80925;
	nov_data.sat[1][0].az = 91.002002;
	nov_data.sat[1][0].cno[0] = 30;
	nov_data.sat[1][0].cno[1] = 31;
	nov_data.sat[1][0].status = 0;


	nov_data.sat[1][1].sys = 6;
	nov_data.sat[1][1].prn = 10;
	nov_data.sat[1][1].elev = 6.797434;
	nov_data.sat[1][1].az = 211.45923;
	nov_data.sat[1][1].cno[0] = 30;
	nov_data.sat[1][1].cno[1] = 40;
	nov_data.sat[1][1].status = 1;


	nov_data.sat[1][2].sys = 6;
	nov_data.sat[1][2].prn = 15;
	nov_data.sat[1][2].elev = 20.236818;
	nov_data.sat[1][2].az = 75.524053;
	nov_data.sat[1][2].cno[0] = 25;
	nov_data.sat[1][2].cno[1] = 44;
	nov_data.sat[1][2].status = 0;

	//glo
	nov_data.sat[2][0].sys = 1;
	nov_data.sat[2][0].prn = 16;
	nov_data.sat[2][0].elev = 24.99678;
	nov_data.sat[2][0].az = 146.642478;
	nov_data.sat[2][0].cno[0] = 19;
	nov_data.sat[2][0].cno[1] = 33;
	nov_data.sat[2][0].status = 0;


	nov_data.sat[2][1].sys = 1;
	nov_data.sat[2][1].prn = 10;
	nov_data.sat[2][1].elev = 29.137632;
	nov_data.sat[2][1].az = 219.00309;
	nov_data.sat[2][1].cno[0] = 28;
	nov_data.sat[2][1].cno[1] = 79;
	nov_data.sat[2][1].status = 1;


	nov_data.sat[2][2].sys = 1;
	nov_data.sat[2][2].prn = 17;
	nov_data.sat[2][2].elev = 38.096062;
	nov_data.sat[2][2].az = 293.004505;
	nov_data.sat[2][2].cno[0] = 30;
	nov_data.sat[2][2].cno[1] = 22;
	nov_data.sat[2][2].status = 0;

	//gal
	nov_data.sat[3][0].sys = 5;
	nov_data.sat[3][0].prn = 5;
	nov_data.sat[3][0].elev = 40.371358;
	nov_data.sat[3][0].az = 248.729191;
	nov_data.sat[3][0].cno[0] = 25;
	nov_data.sat[3][0].cno[1] = 36;
	nov_data.sat[3][0].status = 0;


	nov_data.sat[3][1].sys = 5;
	nov_data.sat[3][1].prn = 10;
	nov_data.sat[3][1].elev = 55.90598;
	nov_data.sat[3][1].az = 130.389169;
	nov_data.sat[3][1].cno[0] = 22;
	nov_data.sat[3][1].cno[1] = 33;
	nov_data.sat[3][1].status = 1;


	nov_data.sat[3][2].sys = 5;
	nov_data.sat[3][2].prn = 15;
	nov_data.sat[3][2].elev = 66.295774;
	nov_data.sat[3][2].az = 0.8426434;
	nov_data.sat[3][2].cno[0] = 25;
	nov_data.sat[3][2].cno[1] = 29;
	nov_data.sat[3][2].status = 0;
#endif


	return 0;
}

