#include<iostream>
#include "assign2.h"
using namespace std;

/*The merge function here merges two outlines by comparing one element ata time just like merge sort.
In adidtion to merge sort we just her keep track of two new variables h1 and h2*/
Point* merge(Point* left, Point* right,int size,int &out_size){
	//cout<<"size = "<<size;
	int h1,h2,l,r,index;
	h1 = 0;
	h2 = 0;
	l = 0;
	r = 0;
	index = 0;

	Point* net;
	cout<<left[1].x<<left[2].x;
	for(int i = 0;i<size;i++){
		if(left[l].x < right[r].x){
			if(left[l].y >= h2){
				net[index].x = left[l].x;
				net[index].y = left[l].y;
				h1 = left[l].y;
				l++;
				index++;
				break;
			}
		}
		if(left[l].x >= right[r].x){
			if(right[r].y>=h1){
				net[index].x = right[r].x;
				net[index].y = right[r].y;
				h2 = right[r].y;
				r++;
				index++;
				break;
			}
		}
	}
	out_size = index;

	return net;
}

/*The split functions is recursive function which divides ther Point array in to two differents parts and then merges
hem seperately and returns the merged outline*/
Point* split(Point* points, int size,int &out_size){
	if (size == 1){
		//cout<<(sizeof(points))/sizeof(Point)<<endl;
		//cerr<<"out ";
		out_size = 2;
		return points;
	}
	
	else{
		int left_size,right_size;
		Point* lefty = split(points, size/2, left_size);	//cerr<<"left "<<lefty.size();
		Point* righty = split(points + size,size-size/2, right_size);	//cerr<<"right ";
		Point* net = merge(lefty,righty,left_size+right_size,out_size);	//cerr<<"net ";
		//cerr<<sizeof(net);

		return net;
	}
}
Point* findOutLine(Box boxes[], int size, int& outputsize){
Point* point_array;
/*Here i am converting the boxes format into the outline format as point*/
	for(int i = 0; i<2*size; i+=2){
		point_array[i].x = boxes[i/2].left;
		point_array[i].y = boxes[i/2].ht;
		point_array[i+1].x = boxes[i/2].right;
		point_array[i+1].y = 0;
		//cout<<point_array[i].x<<","<<point_array[i].y<<endl;
		//cout<<point_array[i+1].x<<","<<point_array[i+1].y<<endl;
	}
	//cerr<<"hello ";
	int out_size;
	point_array = split(point_array, size, &out_size);
	outputsize = out_size;
// set outputsize to the number of points in Point array you are yet to return
return point_array;
}
int main(){
process();
return 0;
}