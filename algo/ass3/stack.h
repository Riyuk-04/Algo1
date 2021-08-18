#include<iostream>

using namespace std;
int MAXVAL = 100;

class stack{
	int i = -1;
	public:
		int arr[100];
		void push(int x);
		void pop();
		bool isempty();
		int top();
		void show();
};

void stack::push(int x){
	if(i>=MAXVAL - 1){
		cout<<"stack overflow";
		return;
	}
	arr[++i] = x;
}

void stack::show(){
	for (int j = 0;j<=i;j++)
		cout<<arr[j];
}

void stack::pop(){
	if(i<0){
		cout<<"stack underflow";
		return;
	}
	arr[i--] = -1;
}

bool stack::isempty(){
	if(i<0)
		return 1;
	else
		return 0;
}

int stack::top(){
	return arr[i];
}