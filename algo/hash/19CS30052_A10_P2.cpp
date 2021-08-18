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

void insert_doublehash(hash1 *h, int key, int val, int hash_size){
	int k = key%hash_size;
	int j = val%hash_size;
	h[k].array[j].key = key;
	h[k].array[j].val = val;
}

void remove_doublehashp(hash1 *p, int key, int val, int hash_size){
	int k = key%hash_size;
	int j = val%hash_size;
	p[k].array[j].key = 0;
	p[k].array[j].val = 0;
}

void remove_doublehashc(hash1 *c, hash1 *p, int key, int hash_size){
	int k = key%hash_size;
	for (int i = 0; i < hash_size; ++i){
		remove_doublehashp(p, c[k].array[i].val, c[k].array[i].key, hash_size);
		if(c[k].array[i].key == key){
			c[k].array[i].key = 0;
			c[k].array[i].val = 0;
		}
	}
}

void pretty_print2(hash1 *p, int hash_size, char x){
	fstream file;
	char filename2[] = "output.txt";
	file.open(filename2,std::ios_base::app);
	for (int i = 0; i < hash_size; ++i){
		int flag = 0;
		for (int j = 0; j < hash_size; ++j){
			if(p[i].array[j].key != 0 || p[i].array[j].val != 0)
				flag = 1;
		}
		if(flag){
			for (int j = 0; j < hash_size; ++j){
				if(p[i].array[j].key == 0 || p[i].array[j].val == 0)
					continue;
				file<<x<<" "<<i<<" "<<p[i].array[j].key<<" "<<p[i].array[j].val<<endl;
			}
		}
		else
			file<<x<<" "<<i<<" -1 -1"<<endl;
	}
	file.close();
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
			insert_doublehash(p, portfolio, id, hash_size);
			insert_doublehash(c, id, portfolio, hash_size);
			continue;
		}
		if(operation == '-'){
			file>>id;
			remove_doublehashc(c, p, id, hash_size);
			continue;
		}
	}
	file.close();
	char filename2[] = "output.txt";
	file.open(filename2,ios::out);
	file.close();
	pretty_print2(p, hash_size, 'p');
	file.open(filename2,std::ios_base::app);
	file<<endl;
	file.close();
	pretty_print2(c, hash_size, 'c');

	return 0;
}
