#include<iostream>
#include<fstream>

using namespace std;

int n;
int **mat;
int count;

typedef struct node{
	int rank;
	node *parent = NULL;
}node;

node ***pointers;

void Make_set(node *head, int x){
	head->rank = 1;
	head->parent = head;
}

node *Find_set(node *head){
	node *temp = head->parent;
	while(temp != head){
		head = temp;
		temp = head->parent;
	}
	//cout<<temp->data;
	return temp;
}

void Union(node *head1, node *head2){
	if(head1->rank > head2->rank)
		head2->parent = head1;
	if(head1->rank < head2->rank)
		head1->parent = head2;
	if(head1->rank == head2->rank){
		head2->parent = head1;
		head1->rank += 1;
	}
}

int main(){

	fstream file;
	char filename[] = "input.txt";
	file.open(filename);
	file>>n;
	mat = (int **)malloc(n*sizeof(int *));
	pointers = (node ***)malloc(n*sizeof(node **));
	for(int i = 0; i < n; ++i){
		mat[i] = (int *)malloc(n*sizeof(int));
		pointers[i] = (node **)malloc(n*sizeof(node *));
	}
	for (int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			file>>mat[i][j];
	file.close();

	for (int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			node *head;
			head = (node *)malloc(sizeof(node));
			Make_set(head,mat[i][j]);
			pointers[i][j] = head;

			if(mat[i][j] == 1){
				if(j>0){
					if(mat[i][j-1] == 1)
						Union(Find_set(pointers[i][j-1]),Find_set(pointers[i][j]));
				}
				if(i>0){
					if(mat[i-1][j] == 1)
						Union(Find_set(pointers[i-1][j]),Find_set(pointers[i][j]));
				}
			}
		}
	}

	node *temp;
	int flag = 0;
	for(int i = 0; i < n; ++i){
		if(mat[n-1][i] == 1){
			temp = Find_set(pointers[n-1][i]);
			for(int j = 0; j < n; ++j){
				if(temp == pointers[0][j]){
					flag = 1;
					break;
				}
			}
		}
		if(flag)	break;
	}

	if(flag)	cout<<"Chip is valid";
	else cout<<"Chip Invalid";
	cout<<endl;
	
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j)
			cout<<mat[i][j]<<" ";
		cout<<endl;
	}
}