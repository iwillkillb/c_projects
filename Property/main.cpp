#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(int argc, char** argv) {
	
	int bit = 0;
	int count0 = 0, count1 = 0;
	int cur,pre, combo = 0;
	int run[5] = {0,0,0,0,0};
	
	srand((unsigned int)time(NULL));	//�Ϻ��� random�� ���� �� �Լ��� �����. 
	for(int a=0 ; a<10000000 ; a++){
		bit = rand()%2;
		if(bit==0)count0++;
		else count1++;
		
		if(a==0)pre = bit;
		else {
			cur = bit;
			if(cur == pre)combo++;
			else combo = 0;
			pre = cur;
		}
		if(combo <= 3)run[combo]++;
		else run[4]++;
	}
	cout << "0 : " << count0 << endl;
	cout << "1 : " << count1 << endl;
	if(count0 > count1)cout << "0 > 1, " << count0-count1 << "�� �� ����." << endl;
	if(count0 < count1)cout << "0 < 1, " << count1-count0 << "�� �� ����." << endl;
	for(int a=0 ; a<4 ; a++){
		cout << a+1 << "�� : " << run[a] << ", ";
	}cout << "5�� �̻� : " << run[4] << endl << endl;
	
	return 0;
}
