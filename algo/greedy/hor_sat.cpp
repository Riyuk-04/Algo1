#include<iostream>
#include<fstream>

using namespace std;

int Lmax = 100000;

void Merge(int *a, int *b, int low, int high, int mid)
{
    int i, j, k, temp[high-low+1],temp2[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;
 
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            temp[k] = a[i];
            temp2[k] = b[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            temp2[k] = b[j];
            k++;
            j++;
        }
    }
 
    while (i <= mid)
    {
        temp[k] = a[i];
        temp2[k] = b[i];
        k++;
        i++;
    }

    while (j <= high)
    {
        temp[k] = a[j];
        temp2[k] = b[j];
        k++;
        j++;
    }
 
    for (i = low; i <= high; i++)
    {
        a[i] = temp[i-low];
        b[i] = temp2[i-low];
    }
}

void MergeSort(int *a, int *b, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        MergeSort(a, b, low, mid);
        MergeSort(a, b, mid+1, high);
 
        Merge(a, b, low, high, mid);
    }
}

void Process(int arr[], int a[], int b[], int n)
{
    int l;
    for (int i = 0; i < n; i++){
        
    }
        
}

void PNC(int arr[], int a[], int b[], int size, int n)
{
    if (size == 1) {
        Process(arr, a, b, n);
        return;
    }
 
    for (int i = 0; i < size; i++) {
        heapPermutation(arr, a, b, size - 1, n);

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
        arr[i] = i+1;

    PNC(arr, a, b, n, n);


    MergeSort(a,b, 0, n-1);

    for (int i = 0; i < n; ++i)
        cout<<a[i]<<","<<b[i]<<endl;    
}