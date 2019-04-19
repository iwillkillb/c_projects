#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

void input_gen(int *, int);
void sort(int *, int);
void swap(int &, int &);

int main(){
	int arr[30000];
	double duration;
	clock_t start, stop;
	int n; 
	
	srand((int)time(NULL));
	
	cout << "데이터의 개수를 입력하세요 : ";
	cin >> n;
	input_gen(arr,n);
	start = clock();
	sort(arr,n);
	stop = clock();
	duration = (double)(stop-start) / CLOCKS_PER_SEC;
	
	for(int a=0 ; a<n ; a++)cout << setw(5) << a+1 << "번째 데이터 : "  << arr[a] << endl;
	
	cout << "자료 수 : " << n << ", 실행시간 : " << duration << endl;
	
	return 0;
}

void input_gen(int *data, int n){
	for(int i=0 ; i<n ; i++)data[i] = (int)rand();
}

void sort(int *data, int n){
	for(int i=0 ; i<n ; i++){
		int j=i;
		for(int k=i+1 ; k<n ; k++)if(data[k] < data[j])j=k;
		swap(data[i],data[j]);
	}
}

void swap(int &a, int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}
