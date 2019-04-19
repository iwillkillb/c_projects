#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20
void Devide(int *, int, int);
void Merge(int *, int, int, int);
int main(){
	int size = 1;
	int *data;
	int a,b;

	while(size > 0 && size <= MAXSIZE){
		printf("배열의 사이즈를 입력하세요.(0~%d) : ",MAXSIZE);
		scanf("%d",&size);
		
		if(size <= 0 || size > MAXSIZE){
			size = 1;
			continue;
		}

		data = (int *)malloc(sizeof(int) * size);

		for(a=0 ; a<size ; a++){
			printf("%d번째 데이터 : ", a+1);
			scanf("%d",&data[a]);
		}
		printf("\n");

		Devide(data, 0, size-1);

		for(a=0 ; a<size ; a++){
			printf("%d ",data[a]);
		}
		printf("\n");

		free(data);
	}

	return 0;
}

void Devide(int *data, int left, int right){
	int mid;
	int a;
	printf("Devide!\tleft:%d\tright:%d\n",left,right); 
	if(left < right){
		mid = (int)((left+right)/2);
		Devide(data, left, mid);
		Devide(data, mid+1, right);
		Merge(data, left, mid, right);
	}
}

void Merge(int *data, int left, int mid, int right){
	int temp[MAXSIZE];
	int left_start = left;
	int left_end = mid;
	int right_start = mid+1;
	int right_end = right;
	int index = 0, a;
	printf("Marge!\tleft:%d\tmid:%d\tright:%d\n",left,mid,right); 
	while( (left_start <= left_end) && (right_start <= right_end) ){
		if(data[left_start] > data[right_start]){
			temp[index] = data[right_start];
			right_start++;
		}
		else{
			temp[index] = data[left_start];
			left_start++;
		}
		index++;
	}//두 개의 부분 중 더 작은 쪽을 temp[]에 넣는다. 

	while(left_start <= left_end){//남은 왼쪽부분의 요소들을 모두 넣는다. 
		temp[index] = data[left_start];
		left_start++;
		index++;
	}
	while(right_start <= right_end){//남은 오른쪽부분의 요소들을 모두 넣는다. 
		temp[index] = data[right_start];
		right_start++;
		index++;
	}
	
	for(a=0 ; a<index ; ++a){//이렇게 정렬된 배열 temp[]를 원래 자리에 덮어쓴다. 
		data[left] = temp[a];
		left++;
	}

}
