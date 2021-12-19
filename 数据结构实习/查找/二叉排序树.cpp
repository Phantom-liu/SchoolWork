#include<bits/stdc++.h>
using namespace std;
struct BStree {
	int value;
	BStree* leftc;
	BStree* rightc;
	BStree(int a = 0) :value(a),leftc(nullptr), rightc(nullptr) {}
};
BStree *root; 
//二叉排序树 循环实现 
void insertBST(int value, BStree* head) {
	if(head==nullptr){
		root=new BStree(value);
		return; 
	} 
	BStree *p=nullptr;
	while (head != nullptr&&value != head->value) {
		p=head;
		if (value > head->value) {
			head = head->rightc;
		}
		else {
			head = head->leftc;
		}
	}
	if(head==nullptr){
		if(value>p->value)p->rightc=new BStree(value);
		else p->leftc=new BStree(value);
	}
}
void CreateBST(int* data, int n)
{
	for (int i = 0; i < n; i++) {
		insertBST(data[i], root);
	}
}
bool searchBST(int value, BStree* head) {
	while (head != nullptr&&value != head->value) {
		if (value > head->value) {
			head = head->rightc;
		}
		else {
			head = head->leftc;
		}
	}
	if (head != nullptr)return true;
	else return false;
}
bool removeBST(int value, BStree* head) {
	BStree *tmp;
	while (head != nullptr&&value != head->value) {
		tmp= head;
		if (value > head->value) {
			head = head->rightc;
		}
		else {
			head = head->leftc;
		}
	}
	if (head == nullptr)return false;
	if(head->leftc == nullptr && head->rightc == nullptr){
		head = nullptr;
		delete head;
	}
	else if (head->leftc == nullptr) {
		BStree *tmp = head;
		head = head->rightc;
		delete tmp;
	}
	else if (head->rightc == nullptr) {
		BStree *tmp = head;
		head = head->leftc;
		delete tmp;
	}
	else {	//找前驱或后继结点 这里我们用后继
		BStree *cur = head;
		head = head->rightc;
		BStree *p;
		while (head->leftc != nullptr) {
			p = head;
			head = head->leftc;
		}
		cur->value = head->value;
		delete p->leftc;
		p->leftc = head->rightc;
		head = cur;
	}
	//tmp为需要删除结点的父节点 head为处理好的子树根节点 
	if (value > tmp->value) {
		tmp->rightc = head;
	}
	else {
		tmp->leftc = head;
	}
	return true;
}
int main()
{
	int a[16];
	/* 0 -4 -8 -6 -4 0 6 14 */
	/* 				0
			 -4			6
		 -8		-6	 		14
	*/
	for (int i = 0; i < 8; i++)a[i] = i*i-5*i;
	CreateBST(a, 8);
//	cout<<searchBST(14,root)<<endl;  
	cout << root->value << endl;
	removeBST(-4,root);
	cout<<searchBST(-4,root)<<endl;
	//removeBST(11, root);
	return 0;
}
