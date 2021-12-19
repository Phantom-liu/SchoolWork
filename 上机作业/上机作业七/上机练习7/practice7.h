#pragma once
class circle
{
protected:
	double x, y;     //x和y表示为圆的圆心坐标 
	double r;       //r表示圆的半径
public:
	circle(double a, double b, double c) :x(a), y(b), r(c) {}//初始化圆的属性，a,b为圆心坐标，c为半径
	friend int relation(circle c1, circle c2);
};
class CStudent {
private:
	char stuno[20];    //学号
	char  name[20];    //姓名，用英语不考虑汉字
	int english;       //英语成绩（小于等于100，大于等于0，不在此范围按0分处理）
	int math;          //数学成绩（小于等于100，大于等于0，不在此范围按0分处理）
	int programe;      //程序设计成绩（小于等于100，大于等于0，不在此范围按0分处理）
	double avg;        //平均成绩，小数点后只取一位，其余部分四舍五入处理
public:
	CStudent();
	//计算平均成绩
	void getavg() {};
	//显示整个记录数据
	void print();
};