#include<iostream>
using namespace std;
 
class Chain;
 
class ChainNode{ 
       friend class Chain;	//Chain 클래스에게 이 클래스의 private 멤버들을 사용할 권한을 주었다. 
public:
       ChainNode(int, ChainNode*);
private:
       int data;
       ChainNode *link;
};
 
class Chain
{
public:
       Chain();
       void Insert(int);
       void Chain_print();
private:
       ChainNode* precede_node(int);
       ChainNode* first;
};

ChainNode::ChainNode(int element=0, ChainNode *next=0)
:data(element),link(next){}//노드는 기본적으로 데이터와 링크 필드를 가졌다. 

Chain::Chain()
{
       first = 0;	//초기 주소는 0으로 지정한다. 
}

void Chain::Insert(int d)	//입력할 인자 d를 얻는다. 
{
       ChainNode *x = precede_node(d);
       ChainNode *t = new ChainNode(d, 0);	//새로운 노드 생성 
       cout << "  -> 노드의 번지는 : " << t << endl;
       if(x){
             t->link = x->link;	//새 노드의 링크에 앞 노드의 링크값을 넣는다. 
             x->link = t;	//앞 노드의 링크가 새 노드를 가리키도록 한다. 
       }
       else{	//아무것도 없으면 first를 설정한다. 
             t->link = first;
             first = t;
       }
       return;
}



ChainNode* Chain::precede_node(int d)
{
       ChainNode *p = 0, *c = first;	//가장 처음에는 c = first이다. 
 
       while(c){	//c에 값이 있을 동안 
             if(c->data < d){	//c = first의 값이 d보다 작은 동안 계속 반복된다. <를 반대로 하면 정렬도 반대로 된다. 
                    p = c;	//return할 값은 c가 된다. 결국 지금까지의 데이터보다 크고 d보다 작은 값이 d 앞에 온다. 
                    c = c->link;	//c는 자신의 다음의 값을 가리킨다. 
             }
             else	//d 이상의 값이면 정지. 데이터들이 오름차순 정렬되는 이유. 
                    break;
       }
       return p;
}

void Chain::Chain_print()
{
       ChainNode *c = first;
       cout << endl << "< 연결리스트의 내용>" << endl;
       if(!c){	//아무런 데이터도 없으면 이 함수는 끝난다. 
             cout << " * 공백리스트입니다. \n";
             return;
       }
       cout << c->data;	//Insert()에서 입력한 값을 출력한다. 
       c=c->link;	//c는 자신의 다음의 값을 가리킨다. 
       while(c){	//값을 가진 노드들을 모두 출력한다. 
             cout << " -> " << c->data;
             c=c->link;	//c는 자신의 다음의 값을 가리킨다. 
       }
       cout << endl;
}

int main()
{
       Chain int_list;
       int d;
 
       for(;;){
             cout << "* 리스트에 추가하려는 값을 입력하세요(없으면0) : ";
             cin >> d;
             if(d ==  0) break;	//0을 입력하면 for문을 빠져나가 프로그램이 종료된다. 
             int_list.Insert(d);
             int_list.Chain_print();
       }       
       return 0;
}
