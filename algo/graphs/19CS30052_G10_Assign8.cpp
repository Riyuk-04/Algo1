#include<iostream>
#include<fstream>

using namespace std;

int Time = 0;
int inf = 9000000;

typedef struct {
	int N;
	int **MAT;
	int **colour;
}Graph;

typedef struct POINT{
	int x, y;
} POINT ;

POINT S,F;

typedef struct {
	POINT arr[2500];
	int index = 0;
} STACK ;

int isemptys(STACK *s){
	if(s->index <= 0)
		return 1;
	else return 0;
}

void push(STACK *s, POINT p){
	s->arr[(s->index)++] = p;
}

POINT pop(STACK *s){
	return s->arr[--(s->index)];
}

POINT Top(STACK *s){
	return s->arr[(s->index - 1)];
}

int max(int a, int b){
	if(a>b)
		return a;
	else 
		return b;
}

void update_graph(Graph graph){
	int n = graph.N;
	for(int i = 0; i<n; i++){
		for (int j = 0;j<n;j++)
			graph.MAT[i][j] = max(graph.MAT[i][j],Time);
	}
}

int stratergy1(STACK *s, Graph graph){
	int x;
	POINT top = Top(s);
	POINT temp;
	int i = top.x;
	int j = top.y;

	if(i == F.x && j == F.y)
		return 1;

	if(i<(graph.N-1)){
		if(graph.MAT[i+1][j] <= Time && graph.colour[i+1][j] == 0){
			temp.x = i+1;
			temp.y = j;
			push(s,temp);
			graph.colour[i+1][j] = 1;
			if(stratergy1(s, graph))
				return 1;
		}
	}

	if(j<(graph.N-1)){
		if(graph.MAT[i][j+1] <= Time && graph.colour[i][j+1] == 0){
			temp.x = i;
			temp.y = j+1;
			push(s,temp);
			graph.colour[i][j+1] = 1;
			if(stratergy1(s, graph))
				return 1;
		}
	}

	if(j>0){
		if(graph.MAT[i][j-1] <= Time && graph.colour[i][j-1] == 0){
			temp.x = i;
			temp.y = j-1;
			push(s,temp);
			graph.colour[i][j-1] = 1;
			if(stratergy1(s, graph))
				return 1;
		}
	}

	if(i>0){
		if(graph.MAT[i-1][j] <= Time && graph.colour[i-1][j] == 0){
			temp.x = i-1;
			temp.y = j;
			push(s,temp);
			graph.colour[i-1][j] = 1;
			if(stratergy1(s, graph))
				return 1;
		}
	}

	pop(s);
	if(isemptys(s))
		return 0;
}

int leastTimeDijkstra(Graph graph_dijkstra){
	int n = graph_dijkstra.N;
	int i = S.x;
	int j = S.y;
	int cost[n][n] = {inf};
	cost[i][j] = graph_dijkstra.MAT[i][j];
	int Time_djikstra = graph_dijkstra.MAT[i][j];

	while(1){
		int min = inf;
		POINT near;
		if(i<(graph_dijkstra.N-1)){
			if(cost[i+1][j] > cost[i][j] + (graph_dijkstra.MAT[i+1][j] - graph_dijkstra.MAT[i][j]))
				cost[i+1][j] = cost[i][j] + (graph_dijkstra.MAT[i+1][j] - graph_dijkstra.MAT[i][j]);
		}

		if(j<(graph_dijkstra.N-1)){
			if(cost[i][j+1] > cost[i][j] + (graph_dijkstra.MAT[i][j+1] - graph_dijkstra.MAT[i][j]))
				cost[i][j+1] = cost[i][j] + (graph_dijkstra.MAT[i][j+1] - graph_dijkstra.MAT[i][j]);
		}

		if(j>0){
			if(cost[i][j-1] > cost[i][j] + (graph_dijkstra.MAT[i][j-1] - graph_dijkstra.MAT[i][j]))
				cost[i][j-1] = cost[i][j] + (graph_dijkstra.MAT[i][j-1] - graph_dijkstra.MAT[i][j]);
		}

		if(i>0){
			if(cost[i-1][j] > cost[i][j] + (graph_dijkstra.MAT[i-1][j] - graph_dijkstra.MAT[i][j]))
				cost[i-1][j] = cost[i][j] + (graph_dijkstra.MAT[i-1][j] - graph_dijkstra.MAT[i][j]);
		}
		for(int i = 0; i<n ;i++){
			for(int j =0 ; j<n ;j++){
				if((cost[i][j] > -inf) && (cost[i][j] < min)){
					min = cost[i][j];
					near.x = i;
					near.y = j;
				}
			}
		}

		int i = near.x;
		int j = near.y;
	break;
	}

	return Time_djikstra;
}

int main(){
	Graph graph,graph_dijkstra;
	int n;
	fstream file;
	char filename[] = "input.txt";
	file.open(filename);
	file>>n;
	graph.N = n;
	int **mat = (int **)calloc(n,sizeof(int *));
	int **colour = (int **)calloc(n,sizeof(int *));
	for (int i = 0; i < n; ++i)
	{
		mat[i] = (int *)calloc(n,sizeof(int));
		colour[i] = (int *)calloc(n,sizeof(int));
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			file>>mat[i][j];
	}
	graph.MAT = mat;
	graph.colour = colour;
	graph_dijkstra = graph;
	file>>S.x>>S.y;
	file>>F.x>>F.y;
	file.close();

	STACK *s;
	s = (STACK *)malloc(sizeof(STACK));
	Time = graph.MAT[S.x][S.y];

	while(1){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++)
				graph.colour[i][j] = 0;
		}
		graph.colour[S.x][S.y] = 1;
		push(s, S);
		update_graph(graph);
		int flag = stratergy1(s,graph);;
		Time++;
		if(flag == 1)
			break;
	}

	cout<<"Minimum time taken is: "<<Time - 1<<endl;
	cout<<"The Path to reach from ("<<S.x<<","<<S.y<<") to ("<<F.x<<","<<F.y<<") is : "<<endl;

	STACK *s_copy;
	s_copy = (STACK *)malloc(sizeof(STACK));

	while(!isemptys(s))
		push(s_copy,pop(s));

	int count = 0;
	while(!isemptys(s_copy)){
		count++;
		POINT temp = pop(s_copy);
		cout<<"("<<temp.x<<","<<temp.y<<") ";
	}

	cout<<endl<<"The Number of Blocks traversed are: "<<count<<endl;

	cout<<"Minimum time taken calculated using djikstra algorithm is: "<<leastTimeDijkstra(graph_dijkstra)<<endl;

}
