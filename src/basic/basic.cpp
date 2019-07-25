#include "basic.h"
#include <fstream>

ListNode* ReverseListNode(ListNode* phead, const int k)
{
	int cnt = 0;
	ListNode *ret = NULL;
	ListNode *cur = phead;
	while (phead->m_pNext != NULL)
	{
		if (cnt < k) cnt++;
		else ret = cur;
		cur = cur->m_pNext;
	}
	return ret;
}


int ListLenght(const ListNode* l)
{
	int len = 0;
	while (l)
	{
		l = l->m_pNext;
		len++;
	}
	return len;
}

void PrintList(const ListNode* l)
{
	while (l)
	{
		std::cout << l->m_nKey << "->";
		l = l->m_pNext;
	}
	std::cout << "nullptr" <<std::endl;
}

template<typename T>
void StackWithMin<T>::push(const T& value)
{
	data_stack.emplace(value);
	if (value < min_stack.top())
	{
		min_stack.emplace(value);
	}
	else
	{
		min_stack.emplace(data_stack.top());
	}
}

template<typename T>
void StackWithMin<T>::pop()
{
	if (!min_stack.empty() && !data_stack.empty())
	{
		data_stack.pop();
		min_stack.pop();
	}
}

template<typename T>
const T& StackWithMin<T>::min()
{
	if (!min_stack.empty() && !data_stack.empty())
	{
		return min_stack.top();
	}
}

int NumOfBin::NumOfAllBin(int n)
{
	int count = 0;
	
	while (n)
	{
		++count;
		n = (n - 1)&n;
	}
	return count;
}

int NumOfBin::IsOddNum(int num)
{
	num = (num - 1)&num;
	if (num)
	{
		return false;
	}
	return true;
}

//double My_Power::Power(const double base, const int exponent)
//{
//	double rst = 1.0;
//	if ( exponent > 0 )
//	{
//		for (int i = 0; i < exponent; i++)
//		{
//			rst *= base;
//		}
//	}
//	else if (exponent == 0)
//	{
//		return 0;
//	}
//	else
//	{
//
//	}
//}

ListNode *MergeList_iter(ListNode* pHead1,ListNode* pHead2)
{
	if (!pHead1)
	{
		return pHead2;
	}
	if (!pHead2)
	{
		return pHead1;
	}

	if (pHead1->m_nKey <= pHead2->m_nKey)
	{
		pHead1->m_pNext = MergeList_iter(pHead1->m_pNext, pHead2);
		return pHead1;
	}
	else
	{
		pHead2->m_pNext = MergeList_iter(pHead1, pHead2->m_pNext);
		return pHead2;
	}

}

ListNode* MergeList_offer(ListNode* pHead1 , ListNode* pHead2)
{
	if (!pHead1)
	{
		return pHead2;
	}
	if (!pHead2)
	{
		return pHead1;
	}
	ListNode* pHeadMerge = nullptr;
	if (pHead1->m_nKey < pHead2->m_nKey)
	{
		pHeadMerge = pHead1;
		pHeadMerge->m_pNext = MergeList_offer(pHead1->m_pNext,pHead2);
	}
	else
	{
		pHeadMerge = pHead2;
		pHeadMerge->m_pNext = MergeList_offer(pHead1,pHead2->m_pNext);
	}
	return pHeadMerge;
}

ListNode* MergeList(ListNode* pHead1, ListNode* pHead2)
{
	if ( pHead1 == nullptr )
	{
		return pHead2;
	}
	if (pHead2 == nullptr)
	{
		return pHead1;
	}
	ListNode* head, *tail;
	head = new ListNode;
	tail = head;
	while (pHead1 || pHead2)
	{
		ListNode *tmp = new ListNode;

		if (!pHead1)
		{
			tail->m_pNext = pHead2;
			break;
		}
		else if (!pHead2)
		{
			tail->m_pNext = pHead1;
			break;
		}
		else if (pHead1->m_nKey <= pHead2->m_nKey)
		{
			tmp = pHead1;
			pHead1 = pHead1->m_pNext;
			tmp->m_pNext = nullptr;
		}
		else
		{
			tmp = pHead2;
			pHead2 = pHead2->m_pNext;
			tmp->m_pNext = nullptr;
		}
		
		tail->m_pNext = tmp;
		tail = tmp;
	}
	head = head->m_pNext;
	return head;
}

ListNode* ReverseList(ListNode *pHead)
{
	if (pHead == nullptr)
	{
		return nullptr;
	}

	if (pHead->m_pNext == nullptr)
	{
		return pHead;
	}

	ListNode* pReversedHead = nullptr;
	ListNode* pNode = pHead;
	ListNode* pPrev = nullptr;

	while (pNode)
	{
		ListNode* pNext = pNode->m_pNext;
		if (pNext)
		{
			pReversedHead = pNode;
		}

		pNode->m_pNext = pPrev;
		pPrev = pNode;
		pNode = pNext;
	}
	return pPrev;
}

int writebinary(unsigned char *buf, const int& len)
{
	const std::string binfile = "../../../testbin.bin";
	//const std::string binfile = "D://learn//cpplearn//test_data//testbin.bin";

	std::ofstream ostrm(binfile, std::ios::binary);
	ostrm.write(reinterpret_cast<char*>(&buf), len); // 二进制输出
	return 0;
}


