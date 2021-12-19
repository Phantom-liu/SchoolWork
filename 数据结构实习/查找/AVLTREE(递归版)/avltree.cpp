#include "avltree.h"
#include<algorithm>
using namespace std;
template<class KEY, class VALUE>
avltree<KEY, VALUE>::~avltree() {
	clear();
}
template<class KEY, class VALUE>
void avltree<KEY, VALUE>::clear() {
	node_size = 0;
	clear(root);
}
template<class KEY, class VALUE>
void avltree<KEY, VALUE>::clear(AVLTREE_NODE_PTR node) {
	if (node == nullptr) {
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}
template<class KEY, class VALUE>
int avltree<KEY, VALUE>::get_height() {
	return get_height(root);
}
template<class KEY, class VALUE>
int avltree<KEY, VALUE>::get_height(AVLTREE_NODE_PTR node) {
	if (node == nullptr) {
		return -1;
	}
	return node->height;
}
template<class KEY, class VALUE>
void avltree<KEY, VALUE>::insert(const KEY &key, const VALUE &value) {
	root = insert(root, key, value);
	return;
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::insert(AVLTREE_NODE_PTR cur, const KEY &key, const VALUE &value) {
	if (cur == nullptr) {
		cur = new AVLTREE_NODE(key, value);
		++node_size;
	}
	else if (key < cur->key) {
		cur->left = insert(cur->left, key, value);
		if (get_height(cur->left) - get_height(cur->right) == 2) {
			if (key < cur->left->key) {
				cur = rotateR(cur);
			}
			else {
				cur = rotateLR(cur);
			}
		}
	}
	else if (key > cur->key) {
		cur->right = insert(cur->right, key, value);
		if (get_height(cur->left) - get_height(cur->right) == -2) {
			if (key > cur->left->key) {
				cur = rotateL(cur);
			}
			else {
				cur = rotateRL(cur);
			}
		}
	}
	else {
		cur->value = value;
	}
	cur->height = max(get_height(cur->left), get_height(cur->right)) + 1;
	return cur;
}
template<class KEY, class VALUE>
void avltree<KEY, VALUE>::remove(const KEY &key) {
	root = remove(root, key);
	return;
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::remove(AVLTREE_NODE_PTR cur, const KEY &key) {
	AVLTREE_NODE_PTR tmp = nullptr;
	if (cur == nullptr) {
		return nullptr;
	}
	else if (key < cur->key) {
		cur->left = remove(cur->left, key);
	}
	else if (key > cur->key) {
		cur->right = remove(cur->right, key);
	}
	else if (cur->left&&cur->right) {
		tmp = find_min(cur->right);
		cur.key = tmp->key;
		cur->value = tmp->value;
		cur->right = remove(cur->right, cur->key);
	}
	else {
		tmp = cur;
		if (cur->left == nullptr) {
			cur = cur->right;
		}
		else if (cur->right == nullptr) {
			cur = cur->left;
		}
		delete tmp;
		node_size--;
	}
	if (cur == nullptr) {
		return cur;
	}
	int left_height = get_height(cur->left), right_height = get_height(cur->right);
	cur->height = max(left_height, right_height);
	if (left_height - right_height == 2) {
		if (get_height(cur->left->right) > get_height(cur->left->left)) {
			return rotateLR(cur);
		}
		else {
			return rotateR(cur);
		}
	}
	else if (right_height - left_height == 2) {
		if (get_height(cur->right->right) < get_height(cur->right->left)) {
			return rotateRL(cur);
		}
		else {
			return rotateL(cur);
		}
	}
	return cur;
}
template<class KEY, class VALUE>
VALUE avltree<KEY, VALUE>::find(const KEY &key) {
	AVLTREE_NODE_PTR tmp = find(root, key);
	if (tmp) {
		return tmp->value;
	}
	else {
		return VALUE();
	}
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::find(AVLTREE_NODE_PTR cur, const KEY &key) {
	if (cur == nullptr) {
		return nullptr;
	}
	else if (key < cur->key) {
		cur->left = find(cur->left, key);
	}
	else if (key > cur->key) {
		cur->right = find(cur->right, key);
	}
	else {
		return cur;
	}
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::find_min(AVLTREE_NODE_PTR cur) {
	if (cur == nullptr||cur->left==nullptr) {
		return cur;
	}
	return find_min(cur->left);
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::find_max(AVLTREE_NODE_PTR cur) {
	if (cur == nullptr || cur->right == nullptr) {
		return cur;
	}
	return find_min(cur->right);
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::rotateL(AVLTREE_NODE_PTR cur) {
	AVLTREE_NODE_PTR subR = cur->right;
	cur->right = subR->left;
	subR->left = cur;
	cur->height = max(get_height(cur->left), get_height(cur->right)) + 1;
	subR->height = max(get_height(subR->left), get_height(subR->right)) + 1;
	return subR;
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::rotateR(AVLTREE_NODE_PTR cur) {
	AVLTREE_NODE_PTR subL = cur->left;
	cur->left = subL->right;
	subL->right = cur;
	cur->height = max(get_height(cur->left), get_height(cur->right)) + 1;
	subL->height = max(get_height(subL->left), get_height(subL->right)) + 1;
	return subL;
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::rotateLR(AVLTREE_NODE_PTR cur) {
	cur->left = rotateL(cur->left);
	return rotateR(cur);
}
template<class KEY, class VALUE>
AVLTREE_NODE_PTR avltree<KEY, VALUE>::rotateRL(AVLTREE_NODE_PTR cur) {
	cur->right = rotateR(cur->right);
	return rotateL(cur);
}

