#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


void GetNum(int num, int base) {
	int result = num % base;
	num /= base;
	if (num > 0)
		GetNum (num, base);				// ��� ���. ��������� ������ ���������� �ϳ��� ��µȴ�. 
	if (result < 10)
		printf("%d", result);			// �������� ��� 
	else
		printf("%c", result-10+'A');	// 16���� �� ���ڷ� ǥ�� 
}

int main(int argc, char** argv) {
	int num, base;
	printf("���� ������ �Է��϶�. ");
	scanf ("%d %d", &num, &base);
	
	if (num == 0 || base == 0)	// 0�� �� 
		return 1;
		
    if (num < 0) {				// ������ �� 
        printf("-");
        num--;
        num = ~num;
    }
	
	GetNum(num,base);
	
	printf("(%d)\n", base);
	
	return 0;
}
