#include "PageReplaceAlgorithm.h"
#include <time.h>
using namespace std;

//��Ҫ�鿴�ڴ�仯�������΢�޸��㷨�ڲ�ѭ���������ṩһ��showPageList��ӡ�ڴ���Ϣ

int main() {
	while (1) {
		srand(time(NULL));
		int memsize, reqsize;
		cout << "�����ڴ��С(1-500)�����г���(1-10000)" << endl;
		cin >> memsize >> reqsize;
		PageReplaceAlgorithm test(memsize, reqsize);
		cout << "________________________________________" << endl;
		cout << endl << "��ȫ�����ҳ�������У�" << endl;
		test.generateRandomRequestSequence(0);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "����ʱ��ֲ��Ե����У�" << endl;
		test.generateRandomRequestSequence(-1);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "���пռ�ֲ��Ե����У�" << endl;
		test.generateRandomRequestSequence(1);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "�����ۺ����ʵ����У�" << endl;
		test.generateRandomRequestSequence(2);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
	}
	return 0;
}

//CREATED BY LZZ 2022.1.5