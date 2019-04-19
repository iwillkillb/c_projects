/*
9. infix 수식을 postfix 수식으로 변환하는 다음의 조건에 따라 C++프로그램을 작성하여
	위 6번의 1)과 3)수식들이 postfix로 변환된 결과와 비교하시오.
  조건)
    1. 연산자는 +, - *, /, %와 괄호로 한정함
    2. 피연산자는 문자 또는 숫자 1자로 제한함
    3. 스택 프로그램은 직접 만들어서 사용할 수도 있고, STL을 사용할 수도 있음
    
    1). a + b * c - d / e :		a b c * + d e / -
    3). (( a + b * d ) + e ) / ( f % a - d ) + c :		 a b d * + e + f a % d - c + /
    
    필요한 함수 : 문자열 입력, 출력, 저장, 연산자/피연산자 구분, 피연산자 계산 
    
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
	cout << "수식을 입력하세요." << endl;
	cin >> input;
	Stack<char> Array(input.size());//객체 생성 시에 적합한 자료형을 <>로 써야 한다. 연산자까지 받아야 하니 char로 한다. 
	
	for(int a=0 ; a<input.size() ; a++){
		//연산자의 경우. 
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
		else if(input[a]=='('){//왼쪽 괄호의 경우, 스택에 저장한다. 
			Array.Push(input[a]);
		}
		else if(input[a]==')'){//오른쪽 괄호의 경우, 스택에서 왼쪽 괄호가 나올 때까지 스택에 있는 모든 것을 출력한다.
			while(Array.Top()!='('){//지금까지의 오류는 연산자를 Top이 (이면 저장해야 한다는 것을 누락했기 때문이었다. 
				cout << Array.Top() << " ";
				Array.Pop();
			}
			if(Array.Top()=='(')Array.Pop();
			
		}
		else cout << input[a] << " ";//그 외 피연산자의 경우, 바로 출력. 
	}
	while(!Array.IsEmpty()){//더 이상의 입력 수식이 없으면 스택에 남아있는 것들을 모두 출력한다. 
		cout << Array.Top() << " ";
		Array.Pop();
	}
	
	return 0;
}
