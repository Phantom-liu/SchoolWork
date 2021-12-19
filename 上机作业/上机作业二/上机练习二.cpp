#include<bits/stdc++.h>
using namespace std;
//利用大整数类求指数较大的情况
typedef long long ll;
const int BASE = 1000000;
struct Bigint
{
	int s[20005];
	int cnt=0;
	Bigint(ll num = 0) { *this = num; }
	Bigint operator = (ll num)
	{
		int cntt = 0;
		do
		{
			s[cntt++]=(num%BASE);
			num /= BASE;
		} while (num > 0);
		cnt = cntt;
		return *this;
	}
	Bigint operator=(Bigint num) {
		memcpy(s, num.s,4*num.cnt);
		cnt = num.cnt;
		return *this;
	}
};
Bigint operator +(const Bigint &a, const Bigint &b)
{
	Bigint c;
	int cnt = 0;
	int alen =a.cnt, blen =b.cnt;
	for (int i = 0, g = 0;; i++)
	{
		if (g == 0 && i >= alen && i >= blen)break;
		int x = g;
		if (i < alen)x += a.s[i];
		if (i < blen)x += b.s[i];
		c.s[cnt++]=(x % BASE);
		g = x / BASE;
	}
	c.cnt = cnt;
	return c;
}

Bigint operator *(const Bigint &a, const Bigint &b)
{
	Bigint c;
	int cnt = 0;
	int alen =a.cnt, blen =b.cnt;
	for (int i = 0, g = 0;; i++)
	{
		if (i >= alen+blen - 1 && g == 0)break;
		ll sum = g;
		for (int j = max(0, i - blen + 1); j <= i && j < alen; j++) {
			sum += (ll)a.s[j] * (ll)b.s[i - j];
		}
		c.s[cnt++] = (sum % BASE);
		g = sum / BASE;
	}
	c.cnt = cnt;
	return c;
}
int sumall(int a) {
	int sum = 0;
	while (a) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}

int getpowerdsum(int a, int b) {
	Bigint res = a;
	Bigint ans = 1;
	while (b) {
		if (b & 1) {
			ans = ans * res;
		}
		res = res * res;
		b >>= 1;
	}
	int sum = 0;
	for (int i = 0; i < ans.cnt;i++)sum += sumall(ans.s[i]);
	return sum;
}
int main() {
	clock_t s = clock();
	cout << getpowerdsum(9, 50000) << endl;
	clock_t e = clock(); cout << e - s << endl;
	//cout << getpowerdsum(9, 10) << endl;
	return 0;
}
/* int c;
int res[3][3];
void muti(int a[][3], int b[][3]) {
	memset(res, 0, sizeof res);
	for (int i = 1; i <= 2; i++)
		for (int j = 1; j <= 2; j++)
			for (int k = 1; k<= 2; k++)
				res[i][j] += (a[i][k] * b[k][j])%c; //过程中取余数
	for (int i = 1; i <= 2; i++)
		for (int j = 1; j <= 2; j++)
			a[i][j] = res[i][j]%c;
}
int ans[3][3];
//矩阵快速幂
void martixpow(int a[][3],long long n) {
	ans[1][1] = ans[2][2] = 1;
	while (n) {
		if (n & 1) {
			muti(ans,a);
		}
		muti(a, a);
		n >>= 1;
	}
}
int main()
{
	long long n;
	cout<<"输入一个n（n<2^62）  输入一个素数c"<<endl;
	cin >> n >> c;
	int a[3][3];
	a[1][1]= 47, a[1][2] = 99, a[2][1] = 1, a[2][2] = 0; //二阶线性递推数列求通项的方法
	martixpow(a,n-1);
	cout << ans[1][1]<<endl;
	return 0;
} */