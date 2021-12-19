#pragma once
#define AVLTREE_NODE avltree_node<KEY,VALUE>
#define AVLTREE_NODE_PTR avltree_node<KEY,VALUE>*
template<class KEY, class VALUE>
class avltree_node {
public:
	KEY key;
	VALUE value;
	int height;
	AVLTREE_NODE_PTR left;
	AVLTREE_NODE_PTR right;
	avltree_node(const KEY &key = KEY(), const VALUE &value = VALUE()) :key(key), value(value), height(0),
		left(nullptr), right(nullptr) {}
};
template<class KEY, class VALUE>
class avltree {
public:
	avltree() :root(nullptr), node_size(0) {}
	~avltree();
	void insert(const KEY &key, const VALUE &value);
	void remove(const KEY &key);
	VALUE find(const KEY &key);
	AVLTREE_NODE_PTR get_root() { return root; }
	void clear();
	int get_height();
	int size() { return node_size; };
private:
	void clear(AVLTREE_NODE_PTR node);
	int get_height(AVLTREE_NODE_PTR node);
	//AVLTREE_NODE_PTR new_node(const KEY &key, const VALUE &value);
	AVLTREE_NODE_PTR insert(AVLTREE_NODE_PTR cur, const KEY &key, const VALUE &value);
	AVLTREE_NODE_PTR remove(AVLTREE_NODE_PTR cur, const KEY &key);
	AVLTREE_NODE_PTR find(AVLTREE_NODE_PTR cur, const KEY &key);
	AVLTREE_NODE_PTR rotateL(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR rotateR(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR rotateLR(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR rotateRL(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR find_min(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR find_max(AVLTREE_NODE_PTR cur);
	AVLTREE_NODE_PTR root;
	int node_size;
};