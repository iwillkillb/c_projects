#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
void swap(double &a, double &b);
int main(){//�ڷ�� ar[]�� �־ ���. 
	double ar[] = {-6, 5, 9, 4, 4, 12, 37, 5, 3, 3};
	double average = 0.0;
	double result = 0.0;
	double middle = 0.0;
	int ar_size = sizeof(ar)/sizeof(ar[0]);
	
		//--------------------������ ���İ� ��� 
	for(int a=0 ; a<ar_size ; a++){
		for(int b=a+1 ; b<ar_size ; b++)if(ar[a] > ar[b])swap(ar[a], ar[b]);
	}
	
	for(int a=0; a<ar_size ; a++){
		if(a%4 == 0 && a != 0)cout << endl;
		cout << fixed << setprecision(4) << ar[a] << " ";
	}cout << endl << endl;
	
	//--------------------��հ� ũ�� 
	for(int a=0 ; a<ar_size ; a++)average += ar[a];
	average /= ar_size;
	
	cout << "��� : " << average << endl; 
	cout << "ũ�� : " << ar_size << endl << endl; 
	
	//-----------------------ǥ���߾Ӱ�
	if(ar_size % 2 == 0)middle = ar[(int)(ar_size/2)] + ar[(int)(ar_size/2)+1];
	else middle = ar[(int)(ar_size/2)];
	cout << "ǥ���߾Ӱ� : " << middle << endl;

	//---------------ǥ��ǥ������ 
	for(int a=0 ; a<ar_size ; a++)result += (ar[a] - average) * (ar[a] - average);
	result /= ar_size-1;
	cout << "ǥ���л� : " << result << endl;
	result = sqrt(result);
	cout << "ǥ��ǥ������ : " << result << endl;
	
	return 0;
}

void swap(double &a, double &b){
	double swap;
	
	swap = a;
	a = b;
	b = swap;
}
