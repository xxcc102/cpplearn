#include "timer.h"

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
	int rangeSumBST(TreeNode* root, int L, int R);
};

class Areaof3D{
public:
	int projectionArea(vector<vector<int>>& grid);
};



class MaxDepth {
public:
	int maxDepthofNtree(Node* root);
};