
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	FILE* file = fopen("Final History.txt", "r");
	int data[50], root[50];
	int a,b;
	
	
	for(a=0 ; a<50 ; a++){
		data[a] = 0; 
		root[a] = 0;
		fscanf(file,"%d",&data[a]);
		printf("%d-> %d\n",a,data[a]);
		
		if(a%2==0 || a==0){
			root[a/2] = data[a];
		}
		if(data[a]==0){
			root[a/2] = -data[a-1];
			break;
		}
	}
	printf("\n\n");
	
	
	
	for(a=0 ; a<49 ; a++){
		while(root[a] == root[a+1] && root[a] != 0){
			for(b=a ; b<49 ; b++){
				root[b] = root[b+1];
				if(root[b+1]==0)break;
			}
		}
		if(root[a]==0)break;
	}
	
	for(a=0 ; a<50 ; a++){
		printf("%d. %d\n",a,root[a]);
		if(root[a]==0)break;
	}
	
	
	fclose(file);
	return 0;
}
