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

template <class T>//������ 
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
	if(capacity < 1) throw "Stack capacity must be > 0";
	stack = new T[capacity];
	top = -1;
}

template <class T>//�ĸ��� 
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

template <class T>//top�� �ش��ϴ� ���� ��ȯ�Ѵ�. 
inline T& Stack<T>::Top()
{
	if(IsEmpty())throw "Stack is Empty";
	return stack[top];
}





template <class T>
void Stack<T>::Push(const T& x)       // program  3.8
{//���ÿ� x ����. 
	if(top >= capacity - 1)//���� ����� �� ���� ����� �ø��� �Լ��� �̿�. 
		ChangeSize1d();//���⼭ ChangeSize1d()�� ���� ������ ���. 
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
	T *temp = new T[capacity*2];//���ο� �޸� temp�� �Ҵ�. 
	for(i=0; i<capacity; i++)//temp�� ������ ������ �ٿ��ֱ�. 
		temp[i] = stack[i];
	delete []stack;//������ ����. ��������� ������ �뷮���� 2�谡 ��. 
	stack = temp;//������ ���Ӱ� ������ �ּҸ� ����. 
	capacity *= 2;//�뷮 ������ 2��� ����. 
	return;
}	

#endif
