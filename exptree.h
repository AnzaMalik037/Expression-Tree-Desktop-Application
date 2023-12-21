#ifndef exptree_h
#define exptree_h
#include"node.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

struct exptree{
	
	void sound();
	void process_sound();
	void error_sound();
	void menu();
	
	void inputcheck(string);
	void get_infix_input();
	void create_list(char, int,int);
	bool validitycheck(string);
	int precidence(char);
	void display_dbll();
	void del_ll(node*);
	
	void printNode(double, tnode*);
	int heightOfTree(tnode*);
	void printBinaryTree(tnode*);
	
	void making_tree();	
	node* find_lowestprec();
	
	bool isoperator(char);	
	void numerics_in_tree(tnode*);
	void evaluation(tnode*);
};
#endif
