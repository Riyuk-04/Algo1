#include<iostream>
using namespace std;

typedef struct node{
	int vertex;
	struct node *next;
}node,*point;

typedef struct Graph{
	int numVertices;
	struct  node **adjLists;
}Graph;

typedef struct{
	int from;
	int to;
	int weight;
}Edge;

point traverse(point head){
	while(head->next!=NULL)
		head = head->next;

	return head;
}

void show(Graph Graph1){
	point head;
	for(int i=0; i<Graph1.numVertices;i++){
		head = Graph1.adjLists[i];

		while(head->next!=NULL){
			head = head->next;
			cout<<head->vertex<<" ";
		}
	}
}

bool compare(Edge e1, Edge e2){
	if(e1.from > e2.from)
		return 1;
	if (e1.from < e2.from)
		return 0;
	if(e1.weight > e2.weight)
		return 1;
	if(e1.weight < e2.weight)
		return 0;
	if(e1.to >= e2.to)
		return 1;
	if(e1.to < e2.to)
		return 0;
}

void merge(Edge edge_array[],int l, int m, int r){
	int nl = m-l+1;
	int nr = r-m;

	Edge arr1[nl];
	Edge arr2[nr];

	for(int i=0;i<nl;i++)
		arr1[i] = edge_array[l+i];
	for(int i=0;i<nr;i++)
		arr2[i] = edge_array[m+1+i];

	int i = 0;
	int j = 0;
	int index = 0;
	while(i<nl && j<nr){

		if(compare(arr1[i],arr2[j]))
			edge_array[l+index++] = arr2[j++];

		else
			edge_array[l+index++] = arr1[i++];

	}

	while(i<nl)
		edge_array[l+index++] = arr1[i++];

	while(j<nr)
		edge_array[l+index++] = arr2[j++];
}

void merge_sort(Edge edge_array[],int l, int r){
	if(l<r){
		int m = l + (r-l)/2;
		merge_sort(edge_array,l,m);
		merge_sort(edge_array,m+1,r);

		merge(edge_array,l,m,r);
	}
}

int main(){
	Graph Graph1;
	int V,E;
	cin>>V>>E;
	int *In_degree;
	Edge *edge_array;
	edge_array = (Edge*)malloc(E*sizeof(Edge));
	In_degree = (int *)calloc(V,sizeof(int));
	Graph1.numVertices = V;
	Graph1.adjLists = (point*)malloc(V*sizeof(point));
	
	point temp,head;
	Edge ed_temp;

	for (int y=0; y<V; y++){
		temp = (point)malloc(sizeof(node));
		temp->vertex = y;
		temp->next = NULL;
		Graph1.adjLists[y] = temp;
	}
	int index = 0;

	for (int x=0; x<E; x++){
		int i,j;
		cin>>i>>j;
		In_degree[j-1]++;

		ed_temp.from = i;
		ed_temp.to = j;
		edge_array[index++] = ed_temp;

		temp = (point)malloc(sizeof(node));
		head = traverse(Graph1.adjLists[i-1]);
		temp->vertex = j;
		temp->next = NULL;
		head->next = temp;
	}

	for (int i = 0; i < E; i++)
	{
		Edge temp = edge_array[i];
		edge_array[i].weight = In_degree[(temp.from)-1] + In_degree[(temp.to) - 1];
		//cout<<temp.from<<" "<<edge_array[i].weight<<" "<<temp.to<<endl;
	}

	merge_sort(edge_array,0,E-1);

	for (int i = 0; i < E; i++)
	{
		Edge temp = edge_array[i];
		cout<<temp.from<<" "<<temp.weight<<" "<<temp.to<<endl;
	}
	//show(Graph1);

return 0;
}