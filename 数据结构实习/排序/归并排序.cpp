//归并排序
#include<bits/stdc++.h>
using namespace std;
/*void merge(vector<int> &s, const int &a, const int &l, const int &b)
{
	int c[100];
	int pa = a, pb = l + 1, pc = a;
	while (pa <= l && pb <= b) {
		c[pc++] = (s[pa] < s[pb]) ? s[pa++] : s[pb++];
	}
	while (pa <= l)c[pc++] = s[pa++];
	while (pb <= b)c[pc++] = s[pb++];
	for (int i = a; i <= b; i++)s[i] = c[i];
}*/
void mergesort(vector<int> &s,const int &a,const int &b)
{
	if (a < b) {
		int l = (a + b) / 2;
		mergesort(s, a, l);
		mergesort(s, l + 1, b);
		/*merge(s, a, l, b);*/
		//可将过程函数都写在一起（然并卵）
		int c[100];
		int pa = a, pb = l + 1, pc = a;
		while (pa <= l && pb <= b) {
			c[pc++] = (s[pa] < s[pb]) ? s[pa++] : s[pb++];
		}
		while (pa <= l)c[pc++] = s[pa++];
		while (pb <= b)c[pc++] = s[pb++];
		for (int i = a; i <= b; i++)s[i] = c[i];
	}
}
int main()
{
	srand(15);
	vector<int> lzz; 
	for (int x = 0; x < 10; x++)
	{
		lzz.clear();
		for (int i = 0; i < 10; i++) lzz.push_back(rand() % 95);
		mergesort(lzz, 3, 9);
		for (int i = 0; i < 10; i++)cout << lzz[i] << "	";
		cout << endl;
	}
	return 0;
}