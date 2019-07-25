#include "leetcode.h"

ListNode *IntersectionTwoList::getIntersectionNode(ListNode *headA, ListNode *headB)
{
	ListNode *L = new ListNode(0);
	ListNode *r = L;
	
	while (headA && headB)
	{
		if (headA->val != headB->val)
		{
			headA = headA->next;
		}
		else
		{
			ListNode *tmp = headA;
			tmp->next = nullptr;
			r->next = headA;
			r = headA;
			headB = headB->next;
		}
	}
	L = L->next;
	return L;
}



int BST::GenTree(vector<int>&)
{

	return 0;
}


TreeNode* BST::increasingBST(TreeNode* root)
{
	//TreeNode root;

	if (root == nullptr)
	{
		return root;
	}


}


int BST::rangeSumBST(TreeNode* root, int L, int R)
{



	return 0;
}

int Areaof3D::projectionArea(vector<vector<int>>& grid)
{
	if (grid.empty())
	{
		return 0;
	}
	int left = 0, front = 0, bottom = 0;

	for (int i = 0 ; i < grid.size() ; i++)
	{
		int leftmax = 0,frontmax = 0;
		for (int j = 0 ; j < grid.at(i).size() ; j++)
		{
			if (grid.at(i).at(j))
			{
				bottom++;
				if (grid.at(i).at(j) > leftmax)
				{
					leftmax = grid.at(i).at(j);
				}
			}

			if (grid.at(j).at(i) > frontmax)
			{
				frontmax = grid.at(j).at(i);
			}
		}
		left += leftmax;
		front += frontmax;
	}

	return left + front + bottom;
}

int MaxDepth::maxDepthofNtree(Node* root)
{
	int count;
	if (root == nullptr)
	{
		return 0;
	}

	for (auto Node : root->children)
	{
		count = std::max(maxDepthofNtree(Node),count);
	}
	return count++;
}

vector<int> Array_Kind::relativeSortArray(vector<int>& arr1, vector<int>& arr2)
{
	vector<int> rst_arr;

	if (arr1.empty())
	{
		return rst_arr;
	}
	auto iter1 = arr1.begin();
	std::sort(arr1.begin(), arr1.end());

	if (arr2.empty())
	{
		return arr1;
	}

	for (auto find_mem : arr2)
	{
		while (iter1 !=  arr1.end())
		{
			if (*iter1 == find_mem)
			{
				rst_arr.emplace_back(*iter1);
				arr1.erase(iter1);
			}
			else
			{
				iter1++;
			}
		}
	}
	rst_arr.insert(rst_arr.end(),arr1.begin(),arr1.end());

}

vector<int> Array_Kind::relativeSortArray_online(vector<int>& arr1, vector<int>& arr2) {
	unordered_map<int, int> map;
	vector<int> tmp, res;
	for (int i = 0; i < arr2.size(); i++)
		map[arr2[i]] = 0;
	for (int i = 0; i < arr1.size(); i++) 
	{
		if (map.find(arr1[i]) != map.end()) 
			map[arr1[i]]++;
		else 
			tmp.push_back(arr1[i]);
	}
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < arr2.size(); i++)
	{
		for (int j = 0; j < map[arr2[i]]; j++) 
			res.push_back(arr2[i]);
	}
	for (int i = 0; i < tmp.size(); i++) 
		res.push_back(tmp[i]);
	return res;
}

int numbits(int num)
{
	int cnt = 0;
	while (num)
	{
		num &= (num - 1);
		cnt++;
	}
	return cnt;
}

bool IsPrime(int num)
{
	if (num == 1)
	{
		return false;
	}
	int div = 2;

	while ( div <= (num/2) )
	{
		if (num%div == 0)
		{
			return false;
		}
		div++;
	}
	return true;
}

int SetBits::countPrimeSetBits(int L, int R)
{
	int bitsnum = 0, rst_cnt = 0;
	for (int num = L ; num <= R ; num++)
	{
		//bitsnum = [](int num)
		//{	
		//	int cnt = 0;
		//	while (num)
		//	{
		//		num &= (num - 1);
		//		cnt++;
		//	}
		//	return cnt;
		//};
		bitsnum = numbits(num);

		if (IsPrime(bitsnum))
		{
			rst_cnt++;
		}
	}
	return rst_cnt;
}



//[](int bitnumin)mutable
//{
//	int div = 2;
//	while (div <= (bitnumin /= 2))
//	{
//		if (bitnumin%div == 0)
//		{
//			return false;
//		}
//	}
//	return true;
//};


ListNode* MNode::middleNode(ListNode* head)
{
	ListNode* onestep;
	onestep = head;
	ListNode* twostep;
	twostep = head;
	while (twostep)
	{
		twostep = twostep->next;
		if (twostep)
		{
			twostep = twostep->next;
		}
		else
		{
			break;
		}		
		onestep = onestep->next;
	}
	return onestep;
}


