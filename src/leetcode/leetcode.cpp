#include "leetcode.h"
#include <algorithm>
#include <queue>
#include <sstream>
#include <set>
#include <unordered_set>
//void FFTextStream ::
//formattedGetLine(std::string& line,
//	const bool expectEOF)
//{
//
//		std::getline(*this, line);
//		// Remove CR characters left over in the buffer from windows files
//		if (line.size() == 0)
//			return;
//		while (*line.rbegin() == '\r')
//			line.erase(line.end() - 1);
//		for (int i = 0; i < line.length(); i++)
//			;
//}

int Solution::lengthOfLongestSubstring(string s)
{




	return 0;
}

int BinarySearchSol::search(vector<int>& nums, int target)
{
	int cur = 0,len = nums.size(),cnt = 0;
	while (1)
	{

		if (cnt == len)
		{
			break;
		}
		if (nums[cur] == target)
		{
			return cur;
		}
		else if (nums[cur] < target)
		{
			cur = (cur + len) / 2;
		}
		else
		{
			cur = cur / 2;
		}
		cnt++;
	}
	return -1;
}


vector<int> BinarySearchSol::twoSum(vector<int>& numbers, int target)
{
	vector<int> res;
	int sum = 0, len = numbers.size() - 1, index1 = 0, index2 = len - 1;
	sum = numbers[index1] + numbers[index2];
	for (int i = 0 ; i < len; i++)
	{
		if (sum < target)
		{
			index1++;
		}
		else if (sum > target)
		{
			index2--;
		}
		else if (sum == target)
		{
			break;
		}
		sum = numbers[index1] + numbers[index2];
	}
	res.push_back(index1 + 1);
	res.push_back(index2 + 1);
	return res;
}

vector<string> HashTableSol::uncommonFromSentences(string A, string B)
{
	vector<string> res;
	


	return res;
}

int HashTableSol::singleNumber(vector<int>& nums)
{
	int rst = 0;
	for (auto num:nums)
	{
		rst ^= num;
	}
	return rst;
}
vector<int> HashTableSol::intersection(vector<int>& nums1, vector<int>& nums2)
{
	set<int> setres;

	for (auto num:nums1)
	{
		for (auto n : nums2)
		{
			if (n == num)
			{
				setres.insert(n);
			}
		}
	}

	vector<int>res(setres.begin(), setres.end());
	return res;
}

int HashTableSol::islandPerimeter(vector<vector<int>>& grid)
{
	int total = 0;
	int sumcommon = 0;
	for (int k = 0; k < grid.size(); k++)
	{
		
		for (int n = 0;n < grid[k].size();n++)
		{
			if (grid[k][n] == 1)
			{
				total++;
				if ( n>0 && grid[k][n] == grid[k][n-1])
				{
					sumcommon++;
				}
				if ( k>0 && grid[k][n] == grid[k-1][n])
				{
					sumcommon++;
				}
			}
		}

	}

	return total*4-sumcommon*2;
}


int HashTableSol::repeatedNTimes(vector<int>& A)
{
	std::unordered_multiset<int> B;

	for (auto iter = A.begin();iter != A.end();iter++)
	{
		if (B.count(*iter)== 2)
		{
			return *iter;
		}
		B.insert(*iter);
	}
}


vector<int> LinkSol::nextLargerNodes(ListNode* head)
{
	vector<int> res;
	int tmpmax = 0;
	if (head == nullptr)
	{
		return res;
	}
	ListNode *cur = head;
	
	while (cur->next)
	{
		if (cur->next)
		{

		}
	}

	return res;
}

bool check(ListNode*& head, ListNode* p) {
	if (!p) { return true; }
	bool isPal = check(head, p->next);
	if (head->val != p->val) {
		return false;
	}
	head = head->next;
	return isPal;
}

void iterfunc(ListNode* p)
{
	if (!p)
	{
		return;
	}
	iterfunc(p->next);
}

ListNode *LinkSol::getIntersectionNode(ListNode *headA, ListNode *headB)
{
	ListNode *p1 = headA;
	ListNode *p2 = headB;

	if (p1 == nullptr || p2 == nullptr)
	{
		return nullptr;
	}

	while (p1 && p2 && p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;

		if (p1 == p2)
		{
			return p1;
		}

		if (p1 == nullptr)
		{
			p1 = headB;
		}
		if (p2 == nullptr)
		{
			p2 = headA;
		}
	}

	return p1;
}


//list作为中间变量
ListNode* LinkSol::removeElements1(ListNode* head, int val)
{
	ListNode **list = &head;
	while (*list != nullptr)
	{
		if ((*list)->val == val)
		{
			*list = (*list)->next;
		}
		else
		{
			list = &(*list)->next;
		}
	}
	return head;
}

ListNode* LinkSol::removeElements(ListNode* head, int val)
{
	while (head)
	{
		if (head->val == val)
			head = head->next;
		else
			break;
	}

	if (head == nullptr)
	{
		return nullptr;
	}

	ListNode *cur = head;

	while (cur->next !=nullptr)
	{
		if (cur->next->val == val)
		{
			cur->next = cur->next->next;
		}
		else
		{
			cur = cur->next;
		}
	}

	return head;
}



bool LinkSol::isPalindrome(ListNode* head)
{
	return check(head, head);
}

bool LinkSol::hasCycle(ListNode *head)
{
	if (head == nullptr || head->next == nullptr)
	{
		return false;
	}  

	ListNode *slow = head, *fast = head;
	while ( fast->next != nullptr && fast->next->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow->val == fast->val)
		{
			return true;
		}
	}
	return false;
}



ListNode * LinkSol::deleteDuplicates1(ListNode *head) {
	ListNode*cur = head, *tail = head;
	while (cur) {
		if (cur->val != tail->val) {
			tail->next = cur;
			tail = cur;
		}
		cur = cur->next;
		tail->next = NULL;
	}
	return head;
}


ListNode* LinkSol::deleteDuplicates(ListNode* head)
{
	ListNode *cur = head;

	while (cur->next != nullptr)
	{
		if(cur->val == cur->next->val)
		{
			cur->next = cur->next->next;
		}
		else
		{
			cur = cur->next;
		}
	}
	return head;
}


ListNode* LinkSol::mergeTwoLists1(ListNode* l1, ListNode* l2)
{
	ListNode dummy(0);
	ListNode *rst = &dummy;

	while (l1 && l2)
	{
		ListNode *&node = l1->val < l2->val ? l1 : l2;
		rst->next = node;
		rst = rst->next;
		node = node->next;
	}
	rst->next = l1 ? l1 : l2;
	return dummy.next;
}


ListNode* LinkSol::mergeTwoLists(ListNode* l1, ListNode* l2)
{
	if (l1==nullptr)
	{
		return l2;
	}
	if (l2 == nullptr)
	{
		return l1;
	}

	if (l1->val <= l2->val )
	{
		l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	}
	else
	{
		l2->next = mergeTwoLists(l1, l2->next);
		return l2;
	}
}


void statictest::func_a(int a)
{
	cout << a << endl;
}

void statictest_c::func_a(int a)
{
	cout << a << endl;
}




ListNode* LinkSol::reverseList(ListNode* head)
{
	ListNode *pre = new ListNode(0), *cur = head;
	pre->next = head;
	while (cur && cur->next) {
		ListNode* temp = pre->next;
		pre->next = cur->next;
		cur->next = cur->next->next;
		pre->next->next = temp;
	}
	return pre->next;
}

ListNode* LinkSol::reverseList1(ListNode* head)
{
	if (!head || !(head->next)) 
	{
		return head;
	}
	ListNode* node = reverseList1(head->next);
	head->next->next = head;
	head->next = NULL;
	return node;
}
void LinkSol::deleteNode(ListNode* node)
{
	auto next = node->next;
	node = next;
	delete next;
}


vector<vector<int>> Solution::matrixReshape(vector<vector<int>>& nums, int r, int c)
{
	int m = nums.size(), n = nums[0].size();
	if (r * c != m * n)
		return nums;
	vector<vector<int>> res(r, vector<int>(c, 0));
	for (int i = 0; i < r * c; i++)
		res[i / c][i%c] = nums[i / n][i%n];
	return res;
}

bool Solution::isToeplitzMatrix(vector<vector<int>>& matrix)
{
	int col = matrix.at(0).size() ,row = matrix.size();

	for (int i = 1; i < row; i++)
	{
		for (int j = 1;j < col; j++ )
		{
			if (matrix[i][j] != matrix[i - 1][j - 1])
				return false;
		}
	}

	return true;
}

vector<int> get_cnt(vector<string>& words)
{
	vector<int> words_v;
	
	for (auto w : words)
	{
		multiset<int> charcnt;
		vector<int> cntchar;

		for (auto c : w)
		{
			int cnt = c - 'a';
			charcnt.insert(cnt);
			cntchar.push_back(cnt);
		}
		sort(cntchar.begin(), cntchar.end());
		words_v.push_back(charcnt.count(*cntchar.begin()));
	}
	//reverse(words_v.begin(), words_v.end());
	return words_v;
}

vector<int> Solution::numSmallerByFrequency(vector<string>& queries, vector<string>& words)
{
	vector<int> res;
	vector<int> q_v = get_cnt(queries);
	vector<int> w_v = get_cnt(words);
	for (auto q : q_v)
	{
		int rescnt = 0;
		for (auto w : w_v)
		{
			if (q < w)
			{
				rescnt++;
			}
		}
		res.push_back(rescnt);
	}

	return res;
}

int Solution::countCharacters(vector<string>& words, string chars)
{
	vector<int> charcnt(26), tmpchar;
	int res = 0;
	bool flag = true;

	for (auto c:chars)
	{
		++charcnt[c - 'a'];
	}
	for (auto w:words)
	{
		tmpchar = charcnt;
		flag = true;
		for (auto ch:w)
		{
			if (--tmpchar[ch - 'a'] < 0)
			{
				flag = false;
			}
		}
		if (flag)
		{
			res += w.size();
		}
	}
	return res;
}


int Solution::maxDistToClosest(vector<int>& seats)
{
	int res = 0, n = seats.size(), last = 0,first= 0, pre = 1,tmpres = 0;
	for (int i = 0 ; i < n ; i++)
	{
		if (seats[i] == 0)
		{
			if (pre == 0)
			{
				tmpres++;
			}		
		}
		else
		{
			if (i == (tmpres+1)&&seats[0]==0)
			{
				first = i;
			}
			last = i;
			res = max(res, tmpres + 1);
			tmpres = 0;
		}
		pre = seats[i];
	}

	res = max(max((res + 1)/2, n - last - 1), first);
	return res;
}

int Solution::maxDistToClosestleet(vector<int>& seats)
{
	int res = 0, n = seats.size(), last = -1;
	for (int i = 0; i < n; ++i) {
		if (seats[i] == 1) {
			res = last < 0 ? i : max(res, (i - last) / 2);
			last = i;
		}
	}
	res = max(res, n - last - 1);
	return res;
}

vector<int> Solution::plusOne(vector<int>& digits)
{
	int tmp = 1;
	for (int num = digits.size()-1;num >= 0 ;--num)
	{
		digits[num] += tmp;
		tmp = digits[num] / 10;
		digits[num] %= 10;
	}
	
	if (tmp != 0)
	{
		digits.insert(digits.begin(), tmp);
	}

	return digits;
}

int Solution::pivotIndexleet(vector<int>& nums)
{

	int total = 0;
	for (int num : nums) total += num;
	int sum = 0;
	for (int i = 0; i < nums.size(); sum += nums[i++])
		if (sum * 2 == total - nums[i])
			return i;

	return -1;
}


int Solution::pivotIndex(vector<int>& nums)
{
	int sum_l = 0, sum_r = 0;
	if (nums.empty())
	{
		return -1;
	}

	//低效率方式
	//for (int pos = 0 ; pos < nums.size() ; pos++)
	//{
	//	sum_l = 0;
	//	sum_r = 0;
	//	for (int lf = 0; lf <pos; lf++)
	//	{
	//		sum_l += nums[lf];
	//	}
	//	for (int rt = pos + 1; rt < nums.size() ; rt++)
	//	{
	//		sum_r += nums[rt];
	//	}
	//	if (sum_l == sum_r)
	//	{
	//		return pos;
	//	}
	//}
	
	//前后同时遍历
	int end = nums.size() - 1;
	int endstep = 0;
	for (int beg = 0 ; beg < nums.size() - 1; )
	{
		if (beg > end)
		{
			return -1;
		}
		if (abs(sum_l) <= abs(sum_r))
		{
			sum_l += nums[beg];
			beg++;
		}
		if (abs(sum_l) > abs(sum_r))
		{
			sum_r += nums[end];
			end--;
		}
		if (sum_r == sum_l && beg == end )
		{
			return beg;
		}
	}
	return -1;
}

vector<int> Solution::addToArrayFormleet(vector<int>& A, int K) 
{
	for (int i = A.size() - 1; i >= 0 && K > 0; --i) {
		A[i] += K;
		K = A[i] / 10;
		A[i] %= 10;
	}
	while (K > 0) {
		A.insert(A.begin(), K % 10);
		K /= 10;
	}
	return A;
}


vector<int> Solution::addToArrayForm(vector<int>& A, int K) 
{
	vector<int> res;
	vector<int> carrybit;
	vector<int> K_from;
	while (K)
	{
		K_from.push_back(K%10);
		K = K / 10;
	}
	reverse(K_from.begin(), K_from.end());


	return res;
}

int Solution::maxSubArrayleetcode(vector<int>& nums)
{
	int sum = nums[0], maxsum = nums[0];
	for (int i = 1; i < nums.size(); i++) {
		//求解所取最后一个元素和其之前的元素的最大最情况
		sum = max(nums[i], sum + nums[i]);
		maxsum = max(maxsum, sum);
	}
	return maxsum;
}


int Solution::maxSubArray(vector<int>& nums) 
{
	int rst = nums.at(0);
	int sum = 0;

	for (int size = 1;size <= nums.size(); size++)
	{
		for (int pos = 0; pos <= nums.size()- size ; pos++)
		{
			sum = 0;
			for (int len = 0 ,beg = pos; len < size; len++,beg++)
			{
				sum += nums.at(beg);
			}

			if (sum > rst)
			{
				rst = sum;
			}
		}
	}
	return rst;
}


vector<string> Solution::findOcurrences(string text, string first, string second) {
		istringstream in(text);
		vector<string> res;
		string s, x = "", y = "";
		while (in >> s) {
			if (x == first && y == second && s != "") 
				res.push_back(s);
			x = y;
			y = s;
		}
		return res;
}


vector<double> Solution::averageOfLevels(TreeNode* root) {
	vector<double> rst_list;
	queue<TreeNode*> binq;
	int sum = 0;

	binq.push(root);

	while (!binq.empty())
	{
		int size = binq.size();
		int cnt = size;
		long sum = 0;
		while (size--) 
		{
			TreeNode* tmp = binq.front();
			binq.pop();
			sum += tmp->val;
			if (tmp->left)
				binq.push(tmp->left);
			if (tmp->right)
				binq.push(tmp->right);
		}
		rst_list.push_back((double)sum / (double)cnt);
	}
	return rst_list;
}



int Solution::heightChecker(vector<int>& heights)
{
	int pre = 0;
	int cnt = 0;
	if (heights.empty())
	{
		return 0;
	}
	vector<int> heights1 = heights;


	sort(heights1.begin(), heights1.end());

	auto iter = heights.begin();
	auto iter1 = heights1.begin();
	for (;iter!= heights.end();iter++,iter1++)
	{
		if (*iter != *iter1)
		{
			cnt++;
		}
	}
	return cnt;
}



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
	TreeNode *rst;

	if (root == nullptr)
	{
		return root;
	}

	return rst;
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



//vector<vector<int>> Solution::allCellsDistOrder(int R, int C, int r0, int c0)
//{
//	int dist;
//	map<int, vector<int,int>> order_dist;
//	vector<vector<int>> v_dist;
//	vector<int, int> pair_pos;
//
//	for (int i = 0; i <= R; i++)
//	{
//		for (int j = 0; j <= C; j++)
//		{
//			dist = abs(i - r0) + abs(j - c0);
//			pair_pos.first = i;
//			pair_pos.second = j;
//			order_dist[dist] = pair_pos;
//		}
//	}
//
//	for (auto iter_dist = order_dist.begin();iter_dist != order_dist.end();iter_dist++)
//	{
//		iter_dist->second();
//	}
//
//
//	return;
//}