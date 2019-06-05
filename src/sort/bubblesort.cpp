#include "sort.h"


using namespace std;

int Generate_Num()
{


	return 0;
}



void Sort::swap(int &a, int &b)
{
	a ^= b;     //a=a^b
	b ^= a;     //b=b^(a^b)=b^a^b=b^b^a=0^a=a
	a ^= b;     //a=(a^b)^a=a^b^a=a^a^b=0^b=b}
}

void Sort::BubbleSort(array<int,10> *input)
{
	int out, in;

	if (input->empty())
	{
		return;
	}
	for (out = 0 ; out < input->size(); out ++ )
	{
		for (in = 0; in < input->size() - out - 1 ; in++)
		{
			if (input->at(in + 1) < input->at(in))
			{
				swap(input->at(in + 1), input->at(in));
			}
		}
	}
}

void Sort::QuickSort(std::vector<int> *)
{




}

void Sort::InsertSort(std::vector<int> *)
{


}

void Sort::HeapSort(std::vector<int> *)
{


}


TEST(Test_Bubble_Sort,Array_ten)
{


}

int main()
{

	array<int, 10> unsorted = { 54,12,22,1,23,40,13,18,44,5 };



	Sort sort;

	sort.BubbleSort(&unsorted);

	for (int i = 0 ; i < unsorted.size();i++)
	{
		cout << unsorted.at(i) << endl;
	}

	return 0;
}