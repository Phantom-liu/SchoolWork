#include<iostream>
using namespace std;
const int maxn = 100000;
int prime[maxn], mark[maxn];
int index = 0;
void primeset(int n) {
	int cnt = 0;
	for (int i = 2; i <= n; i++)
	{
		if (!mark[i]) {
			prime[cnt++] = i;
		}
		for (int j = 0; j < cnt&&i*prime[j] <= n; j++)
		{
			mark[i*prime[j]] = 1;
			if (i%prime[j] == 0) {
				break;
			}
		}
	}
}
int factor(int n, int fac[])
{
	int k = n;
	for (int i = 0; i*i <= n; i++)
	{
		if (!mark[k]) {  //n只剩下一个质因数（较大）时，这样可减少循环次数
			fac[index++] = k;
			break;
		}
		while (k%prime[i] == 0) {
			fac[index++] = prime[i];
			k /= prime[i];
		}
		if (k == 1)break;
	}
	return index;
}
void Drawdiamond(int n)
{
	for (int i = 0; i < n; i++) {
		int k = abs(n - 2 * i - 1) / 2;
		int m = (2 * i + 1 >= n) ? 2 * n - 2 * i - 1 : 2 * i + 1;
		for (int j = k + m; j > 0; j--) {
			if (j <= m) {
				putchar('*');
				continue;
			}
			putchar('\0');
		}
		puts("");
	}
}
void main()
{
	//分解素因数
	int factorarr[maxn];
	cout << "输入一个正整数：" << endl;
	int n;
	cin >> n;
	primeset(n);
	int factorcnt = factor(n, factorarr);
	cout << "分解个数为：" << factorcnt << "\n";
	for (int i = 0; i < index; i++)cout << factorarr[i] << " ";
	puts("");
	//绘菱形
	Drawdiamond(17);
}
