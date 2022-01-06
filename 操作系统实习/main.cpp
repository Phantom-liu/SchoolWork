#include "PageReplaceAlgorithm.h"
#include <time.h>
using namespace std;

//需要查看内存变化情况可稍微修改算法内部循环，类中提供一个showPageList打印内存信息

int main() {
	while (1) {
		srand(time(NULL));
		int memsize, reqsize;
		cout << "输入内存大小(1-500)和序列长度(1-10000)" << endl;
		cin >> memsize >> reqsize;
		PageReplaceAlgorithm test(memsize, reqsize);
		cout << "________________________________________" << endl;
		cout << endl << "完全随机的页请求序列：" << endl;
		test.generateRandomRequestSequence(0);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "具有时间局部性的序列：" << endl;
		test.generateRandomRequestSequence(-1);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "具有空间局部性的序列：" << endl;
		test.generateRandomRequestSequence(1);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
		cout << endl << "具有综合性质的序列：" << endl;
		test.generateRandomRequestSequence(2);
		test.showOPT();
		test.showLRU();
		test.showLFU();
		cout << "________________________________________" << endl;
	}
	return 0;
}

//CREATED BY LZZ 2022.1.5