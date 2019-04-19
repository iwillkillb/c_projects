#include<iostream>

using namespace std;
#define MAX_NUM 8
void quicksort(int low,int high);
int partition(int s[],int low, int high , int pivot_point);
int s[MAX_NUM]={15, 22, 13, 27, 12, 10, 20, 25};
void printarry(int a[]);

int Queue[100][2];
int queue_low, queue_high;
int front = -1;p0
int rear = -1;

int main()
{
	quicksort(0,7);
	printarry(s);
}
void quicksort(int low,int high){
	int pivotpoint=s[0];
	
	rear++;
	Queue[rear][0] = low;
	Queue[rear][1] = high;

	while (front < rear){

		// Queue pop
		front++;
		queue_low = Queue[front][0];
		queue_high = Queue[front][1];
		
		// Queue pop end

		printf("%d %d\n", queue_low, queue_high);
		

		pivotpoint = partition(s, queue_low, queue_high, pivotpoint);
		printf("%d\n", pivotpoint);
		int wait = getchar();

		if(queue_low < pivotpoint - 1){
			rear++;
			Queue[rear][0] = queue_low;
			Queue[rear][1] = pivotpoint - 1;
		}

		if( pivotpoint + 1 < queue_high){
			rear++;
			Queue[rear][0] = pivotpoint + 1;
			Queue[rear][1] = queue_high;
		}
	}

	
}

int partition(int s[], int low, int high, int pivotpoint){
	int i,j,temp;
	int pivot_item;
	pivot_item=s[low];
	j=low;
	for(i=low+1;i <=high; i++)
		if(s[i]<pivot_item){
			j++;
			temp=s[i];
			s[i]=s[j];
			s[j]=temp;
		}
		pivotpoint =j;
		temp=s[low];
		s[low]=s[pivotpoint];
		s[pivotpoint]=temp;

	return pivotpoint;
}
void printarry(int a[]){
	for(int i=0;i<MAX_NUM;i++)
		cout<<" "<<a[i]<<" ";
	cout<<endl;
}

