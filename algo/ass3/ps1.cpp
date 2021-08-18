#include<iostream>

using namespace std;

typedef struct {
	int x, y;
} POINT ;

typedef struct POINT_2{
	int x, y;
	POINT_2 *next;
} POINT_2 ;

typedef struct {
	POINT *Arr ;
	int queue_size;
} QUEUE ;

typedef struct {
	POINT_2 *head;
} STACK ;

typedef struct {
	int Len;
	int Breadth;
	int **MAT;
	int **colour;
}Graph;

void init(QUEUE *qP, int size){
	qP->queue_size = 0;
	qP->Arr = (POINT*)malloc(size*sizeof(POINT));
}

int isempty(QUEUE qP){
	if(qP.queue_size<=0)
		return 1;
	else
		return 0;
}

void enqueue(QUEUE *qP, POINT p){
	*(qP->Arr + qP->queue_size++) = p;
}

POINT dequeue(QUEUE *qP){
	POINT temp = *(qP->Arr);
	qP->Arr += 1;
	qP->queue_size--;
}

void inits(STACK *s){
	s->head = NULL;
}

int isemptys(STACK s){
	if(s.head == NULL)
		return 1;
	else return 0;
}
void push(STACK *s, POINT p){
	POINT_2 *temp = (POINT_2*)malloc(sizeof(POINT_2));
	temp->x = p.x;
	temp->y = p.y;
	temp->next = s->head;
	s->head = temp;
}
POINT pop(STACK *s){
	s->head = s->head->next;
}

int strategy1(QUEUE *qP, POINT head, POINT Fly, Graph graph){
	int A = graph.Len;
	int B =  graph.Breadth;
	int i = head.x;
	int j = head.y;

	POINT temp;
	enqueue(qP,head);
	graph.colour[i][j] = 1;

	while(!(i==Fly.x && j==Fly.y)){

		//cout<<i<<" "<<j<<endl;

		if(i+1 < A){
			if(graph.MAT[i+1][j]==0 && graph.colour[i+1][j]==0){
				temp.x = i+1;
				temp.y = j;
				enqueue(qP, temp);
				graph.colour[i+1][j] = 1;
			}}
		if(i-1 >= 0){
			if(graph.MAT[i-1][j]==0 && graph.colour[i-1][j]==0){
				temp.x = i-1;
				temp.y = j;
				enqueue(qP, temp);
				graph.colour[i-1][j] = 1;
			}}
		if(j+1 < B){
			if(graph.MAT[i][j+1]==0 && graph.colour[i][j+1]==0){
				temp.x = i;
				temp.y = j+1;
				enqueue(qP, temp);
				graph.colour[i][j+1] = 1;
			}}
		if(j-1 >= 0){
			if(graph.MAT[i][j-1]==0 && graph.colour[i][j-1]==0){
				temp.x = i;
				temp.y = j-1;
				enqueue(qP, temp);
				graph.colour[i][j-1] = 1;
			}}

		graph.colour[i][j]++;
		dequeue(qP);
		if (isempty(*qP)) return 0;
		i = qP->Arr->x;
		j = qP->Arr->y;
	}

	if (i==Fly.x && j==Fly.y)
		return 1;

}

void pretty_print(STACK *s){
	do{
		cout<<"("<<s->head->x<<","<<s->head->y<<")";
		pop(s);
	}while(!isemptys(*s));
}

void strategy2(STACK *s, POINT top, POINT Fly, Graph graph){
	POINT temp;
	int A = graph.Len;
	int B =  graph.Breadth;
	int i = top.x;
	int j = top.y;
	push(s,top);
	graph.colour[i][j] = 1;

	if (i==Fly.x && j==Fly.y){
		pretty_print(s);
		exit(1);
	}

	if(i-1 >= 0){
		if(graph.MAT[i-1][j]==0 && graph.colour[i-1][j]==0){
			temp.x = i-1;
			temp.y = j;
			strategy2(s, temp, Fly, graph);
		}}
	if(j-1 >= 0){
		if(graph.MAT[i][j-1]==0 && graph.colour[i][j-1]==0){
			temp.x = i;
			temp.y = j-1;
			strategy2(s, temp, Fly, graph);
		}}
	if(j+1 < B){
		if(graph.MAT[i][j+1]==0 && graph.colour[i][j+1]==0){
			temp.x = i;
			temp.y = j+1;
			strategy2(s, temp, Fly, graph);
		}}
	if(i+1 < A){
		if(graph.MAT[i+1][j]==0 && graph.colour[i+1][j]==0){
			temp.x = i+1;
			temp.y = j;
			strategy2(s, temp, Fly, graph);
		}}
	graph.colour[i][j] = 2;
	pop(s);

	if(isemptys(*s)){
		cout<<"Stack became empty: ERROR";
		exit(1);
	}

}

void printgrid(int x[], int y[], int A, int B, int N){
	
	int mat[A][B];
	for (int i = 0; i < N; ++i)
		mat[x[i]][y[i]] = 1;

	cout<<endl<<"Grid of stones is"<<endl;

	for(int i=0;i<A;i++){
		for (int j = 0; j < B; j++){
			if(mat[i][j]==1)
				cout<<"-";
			else cout<<"*";
		}
		cout<<endl;
	}cout<<endl;
}

int main(){
	Graph graph;
	int A,B,N;
	POINT James,Fly;
	cin>>A>>B>>N;

	int x[N],y[N];

	for(int i=0; i<N; i++)
		cin>>x[i];
	for(int i=0; i<N; i++)
		cin>>y[i];

	cin>>James.x>>James.y>>Fly.x>>Fly.y;

	printgrid(x,y,A,B,N);

	int **mat = (int **)calloc(A,sizeof(int *));
	int **colour = (int **)calloc(A,sizeof(int *));
	for (int i = 0; i < A; ++i)
	{
		mat[i] = (int *)calloc(B,sizeof(int));
		colour[i] = (int *)calloc(B,sizeof(int));
	}

	for (int i = 0; i < N; ++i)
		mat[x[i]][y[i]] = 1;

	graph.Len = A;
	graph.Breadth = B;
	graph.MAT = mat;
	graph.colour = colour;

	QUEUE *qP = (QUEUE*)malloc(sizeof(QUEUE));
	init(qP, A*B);
	int path = strategy1(qP,James,Fly,graph);

	int **colour2 = (int **)calloc(A,sizeof(int *));
	for (int i = 0; i < A; ++i)
	{
		colour2[i] = (int *)calloc(B,sizeof(int));
	}
	graph.colour = colour2;
	
	if(path){
		cout<<"Path Exists"<<endl;
		STACK *s = (STACK*) malloc(sizeof(STACK));
		inits(s);
		strategy2(s,Fly,James,graph);
	}
	else 
		cout<<"Path does not exist";

return 0;
}