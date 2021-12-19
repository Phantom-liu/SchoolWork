#include<iostream>
using namespace std;
//链表方法 O(nk)
int josephus_linkedlist(int n, int k) {
	struct list {
		int k;
		list *next;
		list(int k):k(k),next(nullptr){}
	};
	list *head = new list(1);
	list *tmp = head;
	for (int i = 2; i <= n; i++) {
		tmp->next = new list(i);
		tmp = tmp->next;
	}
	int cnt = n;
	tmp->next = head;
	tmp = head;
	while (cnt > 1) {
		for (int i = 1; i <= k - 2; i++) {
			tmp = tmp->next;
		}
		list *tmpnxt = tmp->next;
		tmp->next = tmp->next->next;
		delete tmpnxt;
		tmp = tmp->next;
		cnt--;
	}
	return tmp->k;
}
//数学推导 O(n)
int josephus_mathsolution(int n, int k) {
	int pre, now = 0;	//首先为了便于计算 我们将1-n映射至0-(n-1);
	// 我们考虑任意一个存活者在新的一轮游戏（报数）中的序号now 两种情况，i表示当前剩余人数:
	//		1.该人在上一轮中的序号大于上一轮死者的序号（例如上一轮3号死了，而此人为4号）
	//		那么该人在新的一轮中的序号为上一轮序号pre-k  (上轮3号死，那么k=4) (pre-k属于0到i-k)
	//		2.该人在上一轮中的序号小于上一轮死者的序号
	//		那么该人在新的一轮中的序号为上一轮序号pre-k+i+1 (将pre-k属于-k到-2范围内的部分映射至i-k+1到i-1 
	//															与1中的范围共同构成0到i-1的映射)
	//		综合分析可得now=(pre-k+i+1)%i   进而得到 pre=(now+k-i-1)%(i+1) 取正值 pre=(now+k)%(i+1);
	for (int i = 1; i <= n - 1; i++) {
		pre = (now + k) % (i + 1);
		now = pre;
	}
	return pre + 1;		//将0-(n-1)映射回1-n
}
int main() {
	cout << josephus_mathsolution(10, 3);
	return 0;
}
