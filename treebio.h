#pragma once

#include <iostream>
#include <stdint.h>
#include <string>
#include <memory.h>
#include "md5bio.h"


// using namespace std;

struct block {
	DWORD hash;
	const char * key;
	const char * value;
};

struct node {
	block data;
	int height;
	node* left;
	node* right;
	node(block k) {
		data = k;
		left = right = 0;
		height = 1;
	}
};



class tree {
	node* root = NULL;
	unsigned int counter = 0;

	node* balance(node* p);

	node* rotate_right(node* p); // правый поворот вокруг p
	node* rotate_left(node* q); // левый поворот вокруг q

	uint8_t check_height(node* p);
	int balance_factor(node* p);
	void fix_height(node* p);

	node* insert(node* p, node* input, DWORD k);
	node* findmin(node* p);
	node* removemin(node* p);
	node* remove(node* p, DWORD k);

	node* find_node(node* p, DWORD h);

	void LKR(node* p);
public:
	void set_node(const char *key, const char *value);
	const char* get_node(const char* key);
	void del_node(const char* key);
	
	void LKR();
};

