#include<iostream>											//a=97 and z=122
#include<fstream>
#include<string>

using namespace std;

typedef struct Node {
	char symbol ;
	int frequency ;
	int Nvalue = 0;
	Node * next = NULL;
	Node * left = NULL;
	Node * right = NULL;
} Node;

void insert(Node *head, int ascii, int freq){
	Node *temp1 = head;
	while(temp1->next!=NULL){
		temp1 = temp1->next;
	}
	Node *temp2;
	temp2 = (Node*)malloc(sizeof(Node));
	temp2->symbol = char(ascii);
	temp2->frequency = freq;
	temp1->next = temp2;
}

void createBST(Node **head, int *index){
	Node *temp1 = *head;
	if(temp1->next == NULL)
		return;
	Node *temp2 = temp1->next;
	*head = temp2->next;
	Node *N = (Node*)malloc(sizeof(Node));
	N->left = temp1;
	N->right = temp2;
	N->symbol = '$';
	N->Nvalue = *index;
	*index = *index + 1;
	N->frequency = temp1->frequency + temp2->frequency;

	temp1 = *head;
	if(temp1->next == NULL){
		while(1){
					if(N->frequency >= temp1->frequency){
						if(temp1->right == NULL){
							temp1->right = N;
							return;
						}
						else
							temp1 = temp1->right;
					}
					if(N->frequency < temp1->frequency){
						if(temp1->left == NULL){
							temp1->left = N;
							return;
						}
						else
							temp1 = temp1->left;
					}
				}
	}
	while(temp1->next->next != NULL && N->frequency > temp1->next->frequency)
		temp1 = temp1->next;

	if(temp1->next->next == NULL && temp1->next->frequency < N->frequency){
		temp1->next->next = N;
		return;
	}
	else{
		if(temp1->next->symbol != '$'){
			N->next = temp1->next;
			temp1->next = N;
			return;
		}
		if(temp1->next->symbol == '$'){
			if(N->frequency == temp1->frequency){
				N->next = temp1->next->next;
				temp1->next->next = N;
				return;
			}
			else{
				temp1 = temp1->next;
				while(1){
					if(N->frequency >= temp1->frequency){
						if(temp1->right == NULL){
							temp1->right = N;
							return;
						}
						else
							temp1 = temp1->right;
					}
					if(N->frequency < temp1->frequency){
						if(temp1->left == NULL){
							temp1->left = N;
							return;
						}
						else
							temp1 = temp1->left;
					}
				}
			
			}
		}
	}
}

void pre_order(Node *head){
	if(head == NULL)
		return;

	if(head->symbol == '$'){
		cout<<"N"<<head->Nvalue<<"("<<head->frequency<<"),";
	}
	else
		cout<<head->symbol<<"("<<head->frequency<<"),";
	pre_order(head->left);
	pre_order(head->right);
}

void find(int ascii, int freq, Node *head){
	while(1){
		if(freq == head->frequency && int(ascii) == head->symbol)
			return;
		if(head->right != NULL){
			if(freq > head->frequency/2){
				cout<<"1";
				head = head->right;
			}
		}
		if(head->left != NULL){
			if(freq <= head->frequency/2){
				cout<<"0";
				head = head->left;
			}
		}
	}return;
}

int main(){
	int n,t;
	int dict[2][36];
	char x;
	int *arr = (int *)calloc(123,sizeof(int));
	fstream file;
	char filename[] = "log.txt";
	file.open(filename);

	file>>n;
	while (file >> x){
		t = int(x);
		if(t<95 && t>60)
			t = t + 32;
		arr[t]++;
	}
	file.close();

	for (int i = 97; i < 123; ++i)
	{
		dict[0][i-97] = i;
		dict[1][i-97] = arr[i];
		cout<<char(i)<<"="<<arr[i]<<",";
	}

	for (int i = 48; i < 57; ++i)
	{
		dict[0][i-48+26] = i;
		dict[1][i-48+26] = arr[i];
		cout<<i-48<<"="<<arr[i]<<",";
	}
	dict[0][57-48+26] = 57;
	dict[1][57-48+26] = arr[57-48+26];
	cout<<"9="<<arr[57]<<endl;

	Node *head;
	int min = 0;
	int max = 0;
	int flag = 1;
	for (int i = 0; i < 36; ++i)
	{
		if(dict[1][i] > max)
			max = dict[1][i];
	}
	while(min<=max){
		for (int i = 0; i < 36; ++i)
		{
			if(dict[1][i] == min){
				if(flag==1){
					head = (Node*)malloc(sizeof(Node));
					head->symbol = char(dict[0][i]);
					head->frequency = dict[1][i];
					flag = 0;
				}
				else
					insert(head,dict[0][i],dict[1][i]);
			}
		}min++;
	}

	Node *temp1 = head;
	/*while(temp1->next!=NULL){
		cout<<temp1->symbol<<"="<<temp1->frequency<<",";
		temp1 = temp1->next;
	}cout<<temp1->symbol<<"="<<temp1->frequency;*/

	int index = 1;
	while(head->next != NULL){
		createBST(&head,&index);
	}

	temp1 = head;
	pre_order(temp1);
	temp1 = head;

	for (int i = 0; i < 36; ++i)
	{
		cout<<endl<<char(dict[0][i])<<" ";
		find(dict[0][i],dict[1][i],temp1);
		temp1 = head;
	}
}