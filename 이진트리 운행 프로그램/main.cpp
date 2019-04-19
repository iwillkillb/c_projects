#include <iostream>
#include <queue>

using namespace std;

template <class T>  
class Tree;


class TreeNode{
template <class T> friend class Tree;   //friend ���� template <...> ������. 
private:
  TreeNode *LeftChild;
  char data;
  TreeNode *RightChild;
};

template <class T>
class Tree{
public:
  Tree(){root=0;};
  void tree_input();
  void inorder();
  void preorder();
  void postorder();
private:
  void inorder(TreeNode *CurrentNode);
  void preorder(TreeNode *currentNode);
  void postorder(TreeNode *currentNode);
  TreeNode *root;
};
 
 
 
 
 
template <class T>
void Tree<T>::tree_input()
{
  queue<TreeNode*> q;
  TreeNode *t, *c;
  char d;
 
  cout << "\n * ����Ʈ�� ��Ʈ : ";
  cin >> d;
  if(d=='0'){
    cout << "* ��������Ʈ�� *" << endl;
    return;
  }
  t = new TreeNode;
  root=t;
  t->data = d;
  q.push(t);
 while(!q.empty()){
        c=q.front();
        q.pop();
     cout << " * " << c->data << "�� �� �� �ڳ�� : ";
     cin >> d;
     if(d=='0')c->LeftChild = 0;
       else{
         t = new TreeNode;
         c->LeftChild = t;
         t->data = d;
         q.push(t);
       }
     cout << " * " << c->data << "�� ������ �ڳ�� : ";
     cin >> d;
     if(d=='0')c->RightChild = 0;
       else{
         t = new TreeNode;
         c->RightChild = t;
         t->data = d;
         q.push(t);
       }
  }
  cout << " * ����Ʈ�� �Է� �Ϸ� *" << endl;
  return;
}


template <class T>
void Tree<T>::inorder()
{
  cout << "\n * �������� : ";
  inorder(root);
  cout << endl;
}

template <class T>
void Tree<T>::inorder(TreeNode *CurrentNode)
{
  if(CurrentNode){
    inorder(CurrentNode->LeftChild);
    cout << CurrentNode -> data << ' ';
    inorder(CurrentNode->RightChild);
  }
}

//------------------------

template <class T>
void Tree<T>::preorder()
{
  cout << "\n * �������� : ";
  preorder(root);
  cout << endl;
}

template <class T>
void Tree<T>::preorder(TreeNode *CurrentNode)
{
  if(CurrentNode){
    cout << CurrentNode -> data << ' ';
    preorder(CurrentNode->LeftChild);
    preorder(CurrentNode->RightChild);
  }
}

template <class T>
void Tree<T>::postorder()
{
  cout << "\n * �������� : ";
  postorder(root);
  cout << endl;
}

template <class T>
void Tree<T>::postorder(TreeNode *CurrentNode)
{
  if(CurrentNode){
    postorder(CurrentNode->LeftChild);
    postorder(CurrentNode->RightChild);
    cout << CurrentNode -> data << ' ';
  }
}






//-------------------------------------------

int main()
{
  Tree <char> t;  //�Է��� ���ڿ��� char���̴� �̰ɷ� ������. 
 
  cout << " < ����Ʈ�� ���� ���α׷� >\n";
  cout << "�Է��� �� data�� ����1�ڸ�, �ڳ�尡 ������ '0'�� �Է��Ͻÿ�.\n";
 
  t.tree_input();
  t.inorder();
  t.preorder();
  t.postorder();
  return 0;
}


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

/*
#include <iostream>
#include <queue>
using namespace std;
  
class Tree;
 
class TreeNode{
friend class Tree;
private:
  TreeNode *LeftChild;
  char data;
  TreeNode *RightChild;
};
 
class Tree{
public:
  Tree(){root=0;};
  void tree_input();
  void inorder();
private:
  void inorder(TreeNode *CurrentNode);
  TreeNode *root;
};
 
void Tree::tree_input()
{
  queue<TreeNode*> q;
  TreeNode *t, *c;
  char d;
 
  cout << "\n * ����Ʈ�� ��Ʈ : ";
  cin >> d;
  if(d=='0'){
    cout << "* ��������Ʈ�� *" << endl;
    return;
  }
  t = new TreeNode;
  root=t;
  t->data = d;
  q.push(t);
 while(!q.empty()){
        c=q.front();
        q.pop();
     cout << " * " << c->data << "�� �� �� �ڳ�� : ";
     cin >> d;
     if(d=='0')c->LeftChild = 0;
       else{
         t = new TreeNode;
         c->LeftChild = t;
         t->data = d;
         q.push(t);
       }
     cout << " * " << c->data << "�� ������ �ڳ�� : ";
     cin >> d;
     if(d=='0')c->RightChild = 0;
       else{
         t = new TreeNode;
         c->RightChild = t;
         t->data = d;
         q.push(t);
       }
  }
  cout << " * ����Ʈ�� �Է� �Ϸ� *" << endl;
  return;
}



void Tree::inorder()
{
  cout << "\n * �������� : ";
  inorder(root);
  cout << endl;
}
void Tree::inorder(TreeNode *CurrentNode)
{
  if(CurrentNode){
    inorder(CurrentNode->LeftChild);
    cout << CurrentNode -> data << ' ';
    inorder(CurrentNode->RightChild);
  }
}
int main()
{
  Tree t;
 
  cout << " < ����Ʈ�� ���� ���α׷� >\n";
  cout << "�Է��� �� data�� ����1�ڸ�, �ڳ�尡 ������ '0'�� �Է��Ͻÿ�.\n";
 
  t.tree_input();
  t.inorder();
  return 0;
}
*/
