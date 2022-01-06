#include "PageReplaceAlgorithm.h"

using namespace std;


PageReplaceAlgorithm::PageReplaceAlgorithm(int memsize, int reqsize) {
	if (memsize > MAX_MEMSIZE || reqsize > MAX_REQSIZE) {
		throw "INVALID SIZE";
	}
	memSize = memsize;
	reqSize = reqsize;
	pageSize = 0;
	head = NULL;
	tail = NULL;
}

// 0模拟全随机 -1模拟时间局部性 1模拟空间局部性
void PageReplaceAlgorithm::generateRandomRequestSequence(int choose) {
	switch (choose) {
	case 0:
		absoluteRandom();
		break;
	case -1:
		timeLocality();
		break;
	case 1:
		spaceLocality();
		break;
	case 2:
		intergratedCondition();
		break;
	default:
		cout << "无效的随机方式！" << endl;
	}
}

void PageReplaceAlgorithm::showLRU() {
	ResultBox res = LRU();
	cout << "LRU算法：" << endl;
	printRes(res);
}

void PageReplaceAlgorithm::showLFU() {
	ResultBox res = LFU();
	cout << "LFU算法：" << endl;
	printRes(res);
}

void PageReplaceAlgorithm::showOPT() {
	ResultBox res = OPT();
	cout << "OPT算法：" << endl;
	printRes(res);
}

void PageReplaceAlgorithm::showPageList() {
	Page *tmp = head;
	cout << "_____________________" << endl;
	cout << "内存：" << endl;
	cout << "页号" << "\t" << "次数" << endl;
	while (tmp) {
		cout << tmp->pageNum <<"\t"<<tmp->count << endl;
		tmp = tmp->next;
	}
	cout << "_____________________" << endl;
}

void PageReplaceAlgorithm::printRes(ResultBox res) {
	cout << "页命中次数：" << setw(5) << res.hitTime << "\t"
		<< "总请求次数：" << setw(5) << res.hitTime + res.missTime << "\t"
		<< "缺  页  率：" << setw(5) << res.missRate << "\t" << endl;
}

void PageReplaceAlgorithm::clearPage() {
	while (head != tail) {
		head = head->next;
		delete head->pre;
	}
	delete head;
	head = NULL;
	tail = NULL;
	pageSize = 0;
	pageMap.clear();
}

ResultBox PageReplaceAlgorithm::LRU() {
	clearPage();
	ResultBox res;
	Page *first = new Page(requestSequence[0]);
	pageMap[requestSequence[0]] = first;
	head = tail = first;
	pageSize++;
	res.missTime++;
	for (int i = 1; i < requestSequence.size(); i++) {
		int request = requestSequence[i];
		if (pageMap.count(request)) {
			(pageMap[request]->count)++;
			res.hitTime++;
			continue;
		}
		Page *page = new Page(request);
		if (pageSize < memSize) {
			head->pre = page;
			page->next = head;
			head = page;
			pageSize++;
		}
		else {
			Page *page = new Page(request);
			//替换最久未被使用的那页
			pageMap.erase(tail->pageNum);
			tail = tail->pre;
			delete tail->next;
			tail->next = NULL;
			page->next = head;
			head->pre = page;
			head = page;
		}
		res.missTime++;
		pageMap[request] = page;
	}
	res.missRate = (double)res.missTime / (res.missTime + res.hitTime);
	return res;
}

ResultBox PageReplaceAlgorithm::LFU() {
	clearPage();
	ResultBox res;
	Page *first = new Page(requestSequence[0]);
	pageMap[requestSequence[0]] = first;
	head = tail = first;
	pageSize++;
	res.missTime++;
	for (int i = 1; i < requestSequence.size(); i++) {
		int request = requestSequence[i];
		if (pageMap.count(request)) {
			Page *page = pageMap[request];
			(page->count)++;
			res.hitTime++;
			if (page == tail) {
				continue;
			}
			Page *tmp = page->next;
			//将count++后的page插入到适当位置
			while (tmp && page->count > tmp->count) {
				tmp = tmp->next;
			}
			//这里双向链表的插入写的比较繁琐----------------
			if(tmp && tmp != page->next){	
				if (page != head) {		//中间
					page->pre->next = page->next;
					page->next->pre = page->pre;
				}
				else {
					head = page->next;
					head->pre = NULL;
				}
				tmp->pre->next = page;
				page->pre = tmp->pre;
				page->next = tmp;
				tmp->pre = page;
			}
			else if (!tmp && head != tail) {	//尾
				if (page != head && page->next!=NULL) {
					page->pre->next = page->next;
				}
				else if(page->next != NULL){
					head = page->next;
					head->pre = NULL;
				}
				if (page->next != NULL) {
					page->next->pre = page->pre;
					page->next = NULL;
				}
				tail->pre->next = page;
				page->pre = tail->pre;
				tail = page;
			}
			continue;
			//----------------------------------------------
		}
		Page *page = new Page(request);
		if (pageSize < memSize) {
			head->pre = page;
			page->next = head;
			head = page;
			pageSize++;
		}
		else {
			//替换被使用次数最少的那页
			head->next->pre = page;
			page->next = head->next;
			pageMap.erase(head->pageNum);
			delete head;
			head = page;
		}
		res.missTime++;
		pageMap[request] = page;
	}
	res.missRate = (double)res.missTime / (res.missTime + res.hitTime);
	return res;
}

ResultBox PageReplaceAlgorithm::OPT() {
	clearPage();
	ResultBox res;
	Page *first = new Page(requestSequence[0]);
	pageMap[requestSequence[0]] = first;
	head = tail = first;
	pageSize++;
	res.missTime++;

	//页号范围离散的情况下最好用map
	//这里为了效率使用数组记录(OPT算法的复杂度实在太高)
	int inMemory[MAX_REQSIZE];
	memset(inMemory, 0, sizeof inMemory);
	inMemory[first->pageNum] = 1;
	int vis[MAX_REQSIZE];
	for (int i = 1; i < requestSequence.size(); i++) {
		int request = requestSequence[i];
		if (pageMap.count(request)) {
			res.hitTime++;
			(pageMap[request]->count)++;
			continue;
		}
		Page *page = new Page(request);
		if (pageSize < memSize) {
			tail->next = page;
			tail = page;
			pageSize++;
		}
		else {
			//替换将来最远才被使用的那页
			memset(vis, 0, sizeof vis);
			int findUsedCount = 0;
			for (int j = i + 1; j < reqSize; j++) {
				if (!vis[requestSequence[j]] && inMemory[requestSequence[j]]) {
					vis[requestSequence[j]] = 1;
					findUsedCount++;
				}
				if (findUsedCount == memSize - 1) {
					//当循环结束findUsedCount都小于MEMSIZE-1时，可任选vis未被置1的一页
					break;
				}
			}
			map<int, Page*>::iterator it;
			for (it = pageMap.begin(); it != pageMap.end(); it++) {
				Page *ele = it->second;
				if (!vis[ele->pageNum]) {
					//这是最远的那一页
					inMemory[ele->pageNum] = 0;
					pageMap.erase(it++);	//遍历容器时删除需迭代器++
					break;
				}
			}
		}
		inMemory[request] = 1;
		res.missTime++;
		pageMap[request] = page;
	}
	res.missRate = (double)res.missTime / (res.missTime + res.hitTime);
	return res;
}

//请求序列产生方式
void PageReplaceAlgorithm::absoluteRandom() {
	requestSequence.clear();
	for (int i = 0; i < reqSize; i++) {
		requestSequence.push_back(rand()%PAGENUM_RANGE);
	}
}

void PageReplaceAlgorithm::timeLocality() {
	requestSequence.clear();
	for (int i = 0; i < reqSize; i++) {
		double factor = (double)rand() / RAND_MAX;
		if (i < 10 || factor < TIME_RANDOM_RATE) {
			requestSequence.push_back(rand() % PAGENUM_RANGE);
		}
		else if (factor < 0.90) {
			int vsize = requestSequence.size();
			requestSequence.push_back(requestSequence[vsize - 1 - rand() % (vsize / 3 + 1)]);
		}
		else if (factor > 0.90 && factor < 0.95) {
			requestSequence.push_back(5);
		}
		else if (factor > 0.95 && factor < 0.97) {
			requestSequence.push_back(6);
		}
		else if (factor > 0.97 && factor < 0.99) {
			requestSequence.push_back(8);
		}
		else if (factor > 0.99) {
			requestSequence.push_back(9);
		}
		else {
			requestSequence.push_back(rand() % PAGENUM_RANGE);
		}
	}
}

void PageReplaceAlgorithm::spaceLocality() {
	requestSequence.clear();
	for (int i = 0; i < reqSize; i++) {
		double factor = (double)rand() / RAND_MAX;
		if (i < 10 || factor < SPACE_RANDOM_RATE) {
			requestSequence.push_back(rand() % PAGENUM_RANGE);
		}
		else {
			requestSequence.push_back(requestSequence.back());
		}
	}
}

void PageReplaceAlgorithm::intergratedCondition() {
	requestSequence.clear();
	for (int i = 0; i < reqSize; i++) {
		double factor = (double)rand() / RAND_MAX;
		if (i < 10 || factor < INTERGRATED_RATE) {
			requestSequence.push_back(rand() % PAGENUM_RANGE);
		}
		else if (factor > INTERGRATED_RATE && factor < 0.90) {
			requestSequence.push_back(requestSequence.back());
		}
		else if (factor < 0.90) {
			int vsize = requestSequence.size();
			requestSequence.push_back(requestSequence[vsize - 1 - rand() % (vsize / 3 + 1)]);
		}
		else if (factor > 0.90 && factor < 0.95) {
			requestSequence.push_back(5);
		}
		else if (factor > 0.95 && factor < 0.97) {
			requestSequence.push_back(6);
		}
		else if (factor > 0.97 && factor < 0.99) {
			requestSequence.push_back(8);
		}
		else if (factor > 0.99) {
			requestSequence.push_back(9);
		}
		else {
			requestSequence.push_back(rand() % PAGENUM_RANGE);
		}
		
	}
}