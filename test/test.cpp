#include <iostream>
using namespace std;
int main(){
	int temp = 0;
	int ar[] = {6,3,4,8,5};
	int size = sizeof(ar)/sizeof(ar[0]);
	
	for(int a=0 ; a<size-1 ; a++){
		for(int b=a+1 ; b<size ; b++) {
			if(ar[a] > ar[b]){
				temp = ar[a];
				ar[a] = ar[b];
				ar[b] = temp;
			}
		}
	}
	
	for(int a=0 ; a<size ; a++){
		cout << a+1 << ". " << ar[a] << endl;
	}
	
	cout << endl << 1.4 + 2.3 << endl;
	
	return 0;
}
