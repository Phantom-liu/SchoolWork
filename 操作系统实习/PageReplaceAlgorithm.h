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
//不要超过MAX_REQSIZE 否则需改写OPT算法中的inMemory
#define PAGENUM_RANGE	10000	
#define TIME_RANDOM_RATE  0.6	//小于0.9
#define SPACE_RANDOM_RATE 0.7
#define INTERGRATED_RATE  SPACE_RANDOM_RATE*TIME_RANDOM_RATE


struct Page{
	int pageNum;	//页号
	int count;		//被使用的次数
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
	// 0模拟全随机 -1模拟时间局部性 1模拟空间局部性 2模拟综合情况
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