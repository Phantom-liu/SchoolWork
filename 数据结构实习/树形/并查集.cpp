#include<map>
#include<list>
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Unionfindset {
public:
	void makesets(vector<T> nodes)
	{
		fathermap.clear();
		sizemap.clear();
		for (auto node : nodes)
		{
			fathermap[node] = node;
			sizemap[node] = 1;
		}
	}

	//寻找代表结点，且路径压缩
	T finddeputy(T node)
	{
		T father = fathermap[node];
		if (father != node) {
			return finddeputy(father);
		}
		fathermap[node] = father;
		return father;
	}
	void Union(T a, T b)
	{
		T ahead = finddeputy(a);
		T bhead = finddeputy(b);
		if (ahead != bhead)
		{
			T asize = sizemap[a];
			T bsize = sizemap[b];
			if (asize < bsize)
			{
				fathermap[a] = b;
				sizemap[b] = bsize + asize;
			}
			else
			{
				fathermap[b] = a;
				sizemap[a] = bsize + asize;
			}
		}
	}

	bool issameset(T a, T b)
	{
		return finddeputy(a) == finddeputy(b);
	}

//private:
	map<T, T> fathermap;
	map<T, int> sizemap;
};

int main()
{
	vector<int> l;
	for (int i = 1; i < 10; i++)
	l.push_back(i);
	Unionfindset <int> lzz;
	lzz.makesets(l); 
	lzz.Union(3, 4);
	int s = lzz.finddeputy(l[4]);
	cout << lzz.finddeputy(4) << s << " ";
	cout << "\n" << lzz.sizemap[3];
	return 0;
}