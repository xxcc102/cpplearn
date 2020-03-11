#include "timer.h"
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <map>
//#include <math>

namespace statictest
{
	void func_a(int a);
}

class statictest_c
{
public:
	statictest_c() {}
	~statictest_c() {}

	static void func_a(int a);
};



// Definition for a Node.
class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};



//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode() = default;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

 // Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr)
	 {

	 }
 };

class IntersectionTwoList {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
};




class BST {
public:
	//BST(int sz) :sizearray(sz) {}
	int GenTree(vector<int>&);
	TreeNode* increasingBST(TreeNode* root);
	int rangeSumBST(TreeNode* root, int L, int R);
private:
	//const int sizearray;
};

class Areaof3D{
public:
	int projectionArea(vector<vector<int>>& grid);
};



class MaxDepth {
public:
	int maxDepthofNtree(Node* root);
};


class Array_Kind {
public:
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2);
	vector<int> relativeSortArray_online(vector<int>& arr1, vector<int>& arr2);
};

class SetBits {
public:
	int countPrimeSetBits(int L, int R);
};


class Foo {
	std::mutex m1, m2;

public:
	Foo() {
		m1.lock();
		m2.lock();
	}

	void first(function<void()> printFirst) {
		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		m1.unlock();
	}

	void second(function<void()> printSecond) {
		m1.lock();
		m2.lock();
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		m2.unlock();
	}

	void third(function<void()> printThird) {
		m2.lock();
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
		m2.unlock();
	}
};


class MNode {
public:
	ListNode* middleNode(ListNode* head);
};



class BinarySearchSol
{
public:
	vector<int> twoSum(vector<int>& numbers, int target);
	int search(vector<int>& nums, int target);

protected:
private:
};

class HashTableSol
{
public:
	int repeatedNTimes(vector<int>& A);
	int islandPerimeter(vector<vector<int>>& grid);
	int singleNumber(vector<int>& nums);

	vector<int> intersection(vector<int>& nums1, vector<int>& nums2);

	vector<string> uncommonFromSentences(string A, string B);
protected:
private:
};


class LinkSol {

public:
	ListNode* reverseList(ListNode* head);
	ListNode* reverseList1(ListNode* head);
	void deleteNode(ListNode* node);
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
	ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2);
	ListNode* deleteDuplicates(ListNode* head);
	ListNode* deleteDuplicates1(ListNode* head);

	bool hasCycle(ListNode *head);

	bool isPalindrome(ListNode* head);

	ListNode* removeElements(ListNode* head, int val);
	ListNode* removeElements1(ListNode* head, int val);

	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);

	vector<int> nextLargerNodes(ListNode* head);
};



class MyLinkedList {
private:
	int my_len = 0;
	struct MyListNode
	{
		int val;
		MyListNode *pre;
		MyListNode *next;
		MyListNode(int x):val(x),pre(nullptr),next(nullptr) {}
	};
	MyListNode *head = nullptr;
	MyListNode *tail = nullptr;


public:
	/** Initialize your data structure here. */
	MyLinkedList() {
		
	}

	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	int get(int index) {
		if (index < 0 || index > my_len)
		{
			return -1;
		}
		MyListNode *cur = head;

		for (int cnt = 0 ; cnt < index ; cnt++)
		{
			cur = cur->next;
		}
		return cur->val;
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {
		if (my_len == 0)
		{
			head = new MyListNode(val);
			tail = head;
			my_len++;
		}
		else
		{
			MyListNode *cur = new MyListNode(val);
			cur->next = head;
			head->pre = cur;
			head = cur;
			my_len++;
		}
		return;
	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {
		if (my_len == 0)
		{
			head = new MyListNode(val);
			tail = head;
			my_len++;
		}
		else
		{
			MyListNode *cur = new MyListNode(val);
			tail->next = cur;
			cur->pre = tail;
			tail = cur;
			my_len++;
		}
		return;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {
		if (index < 0|| index >my_len)
		{
			return;
		}
		if (index == 0)
		{
			addAtHead(val);
			return;
		}
		if (index == my_len)
		{
			addAtTail(val);
			return;
		}
		MyListNode *cur = new MyListNode(val);
		MyListNode *tLocate = head;
		int i = 0;
		while (tLocate->next != NULL) {
			++i;
			if (i == index) {
				break;
			}

			tLocate = tLocate->next;
		}

		cur->next = tLocate->next;
		cur->pre = tLocate;
		tLocate->next = cur;
		cur->next->pre = cur;
		my_len++;
	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {
		if (index<0||index > my_len)
		{
			return;
		}
		MyListNode *tLocate = head;
		int i = 0;
		while (tLocate->next != NULL) {
			if (i == index) {
				break;
			}
			++i;
			tLocate = tLocate->next;
		}

		if (tLocate == head)
		{
			head = tLocate->next;
			if (head == nullptr)
			{
				tail == nullptr;
			}
			else
			{
				tLocate->next->pre = nullptr;
			}
		}
		else
		{
			tLocate->pre->next = tLocate->next;
			if (tLocate->next == nullptr)
			{
				tail = tLocate->pre;
			}
			else
			{
				tLocate->next->pre = tLocate->pre;
			}
		}
		my_len--;
		return;
	}
};


class Solution {
public:
	int lengthOfLongestSubstring(string s);

	vector<double> averageOfLevels(TreeNode* root);
	int heightChecker(vector<int>& heights);
	vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0);

	int maxSubArray(vector<int>& nums);
	int maxSubArrayleetcode(vector<int>& nums);

	vector<int> addToArrayForm(vector<int>& A, int K);
	vector<int> addToArrayFormleet(vector<int>& A, int K);

	int pivotIndex(vector<int>& nums);
	int pivotIndexleet(vector<int>& nums);

	vector<int> plusOne(vector<int>& digits);

	int maxDistToClosestleet(vector<int>& seats);
	int maxDistToClosest(vector<int>& seats);

	int countCharacters(vector<string>& words, string chars);

	vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words);

	bool isToeplitzMatrix(vector<vector<int>>& matrix);

	vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c);

	vector<string> findOcurrences(string text, string first, string second);
};
