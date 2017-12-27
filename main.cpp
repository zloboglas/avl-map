#include <iostream>
#include <memory.h>
#include "treebio.h"
#include "md5bio.h"
#include <clocale>
#include <cstring>
#include <cstdio>
#include <stdio.h>

using namespace std;

void menu(tree* t);
void set_node(tree* t);
void get_node(tree* t);
void del_node(tree* t);

int main() {
	setlocale(LC_ALL, "rus");

	tree t;

	/*
	char* key_buffer[] = { "first key", "second key", "third key" };
	char* value_buffer[] = { "first value", "second value", "third value" };


	for (int i = 0; i < 3; i++) {
		t.set_node(key_buffer[i], value_buffer[i]);
	}
	*/

	for (;;) {
		menu(&t);
	}
	

	return 0;
}

void menu(tree* t) {
	cout << endl;
	cout << "¬ведите 1 дл€ того, чтобы создать элемент" << endl;
	cout << "¬ведите 2 дл€ того, чтобы найти элемент по ключу" << endl;
	cout << "¬ведите 3 дл€ того, чтобы  удалить элемент по ключу" << endl;
	cout << "¬ведите 4 дл€ Ћ ѕ обхода дерева" << endl;
	cout << "¬ведите 9 дл€ выхода из меню" << endl;

	int switch_on;
	cin >> switch_on;

	char c[1];
	gets_s(c);
	

	switch (switch_on) {
	case 1:
		set_node(t);
		break;
	case 2:
		get_node(t);
		break;
	case 3:
		del_node(t);
		break;
	case 4:
		t->LKR();
		break;
	default:
		return;
		break;
	}
}

void set_node(tree * t) {
	char key[40], value[40];
	cout << "¬ведите ключ: ";
	gets_s(key);
	cout << "¬ведите значение: ";
	gets_s(value);

	char* key_buffer = key;
	char* value_buffer = value;
	t->set_node(key_buffer, value_buffer);
	cout << "готово!" << endl;
}

void get_node(tree * t) {
	char key[40];
	cout << "¬ведите ключ: ";
	gets_s(key);

	char* key_buffer = key;

	cout << t->get_node(key_buffer) << endl;
}

void del_node(tree * t) {
	char key[40];
	cout << "¬ведите ключ: ";
	gets_s(key);

	char* key_buffer = key;

	t->del_node(key_buffer);
}



/*

first key
second key
third key

first value
second value
third value

first key
first value
*/
