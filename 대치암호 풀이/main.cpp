#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char str[100], result[100];

void Ceaser (int k) {
	for(int a=0 ; a<100 ; a++){
		if(str[a] == '\0'){
			printf("\n");
			break;
		} else {
			if(str[a]+k < 97)
				result[a] = str[a]+k+26;
			else if(str[a]+k > 122)
				result[a] = str[a]+k-26;
			else
				result[a] = str[a]+k;
			
			printf("%c", result[a]);
		}
	}
}
void space(){system("cls");printf("\n\n\n\t\t");}
void Vigenere () {
	int i=0, j=0, keys=0, strs=0, select=0;
	char str[100] ={0,};
	char key[100]={0,};
	space();
	printf("평문 또는 암호문을 입력하세요 .\n\t> ");
	gets(str);
	space();
	printf("암호문은 1번 복호는 2번 : ");
	scanf("%d",&select);
	space();
	printf("키 값입력 : ");
	scanf("%s",key);
	strs= strlen(str);
	keys= strlen(key);
	for(i=0;i<strs;i++) {
		j=i % keys;
		if(select==1){
			if((str[i]>='a')&&(str[i]<='z')) {
				str[i]-='a';
				key[j]-='a'; if((str[i]+key[j]) <0) str[i]+=26; str[i] =(str[i]+key[j])%26; str[i]+='a'; key[j]+='a'; } if((str[i] >='A')&&(str[i]<='Z')) { str[i]-='A'; key[j]-='A'; if((str[i]+key[j])<0) str[i]+=26; str[i]=(str[i]+key[j])%26; str[i]+='A'; key[j]+='A'; } } if(select == 2) { if((str[i]>='a')&&(str[i]<='z')) { str[i]-='a'; key[j]-='a'; if((str[i]-key[j]) <0) str[i]+=26; str[i] =(str[i]-key[j])%26; str[i]+='a'; key[j]+='a'; } if((str[i] >='A')&&(str[i]<='Z')) { str[i]-='A'; key[j]-='A'; if((str[i]-key[j])<0) str[i]+=26; str[i]=(str[i]-key[j])%26; str[i]+='A'; key[j]+='A'; } } } space();	printf("암호화 또는 복호화된 결과 출력\n\t\t"); for(i=0;i<strs;i++){ printf("-"); if(str[i]=='/') str[i]='I'; if(str[i]=='2') str[i]='L'; } printf("\n\t\t%s\n\n\n\n\n\n",str);


}
	

int main(int argc, char** argv) {
	bool con = true;
	int jump;
	
	/*
	while(con) {
		printf("문자열을 입력하세요(소문자) : ");
		scanf("%s", &str);
		
		
	}*/
	
	Vigenere();
	
	
	return 0;
}
