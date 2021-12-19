#include<bits/stdc++.h>
using namespace std;
int arr[9][9];
int put[9][9];
int n;
int sum = 0;
bool judge(int len, int y, int a)
{
	if (arr[len][y] == 0)//不可以放
		return false;

	if (len == 0)//可以放皇后且为第一行
	{
		if (put[len][y] == 0)//没有放皇后
			return true;
	}
	else//不是第一行
	{
		for (int i = 0; i < len; i++)//遍历每一行
		{
			for (int j = 0; j < n; j++)//遍历每一列
			{
				if (put[i][j] == a)//如果是白棋或者黑棋
				{
					if (i == len || j == y || abs(i - len) == abs(j - y))//如果同一行同一列或同斜线
						return false;
				}
			}
		}
	}
	return true;
}
void search(int len)
{
	if (len == n)
	{
		sum++;
		return;
	}
	else
	{
		for (int i = 0; i < n; i++)//黑棋放的位置
		{
			if (judge(len, i, 1))
			{
				put[len][i] = 1;//放黑棋
				for (int j = 0; j < n; j++)
				{
					if (j != i && judge(len, j, 2))
					{
						put[len][j] = 2;//放白棋
						search(len + 1);
						put[len][j] = 0;//回溯
					}
				}
				put[len][i] = 0;//回溯
			}
		}
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			put[i][j] = 0;
			cin >> arr[i][j];
		}
	}
	search(0);
	cout << sum << endl;
}