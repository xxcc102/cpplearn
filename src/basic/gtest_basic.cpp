#include "basic.h"
#include "gtest/gtest.h"
#include <memory>
#include <list>
#include <iterator>
using namespace std;

ListNode* GetLast_K(ListNode *list,const int k)
{
	int n = 0;
	ListNode *pTempList = list;
	ListNode *pRetList = NULL;
	while (pTempList->m_pNext != NULL)
	{
		n++;
	}
    int count = n - k;
	pTempList = list;
	while (count)
	{
		pRetList = pTempList;
		pTempList = pTempList->m_pNext;
	}

	return pRetList;
}


int get_top_pos(std::vector<int>& list_input, const int k)
{
	int pos;
	int high = list_input.size();
	int low = 0;
	int tmp = 0;
	if (k > high)
	{
		return high;
	}

	while (true)
	{
		tmp = (high - low) / 2;
		if (list_input.at(tmp) > k)
		{
			high = high / 2;
		}
		else if (list_input.at(tmp) == k)
		{
			pos = high / 2;
			if (list_input.at(++pos) != k)
			{
				return pos;
			}
		}
		else
		{
			low = high / 2;
		}
	}
}

int Static_Member<int>::mem_ = 1;
int Static_Member<char>::mem_ = 2;


TEST(SETBITS_TEST,NORMAL)
{
	unsigned char buf[200];
	memset(buf,1,100);
	const int len = 100;
	int rst = writebinary(buf, 100);


}


TEST(Virtual_ptr,Normal)
{
	class Virtual_Size
	{
	public:
		void test4(){}
		//virtual int test1() { return 0; }
		//virtual int test2() { return 0; }
		//virtual int test3() { return 0; }
	protected:
	private:
	};

	Virtual_Size Size;
	int a = sizeof(Size);
	int k = 0;
}


TEST(Vector_Increase, Normal)
{
	vector<int> p = { 1,2,3 };
	p.push_back(4);
	p.push_back(5);
	p.push_back(5);
	p.push_back(5);
	p.push_back(5);
	p.push_back(5);
	p.size();
	
}


TEST(STATIC_MEMBER,NORMAL)
{
	cout << Static_Member<int>::mem_ << endl;
	cout << Static_Member<char>::mem_ << endl;

	Static_Member<int> obji1, obji2;
	Static_Member<char> objc1, objc2;

	cout << obji1.mem_ << endl;
	cout << obji2.mem_ << endl;
	cout << objc1.mem_ << endl;
	cout << objc2.mem_ << endl;

	obji1.mem_ = 3;
	objc2.mem_ = 4;

	cout << obji1.mem_ << endl;
	cout << obji2.mem_ << endl;
	cout << objc1.mem_ << endl;
	cout << objc2.mem_ << endl;
}


TEST(mianshi,top_pos)
{
	std::vector<int> order = {1,1,3,3,5,5};
//	int rst = get_top_pos(order,5);
	int rst = get_top_pos(order,1);
	rst = get_top_pos(order,3);
	
}


ListNode* GenerateList(const std::vector<int> ll)
{
	ListNode *L, *r;
	L = new ListNode;
	r = L;
	for (int i = 0; i < ll.size(); i++)
	{
		ListNode * p = new ListNode;
		p->m_nKey = ll.at(i);
		r->m_pNext = p;
		r = p;
	}
	r->m_pNext = nullptr;
	L = L->m_pNext;
	return L;
}


void change_ptr(double *QQ)
{
	
}

TEST(StackWithMin_TEST,Normal)
{
	//StackWithMin stack;

}


TEST(EraseList,NormalTest)
{
	std::list<int> c{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	auto a = c.erase(c.begin());

	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	std::list<int>::iterator range_begin = c.begin();
	std::list<int>::iterator range_end = c.begin();
	std::advance(range_begin, 2);
	std::advance(range_end, 5);

	c.erase(range_begin, range_end);

	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';

}

//TEST(PrintMatrix,Normal)
//{
//	int matrix[4][4];
//	PrintMatrixClockwisely((int**)matrix,1,2);
//}


//TEST(Test_unique_ptr,Normal_Use)
//{
//	std::unique_ptr<double> QQ(new double[100]);
//	memset(QQ.get(),0,sizeof(double)*100);
//	//change_ptr(QQ);
//
//	int b = 0;
//}



TEST(Merge_List_test,Normal_newlist)
{
	std::vector<int> orl_list1 = { 1,2,3 };
	//std::vector<int> orl_list1 = { 1,2,3,4,5,6,7,8,9,101 };
	ListNode *pL1 = GenerateList(orl_list1);

	std::vector<int> orl_list2 = { 1,6 };
	//std::vector<int> orl_list2 = { 1,3,4,6,7,9,13,79 };
	ListNode *pL2 = GenerateList(orl_list2);

	ListNode* rst = MergeList_iter(pL1,pL2);
	//ListNode* rst = MergeList_offer(pL1,pL2);
	PrintList(rst);

	int len = ListLenght(rst);
	
	int tmp;
	while (rst->m_pNext)
	{
		tmp = rst->m_nKey;
		EXPECT_GE(rst->m_pNext->m_nKey,tmp);
		rst = rst->m_pNext;
	}
}

TEST(ReverseList_test,Normal)
{
	std::vector<int> orl_list = {1,2,3,4,5,6,7,8,9};
	ListNode *L = GenerateList(orl_list);
	
	ListNode *rst = ReverseList(L);

	int rst_value = 9;
	while (rst)
	{
			EXPECT_EQ(rst->m_nKey, rst_value);
			ListNode* tmp = rst->m_pNext;
			delete rst;
			rst = tmp;
			rst_value--;
	}

	ListNode *single = new ListNode;
	single->m_nKey = 4;
	single->m_pNext = nullptr;
	ListNode *rst_single = ReverseList(single);
	EXPECT_EQ(rst_single->m_nKey, 4);
	delete single;

}

TEST(NumerOfBin, Normal_Num)
{
	NumOfBin num;
	EXPECT_EQ(num.NumOfAllBin(9999), 8);
}


TEST(IsOddNum, Normal_Num)
{
	NumOfBin num;
	EXPECT_TRUE(num.IsOddNum(1024));
	EXPECT_FALSE(num.IsOddNum(9999));
}