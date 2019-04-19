#include <stdio.h>
#include <malloc.h>
void QuickSort(int *, int, int);
void Swap(int *, int *);

int main(){
	int size;
	int *data;
	int a;
	
	while(1){
		printf("데이터의 개수는? ");
		scanf("%d",&size);
		
		if(size <= 1){
			printf("잘못된 개수입니다. 1보다 큰 값을 입력하세요.\n");
			continue;
		}

		data = (int *)malloc(sizeof(int) * size);
		for(a=0 ; a<size ; a++){
			printf("%d번째 데이터 : ",a+1);
			scanf("%d",&data[a]);
		}

		QuickSort(data, 0, size-1);

		printf("정렬 결과 : ");
		for(a=0 ; a<size ; a++){
			printf("%d ",data[a]);
		}printf("\n\n");

		free(data);
	}
	return 0;
}

void Swap(int *a, int *b){
	int swap = *a;
	*a = *b;
	*b = swap;
}

void QuickSort(int *data, int low, int high){
	int a=low, b=high, pivot=(int)((low+high)/2);
	printf("low:%d pivot:%d high:%d \n",low,pivot,high);
	while(a<=b){
		while(data[a] < data[pivot]){
			printf("분할, a증가\n"); 
			a++;
		}
		while(data[b] > data[pivot]){
			printf("분할, b감소\n"); 
			b--;
		}

		if(a<=b){
			printf("분할, 교환, a:%d b:%d \n",a,b); 
			Swap(&data[a], &data[b]);
			a++;
			b--;
		}
	};

	if(low < b)QuickSort(data,low,b);
	if(a < high)QuickSort(data,a,high);

}/*#include <stdio.h>
#include <malloc.h>
void QuickSort(int *, int, int);
void Swap(int *, int *);

int main(){
	int size;
	int *data;
	int a;
	
	while(1){
		printf("데이터의 개수는? ");
		scanf("%d",&size);
		
		if(size <= 1){
			printf("잘못된 개수입니다. 1보다 큰 값을 입력하세요.\n");
			continue;
		}

		data = (int *)malloc(sizeof(int) * size);
		for(a=0 ; a<size ; a++){
			printf("%d번째 데이터 : ",a+1);
			scanf("%d",&data[a]);
		}

		QuickSort(data, 0, size-1);

		printf("정렬 결과 : ");
		for(a=0 ; a<size ; a++){
			printf("%d ",data[a]);
		}printf("\n\n");

		free(data);
	}
	return 0;
}

void Swap(int *a, int *b){
	int swap = *a;
	*a = *b;
	*b = swap;
}

void QuickSort(int *data, int low, int high){
	int a=low, b=high, pivot=(int)((low+high)/2);

	while(a<=b){
		while(data[a] < data[pivot])a++;
		while(data[b] > data[pivot])b--;

		if(a<=b){
			Swap(&data[a], &data[b]);
			a++;
			b--;
		}
	};

	if(low < b)QuickSort(data,low,b);
	if(a < high)QuickSort(data,a,high);

}*/
