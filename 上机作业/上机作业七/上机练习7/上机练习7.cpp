#include<iostream>
#include"practice7.h"
using namespace std;
int relation(circle c1, circle c2) {
	if (c1.r == c2.r&&c1.x == c2.x&&c1.y == c2.y) {
		return 0;
	}
	double dis = (c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y);
	if (sqrt(dis) > c1.r + c2.r) {
		return 1;
	}
	else {
		return 2;
	}
}
void CStudent::print()
{
	cout << "学号：" << stuno << "  姓名：" << name << "  英语成绩：" << english << "  数学成绩：" << math << "  程序设计成绩" << programe << "  平均成绩";
	printf("%.1f\n", avg);
}
CStudent::CStudent() {
	cin >> stuno >> name >> english >> math >> programe;
	if (english < 0 || english>100)english = 0;
	if (math < 0 || math>100)math = 0;
	if (programe < 0 || programe>100)programe = 0;
	avg = (english + math + programe) / 3.0;
}
/*
1101001 zhangsan 85 69 89
1101002 lisi 75 89 77
1101003 wangwu 100 100 -89
*/
int main()
{
	circle c1(2, 2, 2);
	circle c2(29, 1, 2);
	circle c3(2, 2, 10);
	circle c4(0, 0, 0);
	circle c5(3, 4, 5);

	switch (relation(c1, c1))
	{
	case 0:
		cout << "overlapping" << endl;
		break;
	case 1:
		cout << "separate" << endl;
		break;
	case 2:
		cout << "intersect" << endl;
	}

	switch (relation(c2, c3))
	{
	case 0:
		cout << "overlapping" << endl;
		break;
	case 1:
		cout << "separate" << endl;
		break;
	case 2:
		cout << "intersect" << endl;
	}

	switch (relation(c4, c5))
	{
	case 0:
		cout << "overlapping" << endl;
		break;
	case 1:
		cout << "separate" << endl;
		break;
	case 2:
		cout << "intersect" << endl;
	}
	CStudent s[3];
	for (int i = 0; i < 3; i++)
	{
		s[i].getavg();
		s[i].print();
	}
	return 0;

}