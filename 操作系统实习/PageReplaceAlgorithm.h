#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <random>
#include <iomanip>

using namespace std;

#define MAX_MEMSIZE		500
#define MAX_REQSIZE		10000
//��Ҫ����MAX_REQSIZE �������дOPT�㷨�е�inMemory
#define PAGENUM_RANGE	10000	
#define TIME_RANDOM_RATE  0.6	//С��0.9
#define SPACE_RANDOM_RATE 0.7
#define INTERGRATED_RATE  SPACE_RANDOM_RATE*TIME_RANDOM_RATE


struct Page{
	int pageNum;	//ҳ��
	int count;		//��ʹ�õĴ���
	Page *next;
	Page *pre;
	Page(int pageNum, int count = 1){
		this->pageNum = pageNum;
		this->count = count;
		next = NULL;
		pre =NULL;	
	}
};

struct ResultBox{
	int hitTime = 0;
	int missTime = 0;
	double missRate = 0;
};

class PageReplaceAlgorithm{
public:
	PageReplaceAlgorithm(int memszie = 10, int reqsize = 400);
	// 0ģ��ȫ��� -1ģ��ʱ��ֲ��� 1ģ��ռ�ֲ��� 2ģ���ۺ����
	void generateRandomRequestSequence(int choose = 2);	
	void showLRU();
	void showLFU();
	void showOPT();
	void showPageList();
private:
	void printRes(ResultBox res);
	void clearPage();
	ResultBox LRU();
	ResultBox LFU();
	ResultBox OPT();
	void absoluteRandom();
	void timeLocality();
	void spaceLocality();
	void intergratedCondition();
	int memSize;
	int reqSize;
	int pageSize;
	Page *head;
	Page *tail;
	map<int, Page*> pageMap;
	vector<int> requestSequence;
};