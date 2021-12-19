#include<iostream>
#include"avltree.h"
#include"avltree.cpp"
#include<cstdlib>
using namespace std;
int main() {
	avltree<string,int> map;
	map.insert("sss",1);
	map.insert("asada", 2);
	cout << map.find("asada");
	system("pause");
	return 0;
}
