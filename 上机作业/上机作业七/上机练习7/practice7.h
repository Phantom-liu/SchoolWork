#pragma once
class circle
{
protected:
	double x, y;     //x��y��ʾΪԲ��Բ������ 
	double r;       //r��ʾԲ�İ뾶
public:
	circle(double a, double b, double c) :x(a), y(b), r(c) {}//��ʼ��Բ�����ԣ�a,bΪԲ�����꣬cΪ�뾶
	friend int relation(circle c1, circle c2);
};
class CStudent {
private:
	char stuno[20];    //ѧ��
	char  name[20];    //��������Ӣ�ﲻ���Ǻ���
	int english;       //Ӣ��ɼ���С�ڵ���100�����ڵ���0�����ڴ˷�Χ��0�ִ���
	int math;          //��ѧ�ɼ���С�ڵ���100�����ڵ���0�����ڴ˷�Χ��0�ִ���
	int programe;      //������Ƴɼ���С�ڵ���100�����ڵ���0�����ڴ˷�Χ��0�ִ���
	double avg;        //ƽ���ɼ���С�����ֻȡһλ�����ಿ���������봦��
public:
	CStudent();
	//����ƽ���ɼ�
	void getavg() {};
	//��ʾ������¼����
	void print();
};