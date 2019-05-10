#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


void GetNum(int num, int base) {
	int result = num % base;
	num /= base;
	if (num > 0)
		GetNum (num, base);				// 재귀 방식. 결과적으로 마지막 나머지부터 하나씩 출력된다. 
	if (result < 10)
		printf("%d", result);			// 나머지를 출력 
	else
		printf("%c", result-10+'A');	// 16진수 시 문자로 표현 
}

int main(int argc, char** argv) {
	int num, base;
	printf("수와 진법을 입력하라. ");
	scanf ("%d %d", &num, &base);
	
	if (num == 0 || base == 0)	// 0일 때 
		return 1;
		
    if (num < 0) {				// 음수일 때 
        printf("-");
        num--;
        num = ~num;
    }
	
	GetNum(num,base);
	
	printf("(%d)\n", base);
	
	return 0;
}
