#include<iostream>
using namespace std;
 
class Chain;
 
class ChainNode{ 
       friend class Chain;	//Chain Ŭ�������� �� Ŭ������ private ������� ����� ������ �־���. 
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
:data(element),link(next){}//���� �⺻������ �����Ϳ� ��ũ �ʵ带 ������. 

Chain::Chain()
{
       first = 0;	//�ʱ� �ּҴ� 0���� �����Ѵ�. 
}

void Chain::Insert(int d)	//�Է��� ���� d�� ��´�. 
{
       ChainNode *x = precede_node(d);
       ChainNode *t = new ChainNode(d, 0);	//���ο� ��� ���� 
       cout << "  -> ����� ������ : " << t << endl;
       if(x){
             t->link = x->link;	//�� ����� ��ũ�� �� ����� ��ũ���� �ִ´�. 
             x->link = t;	//�� ����� ��ũ�� �� ��带 ����Ű���� �Ѵ�. 
       }
       else{	//�ƹ��͵� ������ first�� �����Ѵ�. 
             t->link = first;
             first = t;
       }
       return;
}



ChainNode* Chain::precede_node(int d)
{
       ChainNode *p = 0, *c = first;	//���� ó������ c = first�̴�. 
 
       while(c){	//c�� ���� ���� ���� 
             if(c->data < d){	//c = first�� ���� d���� ���� ���� ��� �ݺ��ȴ�. <�� �ݴ�� �ϸ� ���ĵ� �ݴ�� �ȴ�. 
                    p = c;	//return�� ���� c�� �ȴ�. �ᱹ ���ݱ����� �����ͺ��� ũ�� d���� ���� ���� d �տ� �´�. 
                    c = c->link;	//c�� �ڽ��� ������ ���� ����Ų��. 
             }
             else	//d �̻��� ���̸� ����. �����͵��� �������� ���ĵǴ� ����. 
                    break;
       }
       return p;
}

void Chain::Chain_print()
{
       ChainNode *c = first;
       cout << endl << "< ���Ḯ��Ʈ�� ����>" << endl;
       if(!c){	//�ƹ��� �����͵� ������ �� �Լ��� ������. 
             cout << " * ���鸮��Ʈ�Դϴ�. \n";
             return;
       }
       cout << c->data;	//Insert()���� �Է��� ���� ����Ѵ�. 
       c=c->link;	//c�� �ڽ��� ������ ���� ����Ų��. 
       while(c){	//���� ���� ������ ��� ����Ѵ�. 
             cout << " -> " << c->data;
             c=c->link;	//c�� �ڽ��� ������ ���� ����Ų��. 
       }
       cout << endl;
}

int main()
{
       Chain int_list;
       int d;
 
       for(;;){
             cout << "* ����Ʈ�� �߰��Ϸ��� ���� �Է��ϼ���(������0) : ";
             cin >> d;
             if(d ==  0) break;	//0�� �Է��ϸ� for���� �������� ���α׷��� ����ȴ�. 
             int_list.Insert(d);
             int_list.Chain_print();
       }       
       return 0;
}
