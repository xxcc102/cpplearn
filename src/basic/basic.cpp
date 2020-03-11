#include "basic.h"
#include <fstream>






int sameword(char *wordpos,char*wordrov)
{
	int wordp, letterp,len = strlen(wordrov),i;
	while (wordpos)
	{
		for (wordp = 0; wordp < len; wordp++)
		{
			if (*wordpos == *(wordrov + wordp))
			{
				for (i = wordp; i < len ; i++)
				{
					//wordrov = 
					;
				}
			}
		}
	}


	//for (wordp = 0; wordp < strlen(wordpos); wordp++)
	//{
	//	for (letterp = 0; letterp < strlen(wordrov); letterp++)
	//	{

	//	}
	//}
	return 0;
}


int findchangeposword(char *fname,char *word)
{
	FILE *fp;
	char buf[1024];
	int len = 0;
	char *letter,*p;
	int wordlen = strlen(word);

	if (fopen(fname,"r"))
	{
		printf("openfile fail");
	}
	while (fgets(buf,1024,fp))
	{
		len = 0;
		while (*(buf+len))
		{
			if (len == 0 || *(buf+len) == ' ' || *(buf + len) == '\n' || *(buf + len) == '\t')
			{
				letter = buf + len;
				//letterlen = strlen(letter);
				//if (letterlen == wordlen)
				//{

				//}
			}
		}
		
	}

	return 0;
}


int get_weekday(int year, int month, int day)
{
	int i,weekday= 0,totalday = 0;
	int summonthday[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	for (i = 0;i < month - 1;i++)
	{
		totalday = summonthday[i];
	}
	totalday += (year - 1) * 365 + year / 4 - year / 400 + day;
	weekday = totalday % 7;
	return weekday;
}


int insertsort()
{

	return 0;
}


int strcmp_nc(char *s1,char*s2)
{
	while (s1)
	{
		if ((*s1 - 'a') < 0)
		{
			*s1 = *s1 + 32;
		}
		
		if ((*s2 - 'a') < 0)
		{
			*s2 = *s2 + 32;
		}


		if (*s1 - *s2)
		{
			return s1 - s2;
		}
		s1++;
		s2++;
	}
	return 0;
}


int findbigword(char *src,char *res)
{
	int i;
	char tmp = *src;
	for (i = 0; *(src + i) != '\0'; i++)
	{
		if ((tmp - *(src + i)) < 0 )
		{
			tmp = *(src + i);
		}
	}
	res = &tmp;
	return (*res -'0');
}


int SearchDelChar(char *src,char*findchar)
{
	char *q, *p;
	int i, j, res;
	bool flag = false;

	for (p = src, i = 0; *(p + i) != '\0'; i++)
	{
		if (*(p+i)== *findchar)
		{
			res = i + 1;
			break;
		}
	}

	if (i == strlen(src))
	{
		return 0;
	}

	strcpy(src + i, src + i + 1);

	return res;
}

int STRCOUNT(char*str, char*substr)
{
	char *q;
	int i,j = 0,strcnt = 0;
	bool flag = false;

	if (str == NULL || substr == NULL)
	{
		return 0;
	}

	q = str;
	for (int i = 0; *(q+i) != '\0';i++)
	{

		if (*(q+i) != *substr)
		{
			continue;
		}
		else
		{
			j = 0;
			do 
			{
				j++;
				i++;
				if (*(substr + j) == *(q + i) && *(q + i) != '\0')
				{
					continue;
				}
				flag = true;
			} while (*(substr + j) != '\0');
			
		}
		if (flag)
		{
			strcnt++;
			flag = false;
		}
	}
	return strcnt;
}



int sumadd(int a, int n)
{
	int i, j, sum = 0, single = 1;
	for (i = 0; i < n; i++)
	{
		sum += single;
		single *= 10;
		single += 1;

	}

	return sum * a;
}





bool increment(char *number)
{
	bool isvaild = false;
	return isvaild;
}




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


