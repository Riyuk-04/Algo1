#include<iostream>
#include<fstream>

using namespace std;


typedef struct{
	int key = 0;
	int val = 0;
}node;

typedef struct _hashing {
	int key;
	int val;
	struct _hashing *next = NULL;
	node *array;
}hash1;

void insert(hash1 *h, int key, int val, int hash_size){
	int k = key%hash_size;
	hash1 *temp = h + k;
	hash1 *curr = (hash1 *)malloc(sizeof(hash1));
	curr->val = val;
	curr->key = key;
	curr->next = NULL;
	while(1){
		if(temp->next == NULL){
			temp->next = curr;
			break;
		}
		else{
			temp = temp->next;
		}
	}
}

void removep(hash1 *p, int key, int val, int hash_size){
	int k = key%hash_size;
	hash1 *temp = p + k;
	while(temp->next != NULL){
		if(temp->next->key == key && temp->next->val == val){
			temp->next = temp->next->next;
			break;
		}
		else
			temp = temp->next;
	}
}

void removec(hash1 *c, hash1 *p, int key, int hash_size){
	int k = key%hash_size;
	hash1 *temp = c + k;
	while(temp->next != NULL){
		removep(p, temp->next->val, temp->next->key, hash_size);
		temp = temp->next;
	}
	temp = c + k;
	while(temp->next != NULL){
		if(temp->next->key == key){
			temp->next = temp->next->next;
			continue;
		}
		temp = temp->next;
	}
}

void pretty_print(hash1 *p, int hash_size, char x){
	fstream file;
	char filename2[] = "output.txt";
	file.open(filename2,std::ios_base::app);
	hash1 temp;
	for (int i = 0; i < hash_size; ++i){
		temp = p[i];
		if(temp.next == NULL){
			file<<x<<" "<<i<<" "<<temp.key<<" "<<temp.val<<endl;
			continue;
		}
		else
			temp = *temp.next;
		while(1){
			if(temp.next == NULL){
				file<<x<<" "<<i<<" "<<temp.key<<" "<<temp.val<<endl;
				break;
			}
			else{
				file<<x<<" "<<i<<" "<<temp.key<<" "<<temp.val<<endl;
				temp = *temp.next;
				}
		}

	}file.close();
}

int main(){
	int hash_size, test_cases, id, portfolio;
	char operation;
	hash1 *p, *c, *p2, *c2;
	fstream file;
	char filename[] = "input.txt";
	file.open(filename);
	file>>hash_size;
	file>>test_cases;
	p = (hash1 *)malloc(hash_size*sizeof(hash1));
	c = (hash1 *)malloc(hash_size*sizeof(hash1));
	for (int i = 0; i < hash_size; ++i){
		p[i].array = (node *)malloc(hash_size*sizeof(node));
		c[i].array = (node *)malloc(hash_size*sizeof(node));
		p[i].key = -1;
		p[i].val = -1;
		p[i].next = NULL;
		c[i].next = NULL;
		c[i].key = -1;
		c[i].val = -1;
	}

	for (int i = 0; i < test_cases; ++i){
		file>>operation;
		if(operation == '+'){
			file>>id;
			file>>portfolio;
			insert(p, portfolio, id, hash_size);
			insert(c, id, portfolio, hash_size);
			continue;
		}
		if(operation == '-'){
			file>>id;
			removec(c, p, id, hash_size);
			continue;
		}
	}
	file.close();
	char filename2[] = "output.txt";
	file.open(filename2,ios::out);
	file.close();
	pretty_print(p, hash_size, 'p');
	file.open(filename2,std::ios_base::app);
	file<<endl;
	file.close();
	pretty_print(c, hash_size, 'c');

	return 0;
}
