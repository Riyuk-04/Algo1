#include<iostream>
#include"stack.h"

using namespace std;

typedef struct Graph{

		int vertices;
		int edges;
		int **adj_mat;
		int *adj_mat_colour;
}Graph;

void dfs(stack s,Graph graph,int x){
	s.push(x);
	graph.adj_mat_colour[x] ++;
	for (int i = 0; i < graph.vertices; ++i)
	{
		if(graph.adj_mat[x][i]==1 && graph.adj_mat_colour[i]==0){
			dfs(s,graph,i);
		}
	}
	s.pop();
	graph.adj_mat_colour[x] ++;

}

int main(){
	Graph graph;
	int n,e;
	int connected_components = 0;
	cout<<"Number of vertices: ";
	cin>>n;
	cout<<"Number of edges: ";
	cin>>e;
	graph.vertices = n;
	graph.edges = e;
	
	int **adj_mat = (int **)calloc(n,sizeof(int *));
	for (int i = 0; i < n; ++i)
	{
		adj_mat[i] = (int *)calloc(n,sizeof(int));
	}
	int *adj_mat_colour = (int *)calloc(n,sizeof(int));

	for (int i = 0; i < e; ++i)
	{
		int x,y;
		cin>>x>>y;
		adj_mat[x-1][y-1] = 1;
		adj_mat[y-1][x-1] = 1;
	}

	graph.adj_mat = adj_mat;
	graph.adj_mat_colour = adj_mat_colour;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(adj_mat[i][j]==1 && adj_mat_colour[i]==0){
				stack s;
				dfs(s,graph,i);
				connected_components++;
			}
		}
	}
	cout<<"Number od Connected Components = "<<connected_components;


return 0;
}
