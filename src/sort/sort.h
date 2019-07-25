#ifndef _GTEST_SORT
#define _GTEST_SORT
#include "timer.h"

enum SORT_TYPE
{
	BUBBLE = 0,
	QUICK,
	INSERT,
	HEAP,
	SELECT,
	SHELL
};

class Sort 
{
	void swap(int &a, int &b);

	void BubbleSort(std::vector<int> &);


	void InsertSort(std::vector<int> &);

	void HeapSort(std::vector<int> &);

	void SelectSort(std::vector<int> &);

	void ShellSort(std::vector<int> &);
	
public:
	void Sort_fun(std::vector<int> &,const SORT_TYPE &);

	vector<int> QuickSort(std::vector<int> &list, int start, int end);

	vector<int> MergeSort(std::vector<int> &);
	
	vector<int> Merge(std::vector<int> &left, std::vector<int> &right);
};

#endif