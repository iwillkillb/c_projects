#ifndef Stack_H_
#define Stack_H_
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
											void Print();
private:
	void ChangeSize1d();
	int top;
	T *stack;
	int capacity;
};
					/////////////////////
using namespace std;
template <class T>
void Stack<T>::Print(){
	cout << endl << "--------" << endl;
	for(int a=0 ; a<top ; a++)cout << stack[a] << endl;
	cout << endl << "----------------" << endl;
}
						////////////////////////

template <class T>//생성자 
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
	if(capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>//파멸자 
Stack<T>::~Stack()
{
	delete[]stack;
}

template <class T>
inline int Stack<T>::IsEmpty()
{
	if(top<=-1)return 1;
	else return 0;
}

template <class T>//top에 해당하는 값을 반환한다. 
inline T& Stack<T>::Top()
{
	if(IsEmpty())throw "Stack is Empty";
	return stack[top];
}





template <class T>
void Stack<T>::Push(const T& x)       // program  3.8
{//스택에 x 삽입. 
	if(top >= capacity - 1)//원형 사이즈가 다 차면 사이즈를 늘리는 함수를 이용. 
		ChangeSize1d();//여기서 ChangeSize1d()를 쓰는 유일한 경우. 
	stack[++top] = x;
}

template <class T>
void Stack<T>::Pop()                   // program 3.9
{
	if(IsEmpty())throw "Stack is empty"; 
	stack[top--].~T();
}

template <class T>
void Stack<T>::ChangeSize1d()
{
	int i;
	T *temp = new T[capacity*2];//새로운 메모리 temp를 할당. 
	for(i=0; i<capacity; i++)//temp에 원본의 내용을 붙여넣기. 
		temp[i] = stack[i];
	delete []stack;//원본은 삭제. 결과적으로 원본의 용량보다 2배가 됨. 
	stack = temp;//스택은 새롭게 템프의 주소를 받음. 
	capacity *= 2;//용량 정보를 2배로 갱신. 
	return;
}	

#endif
