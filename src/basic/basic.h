#pragma once
#include "common.h"

struct ListNode
{
	int m_nKey;
	ListNode * m_pNext;
};

struct BinaryTreeNode
{
	int	m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

template<typename T>
class Static_Member
{
public:
	static int mem_;
};



template<typename T>
class StackWithMin
{
	std::stack<T> data_stack;
	std::stack<T> min_stack;
public:
	void push(const T&);
	void pop();
	const T& min();
};

int ListLenght(const ListNode* l);
void PrintList(const ListNode* l);
void PrintMatrixClockwisely(int **number, int cols, int rows);

ListNode* ReverseList(ListNode *pHead);

ListNode* MergeList(ListNode* pHead1,ListNode* pHead2);

ListNode* MergeList_offer(ListNode* pHead1, ListNode* pHead2);

ListNode *MergeList_iter(ListNode* pHead1, ListNode* pHead2);


class RightValue{
	int *m_ptr;
public:
	RightValue() :m_ptr(new int(0)) { std::cout << "构造函数" << std::endl; }
	RightValue(const RightValue &rv) :m_ptr(new int(*rv.m_ptr)) { std::cout << "深拷贝构造" << std::endl; }
	RightValue(RightValue&& rv) :m_ptr(rv.m_ptr) {
		rv.m_ptr = nullptr;
	}

};


class NumOfBin
{
public:
	int NumOfAllBin(int n);
	int IsOddNum(int n);
};


class My_Power
{
public:
	double Power(const double base,const int exponent);

};


int writebinary(unsigned char *buf, const int& len);
