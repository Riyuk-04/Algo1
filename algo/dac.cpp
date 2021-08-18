#include<iostream>

using namespace std;

int MAX (int x, int y, int z){
	if(x>=y){
		if(x>=z)
			return x;
		else
			return z;
	}
	if(y>=z)
		return y;
	else
		return z;	
}

int Max_Cross_Seg (int arr[], int n){

	//int n = sizeof(arr)/sizeof(arr[0]);

	if (n==1)
		return arr[0];

	int Left_sum = 0;
	int Right_sum = 0;
	int Max_lsum = 0;
	int Max_rsum = 0;

	for (int i = 1; i <= n/2 ; i++){
		Left_sum += arr[n/2 - i];
		Right_sum += arr[(n-1)/2 + i];

		if(Max_lsum < Left_sum)
			Max_lsum = Left_sum;
		if(Max_rsum < Right_sum)
			Max_rsum = Right_sum;
	}

	return Max_rsum + Max_lsum + (n%2)*arr[n/2];
}

int Max_Seg (int arr[], int n){

	int max_val;
	int left_seg_max;
	int right_seg_max;
	int cross_seg_max;
	//int n = sizeof(arr)/sizeof(arr[0]);

	if (n==1)
		max_val = arr[0];

	else{

		left_seg_max = Max_Seg(arr, n/2);
		right_seg_max = Max_Seg(arr + n/2, n/2 + (n%2));
		cross_seg_max = Max_Cross_Seg(arr, n);

		max_val = MAX(left_seg_max, right_seg_max, cross_seg_max);
	}

return max_val ;
}

int main(){

	int n;
	cout<<"Enter N: ";
	cin>>n;
	cout<<"Enter the sequence: ";
	int arr[n];
	for (int i = 0; i<n ;i++){
		int temp;
		cin>>temp;
		arr[i] = temp;
	}

	cout<<"Maximum sum is: "<<Max_Seg(arr, n);
}