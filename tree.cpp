#include <iostream>
#include "treebio.h"
#include "md5bio.h"

node* tree::rotate_right(node * p) {
	node* q  = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

node* tree::rotate_left(node * q) {
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

unsigned char tree::check_height(node * p) {
	return p ? p->height : 0;
}

int tree::balance_factor(node * p) {
	return check_height(p->right) - check_height(p->left);
}

void tree::fix_height(node * p) {
	int hl = check_height(p->left);
	int hr = check_height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* tree::balance(node* p) // балансировка узла p
{
	fix_height(p);
	if (balance_factor(p) == 2) {
		if (balance_factor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	} 
	if (balance_factor(p) == -2) {
		if (balance_factor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p; // балансировка не нужна
}

void tree::set_node(const char * key, const char * value) {
	block block_ptr;
	block_ptr.key = key;
	block_ptr.value = value;
	block_ptr.hash = hash(key);

	node* node_ptr = new node(block_ptr);

	this->root = insert(this->root, node_ptr, block_ptr.hash);
	counter++;
}


node* tree::insert(node* p, node* input, DWORD k) // вставка узла input с ключем k в дерево с корнем p
{
	if (!p) {
		return input;
	}
	if (k < p->data.hash) {
		p->left = insert(p->left, input, k);
	} else  if (k > p->data.hash) {
		p->right = insert(p->right, input, k);
	} else { // if (k == p->data.hash)
		return p;
	}
	return balance(p);
}

// aaaaaaaaaaaaaaaaaaaaaaaaa

node* tree::findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

node* tree::removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* tree::remove(node* p, DWORD k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->data.hash)
		p->left = remove(p->left, k);
	else if (k > p->data.hash)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;

		this->counter--;
		return balance(min);
	}
	return balance(p);
}

void tree::del_node(const char * key) {
	DWORD h = hash(key);
	this->root = remove(this->root, h);
}

// aaaaaaaaa

const char * tree::get_node(const char * key) {
	DWORD h = hash(key);
	node* output = find_node(this->root, h);
	if (!output) {
		return nullptr;
	} else {
		return output->data.value;
	}
}

node * tree::find_node(node * p, DWORD h) {
	if (!p) {
		return nullptr;
	}
	if (p->data.hash == h) {
		return p;
	} else if (p->data.hash < h) {
		return find_node(p->right, h);
	} else {
		return find_node(p->left, h);
	}
}

// aaa

void tree::LKR() {
	LKR(this->root);
}

void tree::LKR(node * p) {
	if (!p)
		return;

	LKR(p->left);

	std::cout << "key: " << p->data.key << "; value: " << p->data.value << ";" << std::endl;

	LKR(p->right);
}
