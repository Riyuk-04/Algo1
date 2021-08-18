#include<iostream>
#include<fstream>

using namespace std;

typedef struct POINT{
	int x, y;
	int count = 1;
} POINT ;

typedef struct {
	POINT *arr;
	int index;
} STACK ;

typedef struct {
	int Len;
	int Breadth;
	int **MAT;
	int **colour;
}Graph;

void init(STACK *s, int size){
	s->arr = (POINT*)malloc(size*sizeof(POINT));
	s->index = 0;
}

int isemptys(STACK *s){
	if(s->index <= 0)
		return 1;
	else return 0;
}
void push(STACK *s, POINT p){
	*(s->arr + s->index++) = p;
}

POINT pop(STACK *s){
	s->index--;
}

POINT top(STACK *s){
	return *(s->arr + s->index - 1);
}

void strategy1(STACK *s, POINT top, Graph graph, int *max_count){
	POINT temp;
	int A = graph.Len;
	int B =  graph.Breadth;
	int i = top.x;
	int j = top.y;
	push(s,top);
	graph.colour[i][j] = 1;

	if(j+1 < B){
		if(graph.MAT[i][j+1] > graph.MAT[i][j] && graph.colour[i][j+1]!=1){
			temp.x = i;
			temp.y = j+1;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy1(s, temp, graph, max_count);
		}}
	if(i+1 < A){
		if(graph.MAT[i+1][j] > graph.MAT[i][j] && graph.colour[i+1][j]!=1){
			temp.x = i+1;
			temp.y = j;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy1(s, temp, graph, max_count);
		}}
	graph.colour[i][j] = 2;
	pop(s);
	if(isemptys(s)){
		//cout<<"  ";
		return;
	}
}

void strategy2(STACK *s, POINT top, Graph graph, int *max_count){
	POINT temp;
	int A = graph.Len;
	int B =  graph.Breadth;
	int i = top.x;
	int j = top.y;
	push(s,top);
	graph.colour[i][j] = 1;

	if(j+1 < B){
		if(graph.MAT[i][j+1] > graph.MAT[i][j] && graph.colour[i][j+1]!=1){
			temp.x = i;
			temp.y = j+1;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy2(s, temp, graph, max_count);
		}}
	if(i+1 < A){
		if(graph.MAT[i+1][j] > graph.MAT[i][j] && graph.colour[i+1][j]!=1){
			temp.x = i+1;
			temp.y = j;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy2(s, temp, graph, max_count);
		}}
	if(j-1 >= 0){
		if(graph.MAT[i][j-1] > graph.MAT[i][j] && graph.colour[i][j-1]!=1){
			temp.x = i;
			temp.y = j-1;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy2(s, temp, graph, max_count);
		}}
	if(i-1 >= 0){
		if(graph.MAT[i-1][j] > graph.MAT[i][j] && graph.colour[i-1][j]!=1){
			temp.x = i-1;
			temp.y = j;
			temp.count = top.count + 1;
			if (*max_count < temp.count)
				*max_count = temp.count;
			strategy2(s, temp, graph, max_count);
		}}
	graph.colour[i][j] = 2;
	pop(s);
	if(isemptys(s)){
		//cout<<"  ";
		return;
	}
}

int max_element(int arr[], int n){
	int max_no = 0;
	for (int i = 0; i < n; ++i)
	{
		if(arr[i] > max_no)
			max_no = arr[i];
	}
return max_no;
}

int max(int a, int b){
	return (a>b)?a:b;
}

void DP_strategy1(Graph graph){
	int n = graph.Len;
	int m = graph.Breadth;
	int **colour = (int **)calloc(n,sizeof(int *));
	for (int j = 0; j < n; ++j)
		colour[j] = (int *)calloc(m,sizeof(int));

	for (int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			int left = 1;
			int up = 1;
			if(j-1 >= 0){
				if(graph.MAT[i][j-1] < graph.MAT[i][j])
					left = colour[i][j-1] + 1;
			}
			if(i-1 >= 0){
				if(graph.MAT[i-1][j] < graph.MAT[i][j])
					up = colour[i-1][j] + 1;
			}
			colour[i][j] = max(left,up);
			//cout<<colour[i][j]<<" ";
		}
	}

	graph.colour = colour;
	int max = 0;
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if (colour[i][j] > max)
				max = colour[i][j];
		}
	}
	cout<<max<<" ";
}


int main(){

	Graph plot;
	fstream file;
	char filename[] = "input.txt";
	file.open(filename);
	int T;
	file>>T;

	for (int i = 0; i < T; ++i){
		int n,m;
		file>>n;
		file>>m;
		plot.Len = n;
		plot.Breadth = m;
		int **mat = (int **)malloc(n*sizeof(int *));
		for (int j = 0; j < n; ++j)
		{
			mat[j] = (int *)malloc(m*sizeof(int));
			for(int x = 0;x < m; x++)
				file>>mat[j][x];
		}
		plot.MAT = mat;
		/*int arr_games[n*m];
		int index = 0;
		for(int a = 0; a<n ; a++){
			for(int b = 0; b<m; b++){
				int max_count = 1;
				Graph graph = plot;
				int **colour = (int **)calloc(n,sizeof(int *));
				for (int j = 0; j < n; ++j)
					colour[j] = (int *)calloc(m,sizeof(int));
				graph.colour = colour;
				//cout<<graph.colour[a][b]<<" ";
				STACK *s = (STACK*) malloc(sizeof(STACK));
				init(s,n*m+1);
				POINT head;
				head.x = a;
				head.y = b;
				head.count = 1;
				strategy1(s,head,graph, &max_count);
				arr_games[index++] = max_count;
				free(s);
				//cout<<graph.MAT[a][b];
				//cout<<arr_games[index-1]<<" ";
			}
		}*/
		Graph graph = plot;
		DP_strategy1(graph);

		int max_count = 1;
		int **colour = (int **)calloc(n,sizeof(int *));
		for (int j = 0; j < n; ++j)
			colour[j] = (int *)calloc(m,sizeof(int));
		graph.colour = colour;
		//cout<<graph.colour[a][b]<<" ";
		STACK *s = (STACK*) malloc(sizeof(STACK));
		init(s,n*m+1);
		POINT head;
		head.x = 0;
		head.y = 0;
		head.count = 1;
		strategy2(s,head,graph, &max_count);
		free(s);
		cout<<max_count<<" ";

		int arr_games_3[n*m];
		int index_3 = 0;
		for(int a = 0; a<n ; a++){
			for(int b = 0; b<m; b++){
				int max_count = 1;
				graph = plot;
				int **colour = (int **)calloc(n,sizeof(int *));
				for (int j = 0; j < n; ++j)
					colour[j] = (int *)calloc(m,sizeof(int));
				graph.colour = colour;
				//cout<<graph.colour[a][b]<<" ";
				STACK *s = (STACK*) malloc(sizeof(STACK));
				init(s,n*m+1);
				POINT head;
				head.x = a;
				head.y = b;
				head.count = 1;
				strategy2(s,head,graph, &max_count);
				arr_games_3[index_3++] = max_count;
				free(s);
				//cout<<graph.MAT[a][b];
				//cout<<arr_games_3[index_3-1]<<" ";
			}
		}
		cout<<endl;
		//cout<<max_element(arr_games, n*m)<<" "<<max_count<<" "<<max_element(arr_games_3, n*m)<<endl;
	}
	file.close();
}