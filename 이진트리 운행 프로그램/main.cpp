#include <iostream>
#include <queue>

using namespace std;

template <class T>  
class Tree;


class TreeNode{
template <class T> friend class Tree;   //friend 전에 template <...> 써주자. 
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
 
  cout << "\n * 이진트리 루트 : ";
  cin >> d;
  if(d=='0'){
    cout << "* 공백이진트리 *" << endl;
    return;
  }
  t = new TreeNode;
  root=t;
  t->data = d;
  q.push(t);
 while(!q.empty()){
        c=q.front();
        q.pop();
     cout << " * " << c->data << "의 왼 쪽 자노드 : ";
     cin >> d;
     if(d=='0')c->LeftChild = 0;
       else{
         t = new TreeNode;
         c->LeftChild = t;
         t->data = d;
         q.push(t);
       }
     cout << " * " << c->data << "의 오른쪽 자노드 : ";
     cin >> d;
     if(d=='0')c->RightChild = 0;
       else{
         t = new TreeNode;
         c->RightChild = t;
         t->data = d;
         q.push(t);
       }
  }
  cout << " * 이진트리 입력 완료 *" << endl;
  return;
}


template <class T>
void Tree<T>::inorder()
{
  cout << "\n * 중위운행 : ";
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
  cout << "\n * 전위운행 : ";
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
  cout << "\n * 후위운행 : ";
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
  Tree <char> t;  //입력할 문자열은 char형이니 이걸로 써주자. 
 
  cout << " < 이진트리 운행 프로그램 >\n";
  cout << "입력할 때 data는 문자1자를, 자노드가 없으면 '0'를 입력하시오.\n";
 
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
 
  cout << "\n * 이진트리 루트 : ";
  cin >> d;
  if(d=='0'){
    cout << "* 공백이진트리 *" << endl;
    return;
  }
  t = new TreeNode;
  root=t;
  t->data = d;
  q.push(t);
 while(!q.empty()){
        c=q.front();
        q.pop();
     cout << " * " << c->data << "의 왼 쪽 자노드 : ";
     cin >> d;
     if(d=='0')c->LeftChild = 0;
       else{
         t = new TreeNode;
         c->LeftChild = t;
         t->data = d;
         q.push(t);
       }
     cout << " * " << c->data << "의 오른쪽 자노드 : ";
     cin >> d;
     if(d=='0')c->RightChild = 0;
       else{
         t = new TreeNode;
         c->RightChild = t;
         t->data = d;
         q.push(t);
       }
  }
  cout << " * 이진트리 입력 완료 *" << endl;
  return;
}



void Tree::inorder()
{
  cout << "\n * 중위운행 : ";
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
 
  cout << " < 이진트리 운행 프로그램 >\n";
  cout << "입력할 때 data는 문자1자를, 자노드가 없으면 '0'를 입력하시오.\n";
 
  t.tree_input();
  t.inorder();
  return 0;
}
*/
