#include<iostream>
#include<fstream>

using namespace std;

float Lmax = 0;
int out[8];

int max(int a, int b){
	return a>b?a:b;
}

int check(int arr[], int a[], int b[], float l, int n){
	float time[n];
	time[0] = a[arr[0]];
	for (int i = 0; i < n-1; ++i)
	{
		float new_time = max(a[arr[i+1]], time[i] + l);
		if(new_time > b[arr[i+1]])
			return 0;
		else 
			time[i+1] = new_time;
	}
	return 1;
}

void process(int arr[], int a[], int b[], int n)
{
	int low = 0,high = 10000;
	for (int i = 0; i < 50; ++i)
	{
		float mid = (low + high)/2;
		if(check(arr,a,b,mid,n))
			low = mid;
		else 
			high = mid;
	}

	if(low > Lmax){
		Lmax = low;
		for (int i = 0; i < n; ++i)
		{
			out[i] = arr[i];
		}
	}
}

void PNC(int arr[], int a[], int b[], int size, int n)
{
    if (size == 1) {
        process(arr, a, b, n);
        return;
    }
 
    for (int i = 0; i < size; i++) {
        PNC(arr, a, b, size - 1, n);

        if (size % 2 == 1)
            swap(arr[0], arr[size - 1]);
 
        else
            swap(arr[i], arr[size - 1]);
    }
}

int main(){
	fstream file;
	char filename[] = "input.txt";
	file.open(filename);

	int n;
	file>>n;

	int a[n],b[n];
	for (int i = 0; i < n; ++i)
		file>>a[i]>>b[i];
	file.close();

	int arr[n];
	for (int i = 0; i < n; ++i)
		arr[i] = i;

	if(n == 2){
		return 0;
	}

	PNC(arr, a, b, n, n);
	int min = Lmax;
	int sec = (Lmax - min)*60;

	char filename2[] = "output.txt";
	file.open(filename2,ios::out);
	file<<min<<":"<<sec<<endl;
	for (int i = 0; i < n; ++i)
		file<<out[i]<<" ";

	file.close();
}