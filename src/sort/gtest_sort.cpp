#include "sort.h"
#include "gtest/gtest.h"

static TimeTrack tracker;
using namespace std;

const int gtimes = 5;
vector<vector<int>> glist;


struct Gen_Num 
{
	long size;
	long low;
	long up;
};

void Generate_Num(const Gen_Num &conf, vector<int>& list)
{
	int num;

	list.reserve(conf.size);

	for (int i = 0; i < conf.size; i++)
	{
		num = (rand() % (conf.up - conf.low + 1)) + conf.low;
		list.push_back(num);
	}		
}

void Compare(vector<int> &sortlist)
{
	int tmp = 0;
	for (auto &node:sortlist)
	{
		EXPECT_LE(tmp,node);
		tmp = node;
	}
}

int Test_Sort(const SORT_TYPE &type)
{
	vector<unsigned long> timelist;

	//生成sort对象
	Sort sort;

	for (int num = 0; num < gtimes; num++)
	{
		vector<int> list = glist.at(num);
		int start_time = tracker.Track();
		sort.Sort_fun(list, type);
		int finish_time = tracker.Track();
		unsigned long time_dur = tracker.DurationTime(start_time, finish_time);

		timelist.push_back(time_dur);
		tracker.ClearStamp();

		Compare(list);
	}

	return accumulate(timelist.begin(), timelist.end(), 0) / timelist.size();
}


TEST(Get_test_data, Size_Thousand)
{
	Gen_Num conf;
	conf.size = 1000;
	conf.low = 0;
	conf.up = 9999999;
	for (int i = 0; i < gtimes ; i++)
	{
		vector<int> list;
		Generate_Num(conf, list);
		glist.push_back(list);
	}
}


TEST(Test_Sort, ArrayLen_Thousand)
{
	int bubble_time = Test_Sort(SORT_TYPE::BUBBLE);
	int select_time = Test_Sort(SORT_TYPE::SELECT);
	int insert_time = Test_Sort(SORT_TYPE::INSERT);
	int shell_time = Test_Sort(SORT_TYPE::SHELL);
	//int merge_time = ;
	cout << "Bubble_sort 10^3 cost: " << bubble_time << " ms" << endl;
	cout << "Select_sort 10^3 cost: " << select_time << " ms" << endl;
	cout << "Insert_sort 10^3 cost: " << insert_time << " ms" << endl;
	cout << "Shell_sort 10^3 cost: " << shell_time << " ms" << endl;
}

//TEST(Test_Bubble_Sort, Array_thousand)
//{
//}
//
//TEST(Test_Select_Sort, Array_thousand)
//{
//}
//
//TEST(Test_Insert_Sort, Array_thousand)
//{
//}
//
//TEST(Test_Shell_Sort, Array_thousand)
//{
//}