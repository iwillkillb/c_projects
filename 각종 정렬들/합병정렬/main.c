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
		printf("�迭�� ����� �Է��ϼ���.(0~%d) : ",MAXSIZE);
		scanf("%d",&size);
		
		if(size <= 0 || size > MAXSIZE){
			size = 1;
			continue;
		}

		data = (int *)malloc(sizeof(int) * size);

		for(a=0 ; a<size ; a++){
			printf("%d��° ������ : ", a+1);
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
	}//�� ���� �κ� �� �� ���� ���� temp[]�� �ִ´�. 

	while(left_start <= left_end){//���� ���ʺκ��� ��ҵ��� ��� �ִ´�. 
		temp[index] = data[left_start];
		left_start++;
		index++;
	}
	while(right_start <= right_end){//���� �����ʺκ��� ��ҵ��� ��� �ִ´�. 
		temp[index] = data[right_start];
		right_start++;
		index++;
	}
	
	for(a=0 ; a<index ; ++a){//�̷��� ���ĵ� �迭 temp[]�� ���� �ڸ��� �����. 
		data[left] = temp[a];
		left++;
	}

}
