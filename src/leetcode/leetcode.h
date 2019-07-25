#include "timer.h"
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <mutex>

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
     ListNode(int x) : val(x), next(NULL) {}
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