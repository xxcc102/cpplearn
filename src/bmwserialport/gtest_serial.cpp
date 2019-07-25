#include "serial_send_data.h"
#include "gtest/gtest.h"

int GetMsgLen(unsigned char *buf)
{
	char ch[2];
	UINT16 msglen = 0;
	ch[0] = buf[8];
	ch[1] = buf[9];
	memcpy(&msglen, ch, 2);
	return msglen;
}

void ComfirmHeader(LogMessHerderBin &orl, LogMessHerderBin &rst )
{
	EXPECT_EQ(orl.sync1,		rst.sync1);
	EXPECT_EQ(orl.sync2,		rst.sync2);
	EXPECT_EQ(orl.sync3,		rst.sync3);
	EXPECT_EQ(orl.headLen,		rst.headLen);
	EXPECT_EQ(orl.msgID,		rst.msgID);
	EXPECT_EQ(orl.reserved1,	rst.reserved1);
	EXPECT_EQ(orl.port,			rst.port);
	EXPECT_EQ(orl.msgLen,		rst.msgLen);
	EXPECT_EQ(orl.reserved2,	rst.reserved2);
	EXPECT_EQ(orl.reserved3,	rst.reserved3);
	EXPECT_EQ(orl.reserved4,	rst.reserved4);
	EXPECT_EQ(orl.gpsWeek,		rst.gpsWeek);
	EXPECT_EQ(orl.gpsSow,		rst.gpsSow);
	EXPECT_EQ(orl.reserved5,	rst.reserved5);
	EXPECT_EQ(orl.reserved6,	rst.reserved6);
	EXPECT_EQ(orl.reserved7,	rst.reserved7);
}

void CompareSat(BEST_SAT &orl, BEST_SAT &rst)
{
	EXPECT_EQ(orl.sys, rst.sys);
	EXPECT_EQ(orl.sat_id_low, rst.sat_id_low);
	EXPECT_EQ(orl.sat_id_high, rst.sat_id_high);
	EXPECT_EQ(orl.status, rst.status);
	EXPECT_EQ(orl.signal_mask, rst.signal_mask);
}


void Compare_pos(novatel orl, LOG_BESTPOS rst)
{
	EXPECT_EQ(orl.gpsSow, rst.header.gpsSow);
	EXPECT_EQ(orl.gpsWeek, rst.header.gpsWeek);
	EXPECT_FLOAT_EQ(orl.lat, rst.lat);
	EXPECT_FLOAT_EQ(orl.lon, rst.lon);
	EXPECT_FLOAT_EQ(orl.hgt, rst.hgt);
	EXPECT_EQ(orl.dulation, rst.dulation);
	EXPECT_EQ(orl.solAge, rst.solAge);
	EXPECT_EQ(orl.nSVs, rst.nSVs);
	EXPECT_EQ(orl.nSolSvs, rst.nSolSvs);
}

TEST(Generate_Pos, comfirm)
{
	novatel nov_data;
	int all_len = 0;
	unsigned char buf[kmaxbuflen];

	GetNovetal_data(nov_data);

	nov_data.msg_id = 42;
	nov_data.msg_len = 72;
	int len = ConstructBestPos(buf, &nov_data, all_len);

	GenerateBestsats(buf);
	int msglen = GetMsgLen(buf);

	LOG_BESTPOS pos_rst;
	int header_len = sizeof(pos_rst.header);
	memset(&pos_rst, 0, sizeof(LOG_BESTPOS));

	memcpy((char*)&pos_rst, buf, msglen + kheaderlen);


	Compare_pos(nov_data, pos_rst);

	cout << "finished" << endl;
}


TEST(Generate_Savis2, comfirm)
{
	novatel nov_data;
	int all_len = 0;
	unsigned char buf[kmaxbuflen];

	GetNovetal_data(nov_data);
	nov_data.msg_id = 1043;
	nov_data.msg_len = 16 + nov_data.satnum[0] * 40;
	all_len = ConstructSatVis2(buf, &nov_data, all_len, 0);

	GenerateBestsats(buf);
	int msglen = GetMsgLen(buf);

	LOG_SATVIS2 satvis2_rst;
	memcpy((char*)&satvis2_rst + kheaderlen, buf + kheaderlen, msglen);

	cout << "finished" << endl;

}





TEST(Merge_msg, Normal)
{
	novatel nov_data;
	int all_len = 0;
	unsigned char buf[kmaxbuflen];

	GetNovetal_data(nov_data);

	nov_data.msg_id = 42;
	nov_data.msg_len = 72;
	all_len = ConstructBestPos(buf, &nov_data, all_len);

	nov_data.msg_id = 174;
	nov_data.msg_len = 28 + nov_data.nSVs * 4;
	all_len = ConstructDop(buf, &nov_data, all_len);

	LOG_DOP comfirm_dop;
	memcpy((char*)&comfirm_dop, buf + 104, 108);



}



TEST(Generate_TrackSat,Comfirm)
{
	novatel nov_data;
	int all_len = 0;
	unsigned char buf[kmaxbuflen];

	GetNovetal_data(nov_data);
	nov_data.msg_id = 83;
	nov_data.msg_len = 16 + nov_data.nSVs * 80;
	all_len = ConstructTraceBack(buf, &nov_data, all_len);

	int icode = getbitu(buf + kheaderlen +  32, 21, 5);

	GenerateBestsats(buf);
	int msglen = GetMsgLen(buf);

	LOG_TRACKSTAT tracksat_rst;
	memcpy((char*)&tracksat_rst + kheaderlen, buf + kheaderlen, msglen);

	int a = 0;
}






TEST(Generate_bestsat, comfirm)
{
	unsigned char buf[kmaxbuflen];
	LOG_BESTSAT bestsats_rst;

	GenerateBestsats(buf);
	int msglen = GetMsgLen(buf);

	memcpy((char*)&bestsats_rst, buf, msglen + kheaderlen);

	LogMessHerderBin hd_msg_orl;
	GetHeaderBestsats(hd_msg_orl);
	ComfirmHeader(hd_msg_orl, bestsats_rst.header);

	LOG_BESTSAT bestsats_msg;
	GetBestsats(bestsats_msg);
	EXPECT_EQ(bestsats_msg.entries, bestsats_rst.entries);

	for (int num = 0 ; num < bestsats_msg.entries ; num++)
	{
		CompareSat(bestsats_msg.sat[num], bestsats_rst.sat[num]);
	}

	UINT32 crc32;
	memcpy(&crc32, buf + msglen + kheaderlen, 4);

}

TEST(Generate_sativs2, comfirm)
{

}


TEST(ConstructDop_test,dop)
{
	LogMessHerderBin hd_msg;
	GetHeaderDOP(hd_msg);

	unsigned char buf[kmaxbuflen];
	LOG_DOP dop;
	GetDop(dop);

	//int res = ConstructDop(buf, hd_msg, dop);

	LogMessHerderBin hd_msg_rst;
	memcpy(&hd_msg_rst, buf, kheaderlen);
	
	LOG_DOP dop_rst;

	char ch[2];
	ch[0] = buf[8];
	ch[1] = buf[9];
	
	UINT16 msglen = 0;
	memcpy(&msglen,ch,2);
	
	memcpy((char*)&dop_rst + kheaderlen,buf + kheaderlen, msglen);

	UINT32 crc32;
	memcpy(&crc32, buf + 196 -4, 4);

	cout << "finished" << endl;
}


TEST(Construcheader, dop)
{
	LogMessHerderBin hd_msg;
	GetHeaderDOP(hd_msg);

	unsigned char header[200];
	//ConstructLogHeader(header, hd_msg);

	LogMessHerderBin hd_msg_out;
	memcpy(&hd_msg_out, header, 28);
	//cout << "finished" << endl;
}



TEST(Generate_CRC32, comfirm)
{

}