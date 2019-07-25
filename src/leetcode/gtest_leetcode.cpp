#include "leetcode.h"
#include "gtest/gtest.h"

ListNode* GenerateList(const std::vector<int> ll)
{
	ListNode * L = new ListNode(0);
	ListNode * r;
	r = L;
	for (int i = 0; i < ll.size(); i++)
	{
		ListNode * p = new ListNode(i);
		r->next = p;
		r = p;
	}
	L = L->next;

	return L;
}

void  PrintListNode(ListNode *pHead)
{
	while (pHead)
	{
		ListNode *tmp = pHead;
		pHead = pHead->next;
		std::cout << tmp->val << "->";
	}
	std::cout << "nullptr" << std::endl;
}

TEST(mdlistnode, normal)
{
	vector<int> in{ 1,2,3,4,5,6 };
	ListNode *out = GenerateList(in);

	MNode mn;
	ListNode *rst = mn.middleNode(out);
}


TEST(countPrime, SetBits_normal)
{
	SetBits sb;
	int rst;
	//rst = sb.countPrimeSetBits(6,9);
	//rst = sb.countPrimeSetBits(10,15);
	//cout << sb.countPrimeSetBits(842,888) << endl;
	cout << sb.countPrimeSetBits(244,269) << endl;
}

TEST(Relative_Sort_Array,test_normal)
{
	vector<int> arr1{2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
	vector<int> arr2{ 2, 1, 4, 3, 9, 6 };

	Array_Kind arrmem;
	//vector<int> rst_iter = arrmem.relativeSortArray(arr1,arr2);
	vector<int> rst_iter = arrmem.relativeSortArray_online(arr1,arr2);
	for (auto mem : rst_iter)
	{
		cout << mem << endl;
	}
}

TEST(getIntersectionNode_test,Normal)
{
	vector<int> list1 = { 4,1,8,4,5 };
	vector<int> list2 = { 5,0,1,8,4,5 };
	ListNode *pHead1 = GenerateList(list1);
	ListNode *pHead2 = GenerateList(list2);
	//PrintListNode(pHead1);
	IntersectionTwoList *ITL = new IntersectionTwoList();
	ListNode *rst= ITL->getIntersectionNode(pHead1, pHead2);
	PrintListNode(rst);
}

TEST(Areaof3D , Normal)
{
	Areaof3D obj;
	vector<int> obj_inner;
	vector<int> obj_inner1;
	vector<vector <int>> obj_all;
	obj_inner.push_back(2);
	obj_all.push_back(obj_inner);

	EXPECT_EQ(obj.projectionArea(obj_all),5);
	
	obj_inner.clear();
	obj_all.clear();
	obj_inner.push_back(1);
	obj_inner.push_back(2);
	obj_inner1.push_back(3);
	obj_inner1.push_back(4);
	obj_all.push_back(obj_inner);
	obj_all.push_back(obj_inner1);

	EXPECT_EQ(obj.projectionArea(obj_all), 17);

	obj_inner.clear();
	obj_inner1.clear();
	obj_all.clear();
	obj_inner.push_back(1);
	obj_inner.push_back(0);
	obj_inner1.push_back(0);
	obj_inner1.push_back(2);
	obj_all.push_back(obj_inner);
	obj_all.push_back(obj_inner1);

	EXPECT_EQ(obj.projectionArea(obj_all), 8);

}

TEST(MaxDepth , Normal)
{
	MaxDepth obj;
	


	vector<Node*> child1;
	child1.reserve(2);
	Node single[6];
	single[0].val = 5;
	child1.push_back(&single[0]);
	
	single[1].val = 6;
	child1.push_back(&single[1]);

	vector<Node*> child;
	child.reserve(3);
	single[2].val = 3;
	child.push_back(&single[2]);
	single[3].val = 2;

	
	//int depth = obj.maxDepthofNtree(&root);
	//EXPECT_EQ(obj.maxDepthofNtree(&root),3);

}