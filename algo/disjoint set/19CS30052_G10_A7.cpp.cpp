/* Use command line to pass the values of n and m as argv strings
   Use the following commands to run the file:
   ./a.out 19CS30052_G10_A7.cpp 5 6
   or
   ./19CS30052_G10_A7.cpp 5 6
   If no input is passed then n and m assumes a value of 10
   */
#include<iostream>
#include<fstream>

using namespace std;

int n,m;
int **H,**V;

typedef struct _node{
	int rank;
	_node *parent = NULL;
}node;

node ***C;

void makeset(node *head){
	head->rank = 1;
	head->parent = head;
}

node *findset(node *head){
	node *root = head->parent;
	node *temp2 = head;
	while(root != head){
		head = root;
		root = head->parent;
	}

	head = temp2;					//Path compression
	temp2 = head->parent;
	while(temp2 != head){
		head->parent = root;
		head = temp2;
		temp2 = head->parent;
	}

	return root;
}

void mergeset(node *head1, node *head2){			//Merging in order of the ranks
	if(head1->rank > head2->rank){
		head2->parent = head1;
		head2->rank = 0;
	}
	if(head1->rank < head2->rank){
		head1->parent = head2;
		head1->rank = 0;
	}
	if(head1->rank == head2->rank){
		head2->parent = head1;
		head1->rank += 1;
		head2->rank = 0;
	}
}

void printgrid(){

	cout<<endl<<"INITIAL GRID"<<endl;
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
		if(i == 0 && j == 0)	cout<<"+   ";
		else cout<<"+---";
		}cout<<"+"<<endl;
		for(int j = 0; j < m; ++j){
			cout<<"|   ";
		}
		if(i != n-1)
			cout<<"|";
		cout<<endl;
	}
	for(int j = 0; j < m; ++j){
			cout<<"+---";
		}cout<<"+"<<endl;

	cout<<endl<<endl;

	cout<<"FINAL GRID"<<endl;
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cout<<"+";
			if(i>0){
				if(H[i-1][j] == 0)
					cout<<"---";
				if(H[i-1][j] == 1)
					cout<<"   ";
			}
			if(i==0){
				if(j==0)
					cout<<"   ";
				else cout<<"---";
			}
		}cout<<"+"<<endl;

		for(int j = 0; j < m; ++j){
			if(j == 0){
				cout<<"|   ";
			}
			if(j > 0){
				if(V[i][j-1] == 1)
					cout<<"    ";
				if(V[i][j-1] == 0)
					cout<<"|   ";
			}
		}
		if(i != (n-1))
			cout<<"|";
		cout<<endl;
	}
	for(int j = 0; j < m; ++j){
			cout<<"+---";
		}cout<<"+"<<endl;
}

void findtreasure(){

	for (int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			node *head;
			head = (node *)malloc(sizeof(node));
			makeset(head);
			C[i][j] = head;
		}
	}

	int count = 0;
	int i,j,flag;
	while(count < m*n - 1){
		flag = rand()%2;

		if(flag == 1){
			i = rand()%n;
			j = rand()%(m-1);
			if(findset(C[i][j]) != findset(C[i][j+1])){
				V[i][j] = 1;
				count++;
				mergeset(findset(C[i][j]),findset(C[i][j+1]));
			}
		}

		if(flag == 0){
			i = rand()%(n-1);
			j = rand()%m;
			if(findset(C[i][j]) != findset(C[i+1][j])){
				H[i][j] = 1;
				count++;
				mergeset(findset(C[i][j]),findset(C[i+1][j]));
			}
		}

	}

	if(findset(C[0][0]) == findset(C[n-1][m-1]))
		cout<<"The final chamber can be reached from the start chamber"<<endl;
	else {
		cout<<"The final chamber cannot be reached from the start chamber"<<endl;
		exit(1);
	}

	printgrid();
}

int main(int argc, char **argv){

	srand((unsigned int)time(NULL));
	if(argc == 2 ||argc == 1){
		n=10;
		m=10;
	}
	if(argc == 4){
		n = atoi(argv[2]);
		m = atoi(argv[3]);
	}
	if(argc == 3){
		n = atoi(argv[1]);
		m = atoi(argv[2]);
	}

	H = (int **)calloc((n-1),sizeof(int *));
	V = (int **)calloc(n,sizeof(int *));
	C = (node ***)malloc(n*sizeof(node **));
	for(int i = 0; i < n; ++i){
		H[i] = (int *)calloc(m,sizeof(int));
		V[i] = (int *)calloc((m-1),sizeof(int));
		C[i] = (node **)malloc(m*sizeof(node *));
	}

	findtreasure();
}