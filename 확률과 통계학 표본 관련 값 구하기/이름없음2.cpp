#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
void swap(double &a, double &b);
int main(){//자료는 ar[]에 넣어서 써라. 
	double ar[] = {-6, 5, 9, 4, 4, 12, 37, 5, 3, 3};
	double average = 0.0;
	double result = 0.0;
	double middle = 0.0;
	int ar_size = sizeof(ar)/sizeof(ar[0]);
	
		//--------------------데이터 정렬과 출력 
	for(int a=0 ; a<ar_size ; a++){
		for(int b=a+1 ; b<ar_size ; b++)if(ar[a] > ar[b])swap(ar[a], ar[b]);
	}
	
	for(int a=0; a<ar_size ; a++){
		if(a%4 == 0 && a != 0)cout << endl;
		cout << fixed << setprecision(4) << ar[a] << " ";
	}cout << endl << endl;
	
	//--------------------평균과 크기 
	for(int a=0 ; a<ar_size ; a++)average += ar[a];
	average /= ar_size;
	
	cout << "평균 : " << average << endl; 
	cout << "크기 : " << ar_size << endl << endl; 
	
	//-----------------------표본중앙값
	if(ar_size % 2 == 0)middle = ar[(int)(ar_size/2)] + ar[(int)(ar_size/2)+1];
	else middle = ar[(int)(ar_size/2)];
	cout << "표본중앙값 : " << middle << endl;

	//---------------표본표준편차 
	for(int a=0 ; a<ar_size ; a++)result += (ar[a] - average) * (ar[a] - average);
	result /= ar_size-1;
	cout << "표본분산 : " << result << endl;
	result = sqrt(result);
	cout << "표본표준편차 : " << result << endl;
	
	return 0;
}

void swap(double &a, double &b){
	double swap;
	
	swap = a;
	a = b;
	b = swap;
}
