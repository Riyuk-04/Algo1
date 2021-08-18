#include<iostream>
#include<fstream>

using namespace std;

typedef struct _treenode {

	int data ;
	struct _treenode * left = NULL;
	struct _treenode * right = NULL;
	struct _treenode * parent = NULL;
	int balance_factor = 0;
	
} AVLtreenode ;

typedef AVLtreenode * AVLtree ;

void rotation_clock_same(AVLtree *root, AVLtree u){
	AVLtree head = u->parent;
	AVLtree v = u->left;
	AVLtree LL = v->left;
	AVLtree LR = v->right;	//can be null

	if(head == NULL){
		u->parent = v;
		v->parent = head;
		u->left = LR;
		if(LR != NULL)	LR->parent = u;
		v->right = u;
		u->balance_factor = 0;
		v->balance_factor = 0;
		*root = v;//cout<<"1";
	}
	else{
		if(head->right == u)
			head->right = v;
		else
			head->left = v;

		u->parent = v;
		v->parent = head;
		u->left = LR;
		if(LR != NULL)	LR->parent = u;
		v->right = u;
		u->balance_factor = 0;
		v->balance_factor = 0;//cout<<"a";
	}	
}

void rotation_clock_opp(AVLtree *root, AVLtree u){
	AVLtree head = u->parent;
	AVLtree v = u->left;
	AVLtree LL = v->left;	//can be null
	AVLtree w = v->right;
	AVLtree LRR = w->right;	//can be null
	AVLtree LRL = w->left;	//can be null

	if(head == NULL){
		u->parent = w;
		v->parent = w;
		w->parent = head;
		w->left = v;
		w->right = u;
		u->left = LRR;
		if(LRR != NULL)	LRR->parent = u;
		v->right = LRL;
		if(LRL != NULL)	LRL->parent = v;
		u->balance_factor = 1;
		v->balance_factor = 0;
		w->balance_factor = 0;
		*root = w;//cout<<"2";
	}
	else{
		if(head->right == u)
			head->right = w;
		else
			head->left = w;

		u->parent = w;
		v->parent = w;
		w->parent = head;
		w->left = v;
		w->right = u;
		u->left = LRR;
		if(LRR != NULL)	LRR->parent = u;
		v->right = LRL;
		if(LRL != NULL)	LRL->parent = v;
		u->balance_factor = 1;
		v->balance_factor = 0;
		w->balance_factor = 0;//cout<<"b";
	}
}

void rotation_anticlock_same(AVLtree *root, AVLtree u){
	AVLtree head = u->parent;
	AVLtree v = u->right;
	AVLtree RR = v->right;
	AVLtree RL = v->left;	//can be null

	if(head == NULL){
		u->parent = v;
		v->parent = head;
		u->right = RL;
		if(RL != NULL)	RL->parent = u;
		v->left = u;
		u->balance_factor = 0;
		v->balance_factor = 0;
		*root = v;//cout<<"3";
	}
	else{
		if(head->left == u)
			head->left = v;
		else
			head->right = v;

		u->parent = v;
		v->parent = head;
		u->right = RL;
		if(RL != NULL)	RL->parent = u;
		v->left = u;
		u->balance_factor = 0;
		v->balance_factor = 0;//cout<<"c";
	}
}

void rotation_anticlock_opp(AVLtree *root, AVLtree u){
	AVLtree head = u->parent;
	AVLtree v = u->right;
	AVLtree RR = v->right;	//can be null
	AVLtree w = v->left;
	AVLtree RLL = w->left;	//can be null
	AVLtree RLR = w->right;	//can be null

	if(head == NULL){
		u->parent = w;
		v->parent = w;
		w->parent = head;
		w->right = v;
		w->left = u;
		u->right = RLL;
		if(RLL != NULL)	RLL->parent = u;
		v->left = RLR;
		if(RLR != NULL)	RLR->parent = v;
		u->balance_factor = 1;
		v->balance_factor = 0;
		w->balance_factor = 0;
		*root = w;//cout<<"4";
	}
	else{
		if(head->left == u)
			head->left = w;
		else
			head->right = w;

		u->parent = w;
		v->parent = w;
		w->parent = head;
		w->right = v;
		w->left = u;
		u->right = RLL;
		if(RLL != NULL)	RLL->parent = u;
		v->left = RLR;
		if(RLR != NULL)	RLR->parent = v;
		u->balance_factor = 1;
		v->balance_factor = 0;
		w->balance_factor = 0;//cout<<"d";
	}
}

void Insert(int x,AVLtree *root){
	AVLtree temp = *root;
	AVLtree new1 = (AVLtree)malloc(sizeof(AVLtreenode));
	new1->data = x;

	while(1){
		if(x == temp->data){
			cout<<"ERROR :AVL cannot contain repeated elements";
			exit(1);
		}

		if(x > temp->data){
			if(temp->right == NULL){
				new1->parent = temp;
				temp->right = new1;
				temp = temp->right;
				break;
			}
			else
				temp = temp->right;
		}

		if(x < temp->data){
			if(temp->left == NULL){
				new1->parent = temp;
				temp->left = new1;
				temp = temp->left;
				break;
			}
			else
				temp = temp->left;
		}
	}
	while(temp->parent != NULL){
		if(temp->parent->left == temp){
			temp->parent->balance_factor--;
			temp = temp->parent;
			if(temp->balance_factor == 0)
				break;
			if(temp->balance_factor == -2 && temp->left->balance_factor == -1){
				//cout<<" "<<x;
				rotation_clock_same(root,temp);
				break;
			}
			if(temp->balance_factor == -2 && temp->left->balance_factor == 1){
				//cout<<" "<<x;
				rotation_clock_opp(root,temp);
				break;
			}
			continue;
		}
		if(temp->parent->right == temp){
			temp->parent->balance_factor++;
			temp = temp->parent;
			if(temp->balance_factor == 0)
				break;
			if(temp->balance_factor == 2 && temp->right->balance_factor == 1){
				//cout<<" "<<x;
				rotation_anticlock_same(root,temp);
				break;
			}
			if(temp->balance_factor == 2 && temp->right->balance_factor == -1){
				//cout<<" "<<x;
				rotation_anticlock_opp(root,temp);
				break;
			}
			continue;
		}
	}
	return;
}

int Successor(AVLtree root, int x){
	AVLtree temp = root;

	while(1){
		if(x == temp->data)
			break;

		if(x > temp->data)
			temp = temp->right;

		else
			temp = temp->left;
	}

	if(temp->right != NULL){
		temp = temp->right;
		while(temp->left != NULL)
			temp = temp->left;
		return temp->data;
	}

	while(temp->parent->left != temp){
		temp = temp->parent;
		if(temp->parent == NULL){
			cout<<x<<" has no Successor";
			exit(1);
		}
	}

	if(temp->parent->left == temp)
		return (temp->parent->data);
}

void remove(AVLtree *root, int x){
	AVLtree temp = *root;
	AVLtree temp2;

	while(1){
		if(x == temp->data){
			if(temp->left == NULL && temp->right == NULL){
				if(temp->parent->right == temp)
					temp->parent->right = NULL;
				else
					temp->parent->left = NULL;
				break;
			}

			if(temp->parent->left == temp){
				if(temp->right == NULL){
					temp->parent->left = temp->left;
					temp->left->parent = temp->parent;
					break;
				}
				else{
					temp2 = temp;
					temp->parent->left = temp->right;
					temp->right->parent = temp->parent;
					temp = temp->right;
					while(temp->left != NULL)
						temp = temp->left;
					if(temp2->left!=NULL){
						temp->left = temp2->left;
						temp2->left->parent = temp;
					}
					break;
				}
			}

			if(temp->parent->right == temp){
				if(temp->left == NULL){
					temp->parent->right = temp->right;
					temp->right->parent = temp->parent;
					break;
				}
				else{
					temp2 = temp;
					temp->parent->right = temp->left;
					temp->left->parent = temp->parent;
					temp = temp->left;
					while(temp->right != NULL)
						temp = temp->right;
					if(temp2->right!=NULL){
						temp->right = temp2->right;
						temp2->right->parent = temp;
					}
					break;
				}
			}
		}

		if(x > temp->data)
			temp = temp->right;

		else
			temp = temp->left;
	}
}

void in_order_trav(AVLtree root){
	if(root == NULL)
		return;

	in_order_trav(root->left);
	cout<<root->data<<" ";
	in_order_trav(root->right);
}

int main(){
	
	int x;

	fstream file;
	char filename[] = "bst.txt";
	file.open(filename);
	file>>x;

	AVLtree root,temp;
	root = (AVLtree)malloc(sizeof(AVLtreenode));
	root->data = x;

	while (file >> x){
		Insert(x,&root);
	}
	file.close();

    temp = root;
    cout<<"In order traversal: ";
    in_order_trav(temp);

    cout<<endl<<"Data to remove :";
    cin>>x;
    remove(&root,x);
    cout<<"In order traversal: ";
    in_order_trav(temp);

    cout<<endl<<"Find successor of :";
    cin>>x;
    cout<<endl<<"Successor : "<<Successor(root,x)<<endl;
return 0;
}