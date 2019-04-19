#include <iostream>
using namespace std;
void Hanoi(int n, char from, char middle, char to, int &fc, int &dc){
	fc++;
	if(n<=1){
		cout << "원판 이동 : "<< n << " " << from << "에서 " << to << "로 이동" << endl;
		dc++;
	}
	else {
		Hanoi(n-1, from, to, middle, fc, dc);
		cout << "원판 이동 : "<< n << " " << from << "에서 " << to << "로 이동" << endl;
		dc++;
		Hanoi(n-1, middle, from, to, fc, dc);
	}
}
int main() {
	int disk;
	int func_count = 0, disk_count = 0;
	
	cout << "원판은 몇 개입니까? ";
	cin >> disk;
	cout << endl;
	
	Hanoi(disk, 'A', 'B', 'C', func_count, disk_count);
	
	cout << endl << "함수 가동 횟수 : " << func_count << "  원판 이동 횟수 : " << disk_count << endl;
	return 0;
}
