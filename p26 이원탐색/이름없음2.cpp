#include <iostream>
using namespace std;
int BinarySearch(int *a, const int x, const int left, const int right);
int main(){
	int arr[] = {4,5,9,10,11,12,15,17,23,25,28,30};
	int val = sizeof(arr)/sizeof(int);
	int find;
	
	cout << "���� �� : " << val << "��" << endl;
	for(int a=0 ; a<val ; a++)cout << arr[a] << " ";
	cout << endl << endl;
	
	cout << "ã���� ���ڴ�? ";
	cin >> find;
	cout << endl; 
	
	if(BinarySearch(arr, find, 0, val-1)<0)cout << "�� ���ڴ� �����ϴ�." << endl; 
	else cout << find << "�� " << BinarySearch(arr, find, 0, val-1)+1 << "��°�� �ֽ��ϴ�." << endl;
	
	return 0;
}
int BinarySearch(int *a, const int x, const int left, const int right){
	if(left <= right){
		int middle = (left + right) / 2;
		if(x < a[middle])return BinarySearch(a, x, left, middle-1);
		else if(x > a[middle])return BinarySearch(a, x, middle+1, right);
		return middle;
	}
	return -1;
}
