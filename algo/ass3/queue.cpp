#include<iostream>

using namespace std;
int MAXVAL = 5;

class queue{
	int front = -1;
	int rear = 0;

	public:
		int arr[5];
		void push(int x);
		void pop();
		bool isempty();
		int top();
		void show();
};

void queue::push(int x){
	if(front >= MAXVAL-1){
		cout<<"queue overflow";
		return;
	}

	arr[++front] = x;
}

void queue::pop(){
	if(rear > front){
		cout<<"queue underflow";
		return;
	}

	arr[rear++] = -1;
}

int queue::top(){
	if(queue::isempty()){
		cout<<"queue is empty";
		return -1;
	}
	return arr[front];
}

bool queue::isempty(){
	if (rear > front)
		return 1;
	else 
		return 0;
}

void queue::show(){
	for (int i = rear; i<=front; i++)
		cout<<arr[i];
}

int main(){
	queue q;
	q.push(5);
	q.push(5);
	q.push(10);
	q.push(10);
	q.pop();
	q.pop();
	q.pop();
	q.pop();
	cout<<q.top()<<endl;
	cout<<q.isempty();
	q.show();
}