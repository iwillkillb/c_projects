#include <iostream>
using namespace std;
void Hanoi(int n, char from, char middle, char to, int &fc, int &dc){
	fc++;
	if(n<=1){
		cout << "���� �̵� : "<< n << " " << from << "���� " << to << "�� �̵�" << endl;
		dc++;
	}
	else {
		Hanoi(n-1, from, to, middle, fc, dc);
		cout << "���� �̵� : "<< n << " " << from << "���� " << to << "�� �̵�" << endl;
		dc++;
		Hanoi(n-1, middle, from, to, fc, dc);
	}
}
int main() {
	int disk;
	int func_count = 0, disk_count = 0;
	
	cout << "������ �� ���Դϱ�? ";
	cin >> disk;
	cout << endl;
	
	Hanoi(disk, 'A', 'B', 'C', func_count, disk_count);
	
	cout << endl << "�Լ� ���� Ƚ�� : " << func_count << "  ���� �̵� Ƚ�� : " << disk_count << endl;
	return 0;
}
