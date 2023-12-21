#ifndef node_h 
#define node_h
#include<stdlib.h>


struct node{
	char info; //in case flag_ch=1
	int prec;
	int cnt;
	node *lchild;	//will be used as *next in dbll
	node *rchild;
};
struct tnode{
	char info;
	int operand_i;	//in case flag_ch=0 and data type choice is int
	double operand_d; //in case flag_ch=0 and data type choice is double 
	int cnt;
	tnode *lchild;
	tnode *rchild;
};
#endif
