#include<iostream>

using namespace std;

#define MAX_SIZE 100
int Time = -1;

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
		//cout<<"Heap empty";
		return -1;
	}

	int i = 1;
	job temp;
	while(2*i <= H->numJobs){
		if(2*i == H->numJobs){
			if(H->list[i-1].remLength > H->list[2*i-1].remLength || (H->list[i-1].remLength == H->list[2*i-1].remLength && H->list[i-1].jobId > H->list[2*i-1].jobId)){
				temp = H->list[i-1];
				H->list[i-1] = H->list[2*i-1];
				H->list[2*i-1] = temp;
			}i=2*i;
			continue;
		}

		int a = check(H,i);
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

void scheduler(job jobList[], int n, heap *H){

	job current_job;
	int check_array[n] = {0};
	int Turnaround[n];
	for (int i = 0; i < n; ++i)
		Turnaround[i] = -1;
	int flag;
	cout<<"Jobs scheduled at each timestep are: "<<endl;
	while(1){
		Time++;
		int sum = 0;
		for (int i = 0; i < n; ++i){
			if(jobList[i].startTime == Time){
				check_array[i] = 1;
				jobList[i].remLength = jobList[i].jobLength;
				insert(H, jobList[i]);
			}sum += check_array[i];
		}

		flag = extractMinJob(H, &current_job);
		if(flag == 0){
			cout<<current_job.jobId<<" ";
			if(Turnaround[current_job.jobId - 1] == -1)
				Turnaround[current_job.jobId - 1] = Time - current_job.startTime;
		}
		if(flag == -1 && sum < n)
			cout<<"-1 ";
		if(flag == -1 && sum == n)
			break;
		current_job.remLength--;
		if(current_job.remLength > 0 && flag == 0)
			insert(H, current_job);

	}
	cout<<endl<<"Average Turnaround Time is ";
	int Turnaround_avg = 0;
	for (int i = 0; i < n; ++i){
		Turnaround_avg += Turnaround[i];
	}

	cout<<(float)Turnaround_avg/n<<endl;

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
	}
	scheduler(job_list, n,heap1);
}