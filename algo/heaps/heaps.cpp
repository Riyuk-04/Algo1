#include<iostream>

using namespace std;

#define MAX_SIZE 100
int Time = 0;

typedef struct _job {
	int jobId;
	int startTime;
	int jobLength;
	int remLength;
} job;

typedef struct _heap {
	job list[MAX_SIZE];
	int numJobs;
} heap;

int check(heap *H, int i){
	if(H->list[i-1].remLength < H->list[2*i-1].remLength && H->list[i-1].remLength < H->list[2*i].remLength)
		return 1;
	if(H->list[i-1].remLength > H->list[2*i-1].remLength && H->list[i-1].remLength > H->list[2*i].remLength){
		if(H->list[2*i-1].remLength < H->list[2*i].remLength)
			return 2;
		else return 3;
	}
	if(H->list[i-1].remLength > H->list[2*i-1].remLength && H->list[i-1].remLength < H->list[2*i].remLength)
		return 4;
	if(H->list[i-1].remLength < H->list[2*i-1].remLength && H->list[i-1].remLength > H->list[2*i].remLength)
		return 5;

	return -1;
}

heap *initHeap(heap *H){
	H = (heap *)malloc(sizeof(heap));
	H->numJobs = 0;
	return H;
}

void insert(heap *H, job j){
	H->list[H->numJobs++] = j;
	int i = H->numJobs;
	job temp;
	while(i>1){
		if(H->list[i-1].remLength < H->list[i/2-1].remLength || (H->list[i-1].remLength == H->list[i/2-1].remLength && H->list[i-1].jobId < H->list[i/2-1].jobId)){
			temp = H->list[i/2-1];
			H->list[i/2-1] = H->list[i-1];
			H->list[i-1] = temp;
			i = i/2;
		}
		else break;
	}
}

int extractMinJob(heap *H, job *j){
	*j = H->list[0];
	if(H->numJobs > 0)
		H->list[0] = H->list[H->numJobs-- - 1];
	else{
		cout<<"Heap empty";
		return -1;
	}

	int i = 1;
	job temp;
	while(2*i <= H->numJobs){//cerr<<i;
		if(2*i == H->numJobs){
			if(H->list[i-1].remLength > H->list[2*i-1].remLength || (H->list[i-1].remLength == H->list[2*i-1].remLength && H->list[i-1].jobId > H->list[2*i-1].jobId)){
				temp = H->list[i-1];
				H->list[i-1] = H->list[2*i-1];
				H->list[2*i-1] = temp;
			}i=2*i;
			continue;
		}

		int a = check(H,i);
		//cerr<<a;
		if(a == 1){
			break;
		}
		if(a == 2 || a == 4){
			temp = H->list[i-1];
			H->list[i-1] = H->list[2*i-1];
			H->list[2*i-1] = temp;
			i = 2*i;
			continue;
		}
		if(a == 3 || a == 5){
			temp = H->list[i-1];
			H->list[i-1] = H->list[2*i];
			H->list[2*i] = temp;
			i = 2*i+1;
			continue;
		}
		if(a == -1){
			if(H->list[2*i-1].remLength < H->list[2*i].remLength){
				if(H->list[2*i-1].remLength < H->list[i-1].remLength || (H->list[2*i-1].remLength == H->list[i-1].remLength && H->list[2*i-1].jobId < H->list[i-1].jobId)){
					temp = H->list[i-1];
					H->list[i-1] = H->list[2*i-1];
					H->list[2*i-1] = temp;
					i = 2*i;
					continue;
				}
			}
			if(H->list[2*i-1].remLength > H->list[2*i].remLength){
				if(H->list[2*i].remLength < H->list[i-1].remLength || (H->list[2*i].remLength == H->list[i-1].remLength && H->list[2*i].jobId < H->list[i-1].jobId)){
					temp = H->list[i-1];
					H->list[i-1] = H->list[2*i];
					H->list[2*i] = temp;
					i = 2*i + 1;
					continue;
				}
			}
			if(H->list[2*i-1].remLength == H->list[2*i].remLength && H->list[2*i-1].jobId < H->list[2*i].jobId){
				if(H->list[2*i-1].remLength == H->list[i-1].remLength && H->list[2*i-1].jobId < H->list[i-1].jobId){
					temp = H->list[i-1];
					H->list[i-1] = H->list[2*i-1];
					H->list[2*i-1] = temp;
					i = 2*i;
					continue;
				}
			}
			if(H->list[2*i-1].remLength == H->list[2*i].remLength && H->list[2*i-1].jobId > H->list[2*i].jobId){
				if(H->list[2*i].remLength == H->list[i-1].remLength && H->list[2*i].jobId < H->list[i-1].jobId){
					temp = H->list[i-1];
					H->list[i-1] = H->list[2*i];
					H->list[2*i] = temp;
					i = 2*i + 1;
					continue;
				}
			}
			
		}
	}

	return 0;
}


int main(){
	heap *heap1;
	heap1 = initHeap(heap1);
	int n;
	cout<<"Enter no. of jobs (n): ";
	cin>>n;
	job job_list[n];
	job min_job;
	cout<<"Enter the jobs: "<<endl;
	for (int i = 0; i < n; ++i){
		cin>>job_list[i].jobId;
		cin>>job_list[i].startTime;
		cin>>job_list[i].jobLength;
		job_list[i].remLength = job_list[i].jobLength;
		insert(heap1, job_list[i]);
	}

	for (int i = 0; i < n; ++i){
		//cerr<<heap1->list[i].jobId;
	}

	for (int i = 0; i < n; ++i){
		extractMinJob(heap1, &min_job);
		cerr<<min_job.jobId<<" ";
	}

}