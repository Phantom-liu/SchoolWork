#include<bits/stdc++.h>
using namespace std;
void swap(int arr[], int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}
//增量序列参考如下 (2^k-1,...,15,7,3,1)
//希尔排序最佳增量序列研究 -张连堂，张博 《韶关学院学报(自然科学版)》2005年06期 
void shellsort(int arr[], int l, int r) {
	int t = log2(r - l);
	while (t) {
		int d = (1 << t) - 1;
		for (int i = l; i <= r; i += d) {
			for (int j = i; j >= l + d; j -= d) {
				if (arr[j] < arr[j - d]) {
					swap(arr, j, j - d);
				}
				else {
					break;
				}
			}
		}
		t--;
	}
}
int main()
{
	srand(time(NULL));
	int a[105];
	for (int i = 0; i <= 100; i++) {
		a[i] = rand();
	}
	shellsort(a, 0, 100);
	for (int i = 0; i <= 100; i++) {
		cout << a[i] << " ";
	}
	return 0;
}