#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int BinarySearch(int *a, const int x, const int n, int &c);
int main(){
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
	int val = sizeof(arr)/sizeof(int);
	int count;
	double average = 0;
	ofstream file("BinarySearch.txt");
	file << "찾는 숫자 : 비교 횟수" << endl;
	cout << "인자 수 : " << val << "개" << endl;
	for(int a=0 ; a<val ; a++)cout << arr[a] << " ";
	cout << endl << endl;
	
	for(int a=0 ; a<val ; a++){
		count = 0;
		cout << endl;
		
		if(BinarySearch(arr, arr[a], val, count)<0){
			cout << "그 숫자는 없습니다." << endl; 
			file << "그 숫자는 없습니다." << endl; 
		}
		else {
			cout << arr[a] << "는 " << BinarySearch(arr, arr[a], val, count)+1 << "번째에 있습니다." << endl;
			file << setw(2) << arr[a] << " : ";
		}
		cout << "비교 횟수 : " << count << endl << endl;
		file << setw(2) << count << endl;
		average += count;
	}
	
	average /= val;
	cout << " 비교횟수 평균 : " << fixed << setprecision(2) << average << endl;
	file << " 비교횟수 평균 : " << fixed << setprecision(2) << average << endl;
	
	file.close();
	return 0;
}
int BinarySearch(int *a, const int x, const int n, int &c){
	int left = 0, right = n-1;
	while(left<=right){
		int middle = (left + right) / 2;
		c++;
		if(x < a[middle])right = middle - 1;
		else if(x > a[middle])left = middle + 1;
		else return middle;
	}
	return -1;
}
