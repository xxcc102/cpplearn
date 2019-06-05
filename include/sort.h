#include <iostream>
#include <vector>
#include <array>
#include "gtest/gtest.h"


class Sort {
	void swap(int &a, int &b);
public:
	void BubbleSort(std::array<int, 10>*);

	void QuickSort(std::vector<int> *);

	void InsertSort(std::vector<int> *);

	void HeapSort(std::vector<int> *);
};


