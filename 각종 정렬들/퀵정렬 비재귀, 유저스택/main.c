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
  
	 	if( r-l+1 > 1) {  // �������� : ���� �ִ� ������ ���� ������ 1�� �̻��� ���
            p = a[r];	//pivot�� �迭 �ε��� ����
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
			// pivot�� i���� ��ȯ
            t = a[i];
            a[i] = a[r];
			a[r] = t;

			push(r);     // ������ ������ ������ ��
            push(i+1);  // ������ ������ ���� ��
            push(i-1);  // ���� ������ ������ ��
            push(l);     // ���� ������ ���� ��
 
		} // if
	} // while
}

int main(){
	int size;
	int *data;
	int a;
	while(1){
		printf("�������� ������ �Է��ϼ��� : ");
		scanf("%d",&size);
		if(size<2){
			printf("�� ū ����� �Է��ϼ���.\n");
			continue;
		}
		data = (int *)malloc(sizeof(int) * size);

		for(a=0 ; a<size ; a++){
			printf("%d��° ������ : ", a+1);
			scanf("%d",&data[a]);
		}

		qsort(data,size);

		printf("���ĿϷ� : ");
		for(a=0 ; a<size ; a++)
			printf("%d ",data[a]);
		printf("\n\n");

		free(data);
	}
	return 0;
}

