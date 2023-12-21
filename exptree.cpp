#include"exptree.h"
#include<iostream>
#include<stdlib.h>
#include <cmath>
#include <queue>
#include <climits>

#include <windows.h>
#include "MMSystem.h"

using namespace std;

string expr; 
int flag_ch;
string datatype;		
node *start=NULL;
tnode *root=NULL;	
	
void exptree::sound(){PlaySound(TEXT("start.wav"),NULL, SND_SYNC);}

void exptree::process_sound(){PlaySound(TEXT("processing.wav"),NULL, SND_SYNC);}

void exptree::error_sound(){PlaySound(TEXT("error.wav"),NULL, SND_SYNC);}

//void exptree::success(){PlaySound(TEXT("success.wav"),NULL, SND_SYNC);}

void exptree::menu(){
	cout<<"\n\t========================================\n";
	cout<<"\t DATA STRUCTURES AND ALGORITM\n\t Semester Project: Expression Tree";
	cout<<"\n\t========================================\n\n";
	cout<<"\n This Program accpets Infix Notation Expression with variables.";
	cout<<"\n\t========================\n\t========================";
	cout<<"\n\t | * : Multiplication |"<<"\n\t | / : Division       |"<<"\n\t | + : Addition       |";
	cout<<"\n\t | - : Subtraction    |"<<"\n\t | ^ : Power          |"<<"\n\t | % : Subtraction    |";
	cout<<"\n\t========================\n\t========================\n";
	//cout<<"\t | 0 : constant numeric expression |"<<"\n\t | 1 : Expression with variable    |\n\t=====================================\n";cin>>flag_ch;
	sound();
	get_infix_input();
}

void exptree::get_infix_input(){
	cout<<"\n\n Please enter infix notation expression : ";cin>>ws; getline(cin, expr);	
	inputcheck(expr);
	if(validitycheck(expr)==1){
		for (int i=0; i<expr.length(); i++){	
			create_list(expr[i],precidence(expr[i]),i+1);
		}
		//process_sound();
		display_dbll();
	}
}

void exptree::inputcheck(string str){
	char c;int flag;
	for (int i=0; i<str.length(); i++) {
		flag=1;c=str[i];
		if(c>='a' && c<='z' || c>='A' && c<='Z')flag=0;
        if (c=='+' || c=='-' || c=='/' || c=='*' || c=='%' || c=='^')flag=0;
        if(c=='%')flag_ch=3;	//double datatype choice disabler
        if(flag!=0){cout<<"\t>> ERROR INVALID EXPRESSION \n\t>> Please try again\n";error_sound();get_infix_input();}
    }
}

void exptree::create_list(char op, int prec,int count){
	node *q,*tmp;
	tmp=new(struct node);
	tmp->info=op;
	tmp->prec=prec;
	tmp->cnt=count;
	tmp->rchild=NULL;

	if(start==NULL){tmp->lchild=NULL;start=tmp;}
	else{
		q=start;
		while(q->rchild!=NULL)	q=q->rchild;
		q->rchild=tmp;
		tmp->lchild=q;
	}
}

int exptree::precidence(char opr){
	if(opr=='^'){return 1;}
	else if(opr=='*' || opr=='/' || opr=='%'){return 2;}
	else if(opr=='+' || opr=='-'){return 3;}
	else{return -1;}	
}

bool exptree::validitycheck(string str){
	int bracket_flag=0, len=str.length()-1;
	if(str[len]!=')'&&isalpha(str[len])==0){
		cout<<"\n\t>> INVALID EXPRESSION check operators\n";error_sound();get_infix_input();return 0;
	}
	for(int i=0;i<str.length();i++){
		if(str[i]=='('||str[i]==')'){
			bracket_flag++;
		}
		if(isalpha(str[i])==0){	// =0 : characters not alphabets
			if(precidence(str[i+1])!=-1 && precidence(str[i])!=-1){
				cout<<"\n\t>> INVALID EXPRESSION check operators\n";error_sound();get_infix_input();return 0;
			}
		}
	}
	if(bracket_flag%2!=0){cout<<"\n\t>> INVALID EXPRESSION check brackets\n";error_sound();get_infix_input();return 0;}
	if(bracket_flag==0){return 1;}	
}

void exptree::display_dbll(){
	node *q;
	int wcheck=0;
	if(start==NULL){cout<<"List is empty"<<endl;return;}
	q=start;
	cout<<" | expression is : ";
	while(q!=NULL)	{cout<<q->info<<" ";q=q->rchild;}	cout<<endl;
	//q=start;	cout<<" expression with precedence is : ";
	//while(q!=NULL){	cout<<q->info<<" ("<<q->prec<<") ";  q=q->rchild;}cout<<endl;	
	making_tree();
	del_ll(start);
	while(wcheck!=1){
	
	if (flag_ch!=3){	// double option disabled for %
		cout<<" | Enter data type of choice (int/db) for the numeric values: ";cin>>datatype;
	}

	else datatype="int";
	if(datatype=="int" || datatype=="db"){
		wcheck=1;
		numerics_in_tree(root);
		////////////////////////////////////display numeric treee function call here////////////////////////////////////
		evaluation(root);
		if(datatype=="int")		cout<<"\n\t | result : "<<root->operand_i<<" | \n";
		else		cout<<"\n\t | result : "<<root->operand_d<<" | \n"; //success();
		cout<<"\n  ========================================\n";
	}
	else{
		cout<<"\t>> invalid data type \n\t   options=(int/db)  :(\n\n\t  ENTER Again\n";error_sound();
		//exit(1);
	}		
}}

void exptree::making_tree(){
	node* q = find_lowestprec();
	
	if(q->info=='@'){	
		return;
	}
	tnode* w = new tnode();
	w->info = q->info;
    w->cnt=q->cnt;
    w->lchild = NULL;
    w->rchild = NULL;
	if (root == NULL) {
    	root=w;
    	//cout <<" root : " << root->info;    
	    q->info = '@'; // using as a flag to determine already in tree
	} else {
    	tnode *start1 = root;
    	while (start1 != NULL) {
        	if (q->cnt < start1->cnt) {
            	if (start1->lchild == NULL) {
                	start1->lchild=w;
	              //  cout<<endl<<" ("<<start1->info<<") "<<"left : "<<start1->lchild->info;
    	            break;
        	    }
            	start1 = start1->lchild;
	        } else {
    	        if (start1->rchild == NULL) {
        	        start1->rchild=w;
            	   // cout<<endl<<" ("<<start1->info<<") "<<"right : "<<start1->rchild->info;               
                	break;
            	}
            	start1 = start1->rchild;
       		}
    	}
    	q->info = '@';
	}
	making_tree();
}

node* exptree::find_lowestprec(){
	int max=0;
	int c=0;
	if(start==NULL){cout<<"List is empty"<<endl;return start;}
	node *q=start;
	max=start->prec;
	while(q!=NULL){	
		if(max<=q->prec && q->info!='@')	{
		max=q->prec;
		c=q->cnt;
		}
		q=q->rchild;
	}	
	q=start;
	while(q->cnt!=c && c!=0) {		q=q->rchild;	}
	if(c==0){
		cout<<"\n\n=====================================\n===========TREE======================\n";
		printBinaryTree(root); 
		cout<<"=====================================\n=====================================\n\n";
	}	
	return q;	
}

bool exptree::isoperator(char opr){
	return (opr=='*' || opr=='/' || opr=='%'|| opr=='^' || opr=='+' || opr=='-');
}

void exptree::printNode(double n, tnode* removed){
	for (; n > 0; n--) {cout << "  ";}
    if (removed == NULL) {cout << "  ";}
    else {cout << removed->info;}
}
 
int exptree::heightOfTree(tnode* root){
    if (root == NULL) {return 0;}
    return 1+max(heightOfTree(root->lchild),heightOfTree(root->rchild));
}
 
void exptree::printBinaryTree(tnode* root){
    queue<tnode*> treeLevel, temp;
    treeLevel.push(root);
    int counter = 0, height = heightOfTree(root) - 1;
    double numberOfElements = pow(2, (height + 1)) - 1, n;
    while (counter <= height) {
        tnode* removed = treeLevel.front();
        treeLevel.pop();
        if (temp.empty()) {
        	n=numberOfElements / pow(2, counter + 1);
            printNode(n,removed);
        }
        else {
        	n=numberOfElements / pow(2, counter);
            printNode(n,removed);
        }
        if (removed ==NULL) {
            temp.push(NULL);
            temp.push(NULL);
        }
        else {
            temp.push(removed->lchild);
            temp.push(removed->rchild);
        }
        if (treeLevel.empty()) {
            cout << endl<< endl ;	
            treeLevel = temp;
            while (!temp.empty()) {
                temp.pop();
            }
            counter++;
        }
    }
}


void exptree::numerics_in_tree(tnode *ptr){
	int op;
	if(ptr!=NULL){ 
		numerics_in_tree(ptr->lchild);
		if(isoperator(ptr->info)==0){
			if(datatype=="int"){
				cout<<" | Enter value for "<<ptr->info<<" : ";cin>>op;
				while (cin.fail())
    		{
		        cin.clear(); // clear input buffer to restore cin to a usable state
		        cin.ignore(INT_MAX, '\n'); // ignore last input
		        cout << "You can only enter numbers.\n";
		        cout << "Enter a number.\n";
		        cin >>op;
		        
   			 }ptr->operand_i=op;
				
			}
			else if(datatype=="db"){
				cout<<" | Enter value for "<<ptr->info<<" : ";cin>>ptr->operand_d;
			}sound();
		}
	numerics_in_tree(ptr->rchild);
	}
}

void exptree::evaluation(tnode *ptr){
	int n1,n2;
	double d1,d2;
	
	if(ptr!=NULL){
		evaluation(ptr->lchild);
		evaluation(ptr->rchild);
		if(isoperator(ptr->info)==1){
			switch (ptr->info){
				case '+':
					if(datatype=="int")		ptr->operand_i=ptr->lchild->operand_i+ptr->rchild->operand_i;
					else		ptr->operand_d=ptr->lchild->operand_d+ptr->rchild->operand_d;
					break;
				case '-':
					if(datatype=="int")		ptr->operand_i=ptr->lchild->operand_i-ptr->rchild->operand_i;
					else		ptr->operand_d=ptr->lchild->operand_d-ptr->rchild->operand_d;
					break;
				case '*':
					if(datatype=="int")		ptr->operand_i=ptr->lchild->operand_i*ptr->rchild->operand_i;
					else		ptr->operand_d=ptr->lchild->operand_d*ptr->rchild->operand_d;
					break;
				case '/':
					if(ptr->rchild->operand_i==0){cout<<"\t>> ERROR : division by zero (0)\n";error_sound();exit(1);
					}
					if(ptr->rchild->operand_d==0.0){cout<<"\t>> ERROR : division by zero (0)\n";error_sound();exit(1);
					}
					if(datatype=="int")		ptr->operand_i=ptr->lchild->operand_i/ptr->rchild->operand_i;
					else		ptr->operand_d=ptr->lchild->operand_d/ptr->rchild->operand_d;
					break;
				case '%':
					if(datatype=="int")		ptr->operand_i=ptr->lchild->operand_i%ptr->rchild->operand_i;
					break;
				case '^':
					if(datatype=="int")		ptr->operand_i=pow(ptr->lchild->operand_i,ptr->rchild->operand_i);
					break;
			}			
	    }
	}
}

void exptree::del_ll(node* n) {
    while (n != NULL) {
        node* next = n->rchild;
        delete n;
        n = next;
    }
}

