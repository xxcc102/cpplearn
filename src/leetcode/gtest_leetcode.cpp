#include "leetcode.h"
#include "gtest/gtest.h"
void Insert_Node(ListNode* node, vector<int> val)
{

	if (val.empty())
	{
		return;
	}

	ListNode *newnode = new ListNode(val.back());
	val.pop_back();
	node->next = newnode;
	Insert_Node(node->next, val);
	
	//node = node->next;
}
TEST(Search, Normal)
{
	vector<int> in{ -1,0,3,5,9,12 };
	vector<int> in1{ 3,24,50,79,88,150,345 };

	BinarySearchSol *sol = new BinarySearchSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	int res = sol->search(in, 3);
}



TEST(TwoSum, Normal)
{
	vector<int> in{ 2,3,4 };
	vector<int> in1{ 3,24,50,79,88,150,345 };

	BinarySearchSol *sol = new BinarySearchSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	vector<int> res = sol->twoSum(in, 6);
}

TEST(Intersection, Normal)
{
	vector<int> in{ 4,9,5 };
	vector<int> in1{ 9,4,9,8,4 };

	HashTableSol *sol = new HashTableSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	vector<int> res = sol->intersection(in1,in1);
}


TEST(IslandPerimeter, Normal)
{
	vector<vector<int>> in{ { 0,1,0,0 } ,{1,1,1,0} ,{0,1,0,0},{1,1,0,0} };

	HashTableSol *sol = new HashTableSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	int res = sol->islandPerimeter(in);
}


TEST(NextLargerNodes, 1)
{
	ListNode *Node = new ListNode(0);
	ListNode *Node1 = new ListNode(0);

	//vector<int> node_val{ 1,2,2,1 };
	vector<int> node_val{ 5,1,2 };
	vector<int> node_val1{ 5,1 };

	Insert_Node(Node, node_val);
	Insert_Node(Node1, node_val1);

	LinkSol *sol = new LinkSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	vector<int> res = sol->nextLargerNodes(Node->next);
}


TEST(GetIntersectionNode, 1)
{
	ListNode *Node = new ListNode(0);
	ListNode *Node1 = new ListNode(0);

	//vector<int> node_val{ 1,2,2,1 };
	vector<int> node_val{ 4,6,2 };
	vector<int> node_val1{ 5,1 };

	Insert_Node(Node, node_val);
	Insert_Node(Node1, node_val1);

	LinkSol *sol = new LinkSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	ListNode *res = sol->getIntersectionNode(Node->next, Node1->next);
}


TEST(RemoveElements, 1)
{
	ListNode *Node = new ListNode(0);

	//vector<int> node_val{ 1,2,2,1 };
	vector<int> node_val{ 2,1 };

	Insert_Node(Node, node_val);

	LinkSol *sol = new LinkSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	ListNode *res = sol->removeElements(Node->next,1);
}



TEST(IsPalindrome, 1)
{
	ListNode *Node = new ListNode(0);

	vector<int> node_val{ 1,2,2,1 };

	Insert_Node(Node, node_val);

	LinkSol *sol = new LinkSol();
	//ListNode *res = sol->deleteDuplicates(Node->next);
	sol->isPalindrome(Node->next);
}



TEST(DeleteDuplicates, 1)
{
	ListNode *Node = new ListNode(0);

	vector<int> node_val{ 1,1,2,3,3 };

	Insert_Node(Node, node_val);

	LinkSol *sol = new LinkSol();
	//sol->reverseList(Node);
	//ListNode *res = sol->deleteDuplicates(Node->next);
	ListNode *res1 = sol->deleteDuplicates1(Node->next);
}


//
//TEST(A_STRING,B)
//{
//	statictest_c::func_a(5);
//	statictest::func_a(15);
//
//
//
//	string a = "";
//	auto tmp = a.rbegin();
//	int b = 0;
//}


TEST(MergeTwoLists,1)
{
	ListNode *Node1 = new ListNode(0);
	ListNode *Node2 = new ListNode(0);

	vector<int> node_val1{ 4,2,1 };
	vector<int> node_val2{ 4,3,1 };

	Insert_Node(Node1, node_val1);
	Insert_Node(Node2, node_val2);
		
	LinkSol *sol = new LinkSol();
	//sol->reverseList(Node);
	ListNode *rst = sol->mergeTwoLists1(Node1->next, Node2->next);
	ListNode *rst1 = sol->mergeTwoLists(Node1->next, Node2->next);
}


TEST(ReverseList,1)
{
	ListNode *Node = new ListNode(0);

	vector<int> node_val{ 8,7,6,5,4,3,2,1 };

	Insert_Node(Node, node_val);
		
	LinkSol *sol = new LinkSol();
	//sol->reverseList(Node);
	sol->reverseList1(Node);

}


TEST(MatrixReshape,1)
{
	vector<vector<int>> in;
	vector<int> vec[2];
	vec[0] = { 1,2 };
	vec[1] = { 3,4 };
	in.push_back(vec[0]);
	in.push_back(vec[1]);


	Solution *sol = new Solution();
	sol->matrixReshape(in,1,4);
}

TEST(IsToeplitzMatrix,1)
{
	vector<int> vec[5];
	vec[0] = { 1,2,3,4 };
	vec[1] = { 5,1,2,3 };
	vec[2] = { 9,5,1,2 };

	vec[3] = { 1,2 };
	vec[4] = { 2,2 };

	vector<vector<int>> matrix[3];
	matrix[0].push_back(vec[0]);
	matrix[0].push_back(vec[1]);
	matrix[0].push_back(vec[2]);
	matrix[1].push_back(vec[3]);
	matrix[1].push_back(vec[4]);

	vector<int> vec1{ 65, 98, 57 };
	matrix[2].push_back(vec1);
	Solution *sol = new Solution();
	EXPECT_EQ(sol->isToeplitzMatrix(matrix[0]),true);
	EXPECT_EQ(sol->isToeplitzMatrix(matrix[1]),false);
	EXPECT_EQ(sol->isToeplitzMatrix(matrix[2]),true);
	int a = 0;
	//bool flag = sol->isToeplitzMatrix(matrix[0]);
}

TEST(NumSmallerByFrequency,1)
{
	//vector <string> queries{ "bbb", "cc" }, words{ "a", "aa", "aaa", "aaaa" };
	vector <string> queries{ "cbd" }, words{ "zaaaz" };
	Solution *sol = new Solution();
	sol->numSmallerByFrequency(queries, words);
}

TEST(CountCharacters,1)
{
	vector<string> strin{ "cat","bt","hat","tree" };
	string charin{ "atach" };
	Solution *sol = new Solution();
	int res = sol->countCharacters(strin, charin);
}


TEST(MaxDistToClosest,1)
{
	vector<int> in{ 1,0,0,0,1,0,1 };
	vector<int> in1{ 1,0,0,0 };
	vector<int> in2{ 1,0,0,1 };
	vector<int> in3{ 0,0,1 };
	vector<int> in4{ 1,1,1,0,1,0,1,1,0,0,1 };
	Solution *sol = new Solution();
	//int res1 = sol->maxDistToClosest(in);
	//int res2 = sol->maxDistToClosest(in1);
	//int res3 = sol->maxDistToClosest(in2);
	//int res4 = sol->maxDistToClosest(in3);
	int res5 = sol->maxDistToClosest(in4);
}

TEST(Plus_One,Normal)
{
	vector<int> in{ 1,2,3,9 };
	vector<int> in1{ 0 };
	Solution *sol = new Solution();
	vector<int> res = sol->plusOne(in1);
}


TEST(Find_Pivot_Index,Normal)
{
	vector<int> in{ 1, 7, 3, 6, 5, 6 };
	vector<int> in1{ -1,-1,-1,-1,-1,0 };
	vector<int> in2{ -1,-1,-1,-1,-1,-1 };
	vector<int> in3{ -1,-1,-1,-1,0,1 };
	Solution *sol = new Solution();
	sol->pivotIndex(in3);
}


TEST(AddToArrayForm,Normal)
{
	vector<int> A{ 1,2,0,0 };
	Solution *sol = new Solution();
	vector<int> res = sol->addToArrayFormleet(A,34);
}

TEST(Maximum_Subarray,Normal)
{
	vector<int> in{ -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	vector<int> in1{ -2, 1 };
	vector<int> in2{ 1 , 2 };
	Solution *sol = new Solution();
	//int rst = sol->maxSubArray(in2);
	int rst = sol->maxSubArrayleetcode(in);
}

TEST(Occurrences_After_Bigram,Normal)
{
	string text = "alice is a good girl she is a good student";
	string first = "a";
	string second = "good";

	Solution *sol = new Solution();
	vector<string> rst = sol->findOcurrences(text, first,second);
}


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