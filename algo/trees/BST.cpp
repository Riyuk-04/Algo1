#include<iostream>
#include<fstream>

using namespace std;

typedef struct _treenode {

	int data ;
	struct _treenode * left = NULL;
	struct _treenode * right = NULL;
	struct _treenode * parent = NULL;
	
} BSTtreenode ;

typedef BSTtreenode * BSTtree ;

void Insert(int x,BSTtree root){
	BSTtree temp = root;
	BSTtree new1 = (BSTtree)malloc(sizeof(BSTtreenode));
	new1->data = x;

	while(1){
		if(x == temp->data){
			cout<<"ERROR :BST cannot contain repeated elements";
			exit(1);
		}

		if(x > temp->data){
			if(temp->right == NULL){
				new1->parent = temp;
				temp->right = new1;
				return;
			}
			else
				temp = temp->right;
		}

		if(x < temp->data){
			if(temp->left == NULL){
				new1->parent = temp;
				temp->left = new1;
				return;
			}
			else
				temp = temp->left;
		}
	}
}

int Successor(BSTtree root, int x){
	BSTtree temp = root;

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

void remove(BSTtree root, int x){
	BSTtree temp = root;
	BSTtree temp2;

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

void in_order_trav(BSTtree root){
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

	BSTtree root,temp;
	root = (BSTtree)malloc(sizeof(BSTtreenode));
	root->data = x;

	while (file >> x){
		Insert(x,root);
	}
	file.close();
    
    temp = root;
    cout<<"In order traversal: ";
    in_order_trav(temp);

    cout<<endl<<"Data to remove :";
    cin>>x;
    remove(root,x);
    cout<<"In order traversal: ";
    in_order_trav(temp);

    cout<<endl<<"Find successor of :";
    cin>>x;
    cout<<endl<<"Successor : "<<Successor(root,x)<<endl;


return 0;
}