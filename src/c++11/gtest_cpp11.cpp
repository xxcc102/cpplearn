#include "cpp11.h"
#include "gtest/gtest.h"
#include "boost/regex.hpp"
#include <bitset>

void print(){}



//enum status_
//{
//	RED = 0,
//	YELLOW = 1,
//	ERROR = 2,
//	UNKNOW = 3
//};
//
//struct stauts
//{
//	int pos;
//	int stat;
//};
//
//
//void convert_tec(vector<stauts> &in)
//{
//	vector<stauts> con_stat;
//	int loop_status = UNKNOW;
//	int len = 0;
//
//	for (auto iter = in.begin(); iter != in.end();iter++)
//	{
//		stauts loop_con;
//		if (iter->stat == loop_status)
//		{
//			loop_con.stat = iter->stat;
//			loop_con.pos = len++;
//		}
//		else
//		{
//
//		}
//		loop_status = iter->stat;
//	}
//}
//TEST(MERGER_SITUATION, NORMAL)
//{
//	vector<stauts> in;
//	stauts tmp[10];
//
//
//	tmp[0].stat = RED;
//	tmp[1].stat = RED;
//	tmp[2].stat = RED;
//	tmp[3].stat = YELLOW;
//	tmp[4].stat = YELLOW;
//	tmp[5].stat = RED;
//	tmp[6].stat = RED;
//	tmp[7].stat = RED;
//	tmp[8].stat = RED;
//	tmp[9].stat = RED;
//	tmp[10].stat = ERROR;
//	tmp[11].stat = ERROR;
//
//	for (int i = 0; i < 12; i++)
//	{
//		tmp[i].pos = i;
//		in.push_back(tmp[i]);
//	}
//
//	convert_tec(in);
//
//}

TEST(Boost_TEST, 1)
{
	std::string line;
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)");

	while (std::cin)
	{
		std::getline(std::cin, line);
		boost::smatch matches;
		if (boost::regex_match(line, matches, pat))
			std::cout << matches[2] << std::endl;
	}
}


template<typename T,typename... Type>
void print(const T& firstArg, const Type&... args)
{
	cout << firstArg << endl;
	print(args...);
}

struct Sat_t 
{
	int outc[3];
};

struct Opt_t
{
	int maxout;
};

struct Rtk_t
{
	Sat_t ssat[10];
	Opt_t opt;
};


TEST(CJW_TEST, NORMAL)
{
	Rtk_t *rtk = new Rtk_t();
	int i = 1, f = 0;
	memset(rtk, 0, sizeof(Rtk_t));
	for (int i = 0 ; i < 3 ; i++ )
	{
		rtk->ssat[0].outc[i] = i+4;
	}
	rtk->opt.maxout = 5;

	int reset = ++rtk->ssat[i - 1].outc[f] > (unsigned int)rtk->opt.maxout;
	
	f = 1;
	reset = ++rtk->ssat[i - 1].outc[f] > (unsigned int)rtk->opt.maxout;
	
	int k = 0;
}


TEST(Variadic_Templates, Normal)
{
	print(7.5,"hello",bitset<16>(377),42);
}


