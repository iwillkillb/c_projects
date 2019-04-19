#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
int main(int argc, char** argv) {
	int count = 0;
	int bit[5] = {0,0,0,0,1};
	int xo[3] = {0,0,0}, out = 0;
	int allBit, preAllBit;
	
	ofstream file;
	file.open("file.txt");
	cin >> count;
	
	for(int a=0 ; a<count ; a++){
		file << setw(2) << a << "\t";
		for(int b=4 ; b>=0 ; b--)file << bit[b] << "\t";
		file << "|\t";
		for(int b=0 ; b<=2 ; b++)file << xo[b] << "\t";
		file << "|\t" << out << endl;
		
		if(bit[0] == bit[1])xo[0] = 0;
		else xo[0] = 1;
		
		if(bit[3] == xo[0])xo[1] = 0;
		else xo[1] = 1;
		
		if(bit[4] == xo[1])xo[2] = 0;
		else xo[2] = 1;
		
		out = bit[0];
		bit[0] = bit[1];
		bit[1] = bit[2];
		bit[2] = bit[3];
		bit[3] = bit[4];
		bit[4] = xo[2];
		
		if(a==0)
			preAllBit = bit[4]*10000 + bit[3]*1000 + bit[2]*100 + bit[1]*10 + bit[0];
		
		else
			allBit = bit[4]*10000 + bit[3]*1000 + bit[2]*100 + bit[1]*10 + bit[0];
		
		if(preAllBit == allBit)
			break;
	}
	
	file.close();
	return 0;
}
