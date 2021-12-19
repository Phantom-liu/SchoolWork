#include<iostream>
using namespace std;
class stack {
public:
	stack() {
		index = 0;
		memset(a, 0, sizeof a);
	}
	bool push(int value) {
		if (index < size) {
			a[index++] = value;
			return true;
		}
		else {
			cout << "stack overflow!!!" << endl;
			return false;
		}
	}
	int pop() {
		if(index>0)
		return a[--index];
		else {
			cout << "stack empty!!!" << endl;
			return -1;
		}
	}
private:
	int index;
	const int size = 100;
	int a[100];
};
const int NULLVALUE = 999999;
const int SIZE = 10;
class FifoTable {
public:
	FifoTable(int max, int min);   //结构函数，设置对象的max和min值。
	bool AddElement(int d);       //向队列加入一个元素d，成功返回真，否则返回假。如果队列满了，则新的值无法加入
	int GetElement();             //从队列头获取一个元素，并返回该元素值。如果队列为空，则返回NULLVALUE
private:int table[SIZE];   //存放队列数据的数组
		int tail;          //队列尾指针
		int head;          //队列头指针
		int max, min;       //队列元素的界，也就是如果加入队列的元素值大于max或者小于min，加入操作无法成功。
};
FifoTable::FifoTable(int max,int min):max(max),min(min) {
	memset(table, 0, sizeof table);
	tail = 1;
	head = 1;
}
bool FifoTable::AddElement(int d) {
	if (tail<10) {
		if (d<=max&&d>=min) {
			table[tail++] = d;
			return true;
		}
		else {
			//cout << "element not right!!!" << endl;
			return false;
		}
	}
	else {
		//cout << "queue overfolw!!!" << endl;
		return false;
	}
}
int FifoTable::GetElement() {
	if (head < tail) {
		return table[head++];
	}
	else {
		return NULLVALUE;
	}
}
int main()
{
	stack s1;
	int i;
	/*for (i = 1; i < 10; i++)
		s1.push(i);
	for (i = 1; i < 6; i++)
		cout << s1.pop() << ",";
	s1.push(200);
	cout << s1.pop() << endl;
	*/FifoTable ft(20, -2);
	for (i = -2; i <= 23; i++)ft.AddElement(i);
	for (i = 0; i < 9; i++)
		cout << ft.GetElement() << ",";
	cout << ft.GetElement() << endl;
}
