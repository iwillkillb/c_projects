#include <iostream>
using namespace std;
void Recursion(double &val, int &count);
int main(){
	double val;
	int count;
	
	cout << "���ڸ� �Է��ϼ��� : ";
	cin >> val;
	count = val;
	cout << endl << val << "! = ";
	
	Recursion(val, count);
	
	cout << val << endl;
	
	return 0;
}

void Recursion(double &val, int &count){
	if(count>1){
		val *= --count;
		Recursion(val, count);
	}
	
}
