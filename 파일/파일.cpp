#include <iostream>
#include <fstream>
using namespace std;
int main() {
	ofstream fout("fout.txt");
	if(!fout)cout << "����!" << endl;
	else {
		for (int a=1 ; a<=5 ; a++){
			fout << a << "����" << endl; 
			for(int b=1 ; b<=20 ; b++){
				fout << (a-1)*20 + b << ". " << endl;
			}
			fout << endl;
		}
		cout << "�Է� �Ϸ�!" << endl; 
	}
	
	fout.close();
	
	return 0;
} 
