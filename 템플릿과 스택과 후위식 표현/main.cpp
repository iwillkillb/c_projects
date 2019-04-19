/*
9. infix ������ postfix �������� ��ȯ�ϴ� ������ ���ǿ� ���� C++���α׷��� �ۼ��Ͽ�
	�� 6���� 1)�� 3)���ĵ��� postfix�� ��ȯ�� ����� ���Ͻÿ�.
  ����)
    1. �����ڴ� +, - *, /, %�� ��ȣ�� ������
    2. �ǿ����ڴ� ���� �Ǵ� ���� 1�ڷ� ������
    3. ���� ���α׷��� ���� ���� ����� ���� �ְ�, STL�� ����� ���� ����
    
    1). a + b * c - d / e :		a b c * + d e / -
    3). (( a + b * d ) + e ) / ( f % a - d ) + c :		 a b d * + e + f a % d - c + /
    
    �ʿ��� �Լ� : ���ڿ� �Է�, ���, ����, ������/�ǿ����� ����, �ǿ����� ��� 
    
    template <class T>                    // ADT 3.1
class Stack
{
public:
	Stack(int stackCapacity = 10);
	~Stack();
	int IsEmpty();
	T& Top();
	void Push(const T& item);
	void Pop();
private:
	void ChangeSize1d();
	int top;
	T *stack;
	int capacity;
};
*/

#include <iostream>
#include <string>
#include <ctype.h>
#include "Stack.h"
using namespace std;
int main() {
	string input;
	cout << "������ �Է��ϼ���." << endl;
	cin >> input;
	Stack<char> Array(input.size());//��ü ���� �ÿ� ������ �ڷ����� <>�� ��� �Ѵ�. �����ڱ��� �޾ƾ� �ϴ� char�� �Ѵ�. 
	
	for(int a=0 ; a<input.size() ; a++){
		//�������� ���. 
		if(input[a]=='+' || input[a]=='-' || input[a]=='*' || input[a]=='/' || input[a]=='%'){
			if(Array.IsEmpty() || Array.Top() == '(')Array.Push(input[a]);
			else if((input[a]=='*' || input[a]=='/' || input[a]=='%') && (Array.Top()=='+' || Array.Top()=='-')){
				Array.Push(input[a]);
			}
			else {
				cout << Array.Top() << " ";
				Array.Pop();
				Array.Push(input[a]);
			}
		}
		else if(input[a]=='('){//���� ��ȣ�� ���, ���ÿ� �����Ѵ�. 
			Array.Push(input[a]);
		}
		else if(input[a]==')'){//������ ��ȣ�� ���, ���ÿ��� ���� ��ȣ�� ���� ������ ���ÿ� �ִ� ��� ���� ����Ѵ�.
			while(Array.Top()!='('){//���ݱ����� ������ �����ڸ� Top�� (�̸� �����ؾ� �Ѵٴ� ���� �����߱� �����̾���. 
				cout << Array.Top() << " ";
				Array.Pop();
			}
			if(Array.Top()=='(')Array.Pop();
			
		}
		else cout << input[a] << " ";//�� �� �ǿ������� ���, �ٷ� ���. 
	}
	while(!Array.IsEmpty()){//�� �̻��� �Է� ������ ������ ���ÿ� �����ִ� �͵��� ��� ����Ѵ�. 
		cout << Array.Top() << " ";
		Array.Pop();
	}
	
	return 0;
}
