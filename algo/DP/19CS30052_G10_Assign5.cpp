/*Here S(n,c) represents the maximum probability of the system with reactions 1,2,...n and using c catalysts
The recusrive realtion is:
S(n,c) = max[S(n-1,c-1)*e(n,1), S(n-1,c-2)*e(n,2),... S(n-1,n-1)*e(n,c-n+1)]
where e(k,p) is the same as in the question.
The best cases are when we have n = c or when n is 1
*/
#include<iostream>
#include<fstream>

using namespace std;

int main(){

	fstream file;
	char filename[] = "input.txt";
	file.open(filename);
	int n,c;
	file>>n>>c;
	float S[n][c] = {0};
	float e[n][c];

	for(int i = 0;i < n; i++){
		for(int j = 0;j < c; j++){
			file>>e[i][j];
		}
	}
	file.close();

	for(int i = 0;i < c; i++){
		S[0][i] = e[0][i];
	}

	for(int i = 1;i < n; i++){
		S[i][i] = S[i-1][i-1]*e[i][0];
	}

	for(int i = 1;i < n; i++){
		for(int j = i;j < c; j++){
			float max = 0;
			for(int x = 1; x <= j - i + 1; x++){
				if(S[i-1][j-x]*e[i][x-1] > max)
					max = S[i-1][j-x]*e[i][x-1];
			}
			S[i][j] = max;
		}
	}

/*	for(int i = 0;i < n; i++){							//To print the dp array uncomment the code
		for(int j = 0;j < c; j++){
			cout<<S[i][j]<<" ";
		}cout<<endl;
	}*/

	char filename2[] = "output.txt";
	file.open(filename2,ios::out);
	file<<S[n-1][c-1];

	int cat[n];
	float value = S[n-1][c-1];
	for(int i = n-1;i > 0; --i){
		for(int j = 1;j <= c-i; ++j){
			if(S[i-1][c-j-1]*e[i][j-1] == value){
				value = S[i-1][c-j-1];
				cat[i] = j;
				break;
			}
		}
		c -= cat[i];
	}
	cat[0] = c;

	for (int i = 0; i < n; ++i){
		file<<endl<<"reaction "<<i+1<<" : "<<cat[i];
	}
	file.close();

	return 0;
}