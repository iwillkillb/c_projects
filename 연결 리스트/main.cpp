#include <stdio.h>
#include <malloc.h>

struct Node{
	int data;
	struct Node *next;
};
struct Node* HEAD = NULL;

void ListAdd(int data);
void ListPrint();
void ListDel(int data);

int main() {
	ListPrint();
	
	ListAdd(1);
	ListAdd(2);
	ListAdd(3);
	ListPrint();
	
	ListDel(2);
	ListPrint();
	
	ListDel(1);
	ListDel(3);
	ListPrint();
	
	
	return 0;
}

void ListAdd(int data){
	
	struct Node *p;
	struct Node *tmp;
	
	if(HEAD == NULL){
		HEAD = (struct Node *)malloc(sizeof(struct Node));
		HEAD->data = data;
		HEAD->next = NULL;
	}
	else {
		p = HEAD;
		
		while(p->next != NULL){
			p = p->next;
		}
		
		tmp = (Node *)malloc(sizeof(struct Node));
		tmp->data = data;
		tmp->next = NULL;
		
		p->next = tmp;
	}
}

void ListPrint(){
	struct Node *p;
	
	p = HEAD;
	
	printf("List : ");
	while( p != NULL){
		printf("%d -> ", p->data);
		p = p->next;
	}
	printf("\n");
}

void ListDel(int data){
	struct Node *del;
	struct Node *previous;
	struct Node *p;
	
	if(HEAD->data == data){
		del = HEAD;
		HEAD = del->next;
		free(del);
		return;
	}
	else {
		previous = HEAD;
		p = HEAD->next;
		
		while( p != NULL){
			if( p->data == data){
				del = p;
				previous->next = del->next;
				free(del);
				break;
			}
			previous = p;
			p = p->next;
		}
	}
}

