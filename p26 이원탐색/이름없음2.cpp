#include <iostream>
using namespace std;
int BinarySearch(int *a, const int x, const int left, const int right);
int main(){
	int arr[] = {4,5,9,10,11,12,15,17,23,25,28,30};
	int val = sizeof(arr)/sizeof(int);
	int find;
	
	cout << "인자 수 : " << val << "개" << endl;
	for(int a=0 ; a<val ; a++)cout << arr[a] << " ";
	cout << endl << endl;
	
	cout << "찾으실 숫자는? ";
	cin >> find;
	cout << endl; 
	
	if(BinarySearch(arr, find, 0, val-1)<0)cout << "그 숫자는 없습니다." << endl; 
	else cout << find << "는 " << BinarySearch(arr, find, 0, val-1)+1 << "번째에 있습니다." << endl;
	
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
