#include "decode.h"
#include "gtest/gtest.h"

using namespace std;

struct PackageBuf
{
	int msg_type;
	int len;
	unsigned char buf[500];
};


int GetPackage(const unsigned char* buf, const int &len, int &type, int &pos)
{
	for (int i = 0; i < len; i++)
	{
		if ((unsigned char)buf[i] != kRtcm32Preamble)
		{
			continue;
		}

		pos = i;

		if (len - pos < 3)
		{
			return 0;
		}

		int dlen = getbitu(buf + pos, 14, 10);
		if (dlen > 1023)
		{
			continue;
		}

		if (len - pos < dlen + 6)
		{
			return 0;
		}

		int cc = calCrc24(buf + pos, dlen + 3);
		int cb = getbitu(buf + pos, (dlen + 3) * 8, 24);
		if (cc != cb)
		{
			continue;
		}

		int tp = getbitu(buf + pos, 24, 12);

		if (tp == 999)
		{
			return -7;
		}

		if (type == 0 || (type != 0 && tp == type))
		{
			type = tp;
			return dlen + 6;
		}
	}
	return -1;
}


//void Get3EF(const unsigned char* buf)
//{
//
//}

void GetRtcmPackagesByFile(const string& fn, std::vector<PackageBuf>& packages)
{
	const unsigned int  kNumMaxBufLen = 2046;

	ifstream fraw(fn, ios::binary);
	assert(fraw.is_open());


	int writePos = 0;
	unsigned char read_buf[kNumMaxBufLen] = { 0 };
	while (!fraw.eof())
	{
		fraw.read((char*)read_buf + writePos, kNumMaxBufLen - writePos);
		int bLen = fraw.gcount() + writePos;

		int processPos = 0;
		while (1)
		{
			int pos = 0;
			int tp = 0;
			int re = GetPackage(read_buf + processPos, bLen - processPos, tp, pos);

			//if (re == -7)
			//{
			//	while ()
			//	{

			//	}
			//	fraw.read((char*)read_buf + writePos, kNumMaxBufLen - writePos);
			//	
			//}

			if (re < 0)
			{
				writePos = 0;
				break;
			}
			else if (re == 0)
			{
				memcpy(read_buf, read_buf + (processPos + pos), bLen - (processPos + pos));
				writePos = bLen - (processPos + pos);
				break;
			}
			else
			{
				PackageBuf pb;

				pb.msg_type = tp;
				memcpy(pb.buf, read_buf + processPos + pos, re);
				pb.len = re;
				packages.push_back(pb);

				processPos = processPos + pos + re;

			}
		}
	}
}

void initobs(obs_t *obs)
{
	if (!(obs->data = (obsd_t *)malloc(sizeof(obsd_t)*MAXOBS)))
		free(obs->data);
	obs->n = 0;
	obs->nmax = MAXOBS;
}



TEST(GET_DATA, NORMAL)
{
	string fname = "D:\\learn\\cpplearn\\test_data\\RxRec20191025.dat";
	vector<PackageBuf> packdata;
	packdata.reserve(3000);
	vector<obs_t> all_obs;
	nav_t eph;
	obs_t obs;

	GetRtcmPackagesByFile(fname, packdata);

	initnav(&eph);
	initobs(&obs);

	int  rst = -1;
	for (auto item : packdata)
	{

		switch (item.msg_type)
		{
		case 1044:
			rst = decode_type1044(item.buf, item.len, &eph);
			break;
		case 1046:
			rst = decode_type1046(item.buf, item.len, &eph);
			break;
		case 1013:
			rst = -1;
			//rst = decode_type1013(item.buf, item.len, &eph);
			break;
		case 1042:
			rst = decode_type1046(item.buf, item.len, &eph);
			break;
		case 1019:
			rst = decode_type1019(item.buf, item.len, &eph);
			break;
		case 1077:
			rst = decode_msm7(item.buf, item.len, SYS_GPS, &obs);
			break;
		case 1117:
			rst = decode_msm7(item.buf, item.len, SYS_QZS, &obs);
			break;
		case 1127:
			rst = decode_msm7(item.buf, item.len, SYS_CMP, &obs);
			break;
		case 1097:
			rst = decode_msm7(item.buf, item.len, SYS_GAL, &obs);
			break;
		case 4075:
			rst = -1;
			break;
		default:
			rst = -1;
			cout << "type" << item.msg_type << endl;
		}
		if (rst == 1)
		{
			sortobs(&obs);
			all_obs.push_back(obs);
			//free(&obs);
			//initobs(&obs);
			obs.n = obs.nmax = 0;
			memset(obs.data , 0, sizeof(obsd_t)*MAXOBS);
		}

	}

	for (int i = 0; i < MAXSAT; i++)
	{
		cout << "sat[" << i << ":]" << eph.eph[i].sat << endl; //don't include glonass
	}

	uniqnav(&eph);

	for (int i = 0; i < MAXSAT; i++)
	{
		cout << "sat[" << i << ":]" << eph.eph[i].sat << endl; //don't include glonass
	}


}