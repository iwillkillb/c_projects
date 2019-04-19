#include <stdio.h>
#include <malloc.h>
#define MAX_NUM 2000
int stack[MAX_NUM];
int top = 0;
  
void init_stack(){

	top = 0;
}
void push(int i){
	int a;
	for(a=0 ; a<15 ; a++)
		printf("%d ",stack[a]);
	printf(" push, top:%d \n",top);

	if( top >= MAX_NUM) {
		printf("stack full\n");
        return;
        }
    else stack[top++] = i;
}
int pop(){
	int a;
	for(a=0 ; a<15 ; a++)
		printf("%d ",stack[a]);
	printf(" pop, top:%d \n",top);

	if( top == 0)return 0;
	else return stack[--top];
}
int is_stack_empty(){

	if( top == 0)return 1;
	else return 0;
}
void qsort(int *a, int n){
	int p, t;
    int i, j;
    int l, r;
 
    init_stack();
  
    l = 0;
    r = n - 1;
  
    push(r);
	push(l);
  
	while(!is_stack_empty()){
		l = pop();
		r = pop();
  
	 	if( r-l+1 > 1) {  // 종료조건 : 남아 있는 분할의 원소 개수가 1개 이상일 경우
            p = a[r];	//pivot과 배열 인덱스 설정
            i = l - 1;
			j = r;
  
            while(1) {
				while(a[++i] < p);
                while(a[--j] > p);
				if( i >= j)break;
					t = a[i];
                    a[i] = a[j];
                    a[j] = t;
			}
			// pivot과 i값을 교환
            t = a[i];
            a[i] = a[r];
			a[r] = t;

			push(r);     // 오른쪽 분할의 오른쪽 끝
            push(i+1);  // 오른쪽 분할의 왼쪽 끝
            push(i-1);  // 왼쪽 분할의 오른쪽 끝
            push(l);     // 왼쪽 분할의 왼쪽 끝
 
		} // if
	} // while
}

int main(){
	int size;
	int *data;
	int a;
	while(1){
		printf("데이터의 개수를 입력하세요 : ");
		scanf("%d",&size);
		if(size<2){
			printf("더 큰 사이즈를 입력하세요.\n");
			continue;
		}
		data = (int *)malloc(sizeof(int) * size);

		for(a=0 ; a<size ; a++){
			printf("%d번째 데이터 : ", a+1);
			scanf("%d",&data[a]);
		}

		qsort(data,size);

		printf("정렬완료 : ");
		for(a=0 ; a<size ; a++)
			printf("%d ",data[a]);
		printf("\n\n");

		free(data);
	}
	return 0;
}

