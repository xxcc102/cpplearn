#include "sort.h"


using namespace std;

void Sort::Sort_fun(std::vector<int> &list,const SORT_TYPE &sorttypes)
{
	switch (sorttypes)
	{
	case SORT_TYPE::BUBBLE:
		BubbleSort(list);
		break;
	case SORT_TYPE::HEAP:
		HeapSort(list);
		break;
	case SORT_TYPE::INSERT:
		InsertSort(list);
		break;
	case SORT_TYPE::QUICK:
		//BubbleSort(list);
		break;
	case SORT_TYPE::SELECT:
		SelectSort(list);
		break;
	case SORT_TYPE::SHELL:
		ShellSort(list);
		break;
	default:
		break;
	}
}


void Sort::swap(int &a, int &b)
{
	a ^= b;     //a=a^b
	b ^= a;     //b=b^(a^b)=b^a^b=b^b^a=0^a=a
	a ^= b;     //a=(a^b)^a=a^b^a=a^a^b=0^b=b}
}

void Sort::BubbleSort(vector<int> &list)
{
	int out, in;

	if (list.empty())
	{
		return;
	}
	for (out = 0 ; out < list.size(); out ++ )
	{
		for (in = 0; in < list.size() - out - 1 ; in++)
		{
			if (list.at(in + 1) < list.at(in))
			{
				swap(list.at(in + 1), list.at(in));
			}
		}
	}
}

//void Sort::QuickSort(std::vector<int> &list)
//{
//
//
//
//
//}

void Sort::InsertSort(std::vector<int> &list)
{
	int cur,preindex;
	if (list.empty())
	{
		throw "Insert Sort list is too short";
	}
	for(int i = 0 ; i < list.size() - 1; i++)
	{
		cur = list.at(i + 1);
		preindex = i;
		while ( preindex >= 0 && cur < list.at(preindex) )
		{
			list.at(preindex + 1) = list.at(preindex);
			preindex--;
		}
		list.at(preindex + 1) = cur;
	}
}

void Sort::HeapSort(std::vector<int> &list)
{


}

void Sort::SelectSort(std::vector<int> &list)
{
	int minpos,temp;
	if (list.size() <= 0)
	{
		throw "Select Sort list is too short";
	}

	for (int i = 0; i < list.size(); i++)
	{
		minpos = i;
		for (int j = i; j < list.size(); j++)
		{
			if (list.at(j) < list.at(minpos))
			{
				minpos = j;
			}
		}
		temp = list.at(i);
		list.at(i) = list.at(minpos);
		list.at(minpos) = temp;
	}
}

void Sort::ShellSort(std::vector<int> &list)
{
	int temp, gap = list.size() / 2, preindex;

	if (list.empty())
	{
		throw "Shell Sort list is too short";
	}
	while (gap > 0)
	{
		for (int i = 0 ; i < list.size() ; i++)
		{
			temp = list.at(i);
			preindex = i - gap;
			while (preindex >= 0 && temp < list.at(preindex))
			{
				list.at(preindex + gap) = list.at(preindex);
				preindex -= gap;
			}
			list.at(preindex + gap) = temp;
		}
		gap /= 2;
	}
}

vector<int> Sort::MergeSort(std::vector<int> &list)
{
	if (list.size() < 2)
	{
		throw "Merge Sort list is too short";
	}
	int mid = list.size() / 2;
	vector<int> left(list.at(0),list.at(mid));
	vector<int> right(list.at(mid),list.back());

	return Merge(MergeSort(left),MergeSort(right));
}

vector<int> Sort::Merge(std::vector<int> &left, std::vector<int> &right)
{
	vector<int> *rst = new vector<int>(left.size() + right.size());

	for (int index = 0, i = 0 ,j = 0; index < rst->size() ; index ++ )
	{
		if (i < left.size())
		{
			rst->at(index) = right.at(j++);
		}
		else if (j > right.size())
		{
			rst->at(index) = left.at(i++);
		}
		else if ( left.at(i) < right.at(j) )
		{
			rst->at(index) = left.at(i);
			i++;
		}
		else if (right.at(j) < left.at(i))
		{
			rst->at(index) = right.at(j);
			j++;
		}
	}
	return *rst;
}

std::vector<int> Sort::QuickSort(std::vector<int> &list, int start, int end)
{
	if (list.empty() || start < 0 || end > list.size() || start > end)
	{
		throw "Quick Sort list length is error";
		return vector<int>(0);
	}


}

