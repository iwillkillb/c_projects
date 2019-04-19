#include <iostream>
using namespace std;
void SelectionSort(int *ar, const int n);
void swap(int &a,int &b);

int main(){
	int array[] = {19, 15, 21, 27, 12, 23, 16, 18, 14, 8, 33, 22};
	int val = sizeof(array) / sizeof(int);
	int a = 0;
	
	cout << "숫자들의 갯수 : " << val << "개" << endl;
	for(a=0 ; a<val ; a++)cout << array[a] << " ";
	cout << endl;
	
	SelectionSort(array,val);
	for(a=0 ; a<val ; a++)cout << array[a] << " ";
	cout << endl;
	
	return 0;
} 

void SelectionSort(int *ar, const int n){
	int a, b, c;
	
	for(a=0 ; a<n ; a++){
		b = a;
		for(c = a+1 ; c<n ; c++)if(ar[c] < ar[b])b = c;
		swap(ar[a],ar[b]);
	}
}

void swap(int &a, int &b){
	int swap;
	
	swap = a;
	a = b;
	b = swap;
}
