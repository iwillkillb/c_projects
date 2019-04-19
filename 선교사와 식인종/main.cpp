#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //���� ť���� �ε����� �����ϴ� ��ũ�� �Լ�
#define SONSVALUE 10
#define MAXHISTORY 100
int stateSons[SONSVALUE];	//���� ����� �ڽĵ�
int sonsArrayCount = 0;
int history[MAXHISTORY];	//���ݱ��� �ŴҾ��� ����
int historyIndex = 0;

//ť ���� �Լ���-----------------------------------------------------------
typedef struct Queue //Queue ����ü ����
{
	int *buf;//�����
	int qsize;
	int front; //���� �ε���(���� �������� ������ �����Ͱ� �ִ� �ε���)
	int rear;//������ �ε���
	int count;//���� ����

}Queue;

void InitQueue(Queue *queue, int qsize);//ť �ʱ�ȭ
int IsFull(Queue *queue); //ť�� �� á���� Ȯ��
int IsEmpty(Queue *queue); //ť�� ������� Ȯ��
void Enqueue(Queue *queue, int data); //ť�� ����
int Dequeue(Queue *queue); //ť���� ����
void DisposeQueue(Queue *queue);//ť ����ȭ
//--------------------------------------------------------------------------

int HowMany(int value, int i) {	//��� ���� Ư�� �ڸ����� ���ϴ� �Լ�. i�� 10�� ������.
	return (value / (int)pow(10,i)) % 10;
}

//M&C ���� �Լ���------------------------------------------------------------
void Sons(int state);//�ش� ������ �ڽĵ� ��� ����. 1�ܰ�
bool IsPossibleState(int state);//�� ���°� ������ �������� üũ�Ѵ�.
int ChangeState(int state, int mi, int ca);//����� �ű� ���� ���¸� ���Ѵ�. �̵��� ������, ������ ���� ���� mi, ca�� �ִ�.
//--------------------------------------------------------------------------





int main(void)
{
	int i;
	int a;
	Queue queue;	//���� : ...(*queue �ڸ����� &queue�� �ִ´�.)
	InitQueue(&queue, 100);//ť �ʱ�ȭ
	/*
		state : ���� ���� ����. �� ���ڸ��� int������ �������ؼ��� ��, �ƹ� �ǹ� ����.
		9 : Nope...
		3 : Left Missionaries
		3 : Left Cannibals
		0 : Right Missionaries
		0 : Right Cannibals
		0 : 0 - Boat is left, 1 - Boat is right
	*/
	int stateInitial = 933000,
		stateCurrent,
		stateGoal = 900331;
	int count = 0;
		
	
	//Q <- IS
	Enqueue(&queue, stateInitial);
	history[0] = stateInitial;

	while (!IsEmpty(&queue)) {
		stateCurrent = Dequeue(&queue);	//CS <- Q
		if (stateCurrent / 10 == stateGoal / 10) {	//CS==GS -> End!
			printf("GOAL");
			break;
		}
		else {//CS!=GS, Q���� ��� ����?
			Sons(stateCurrent);
			for (a = 0; a < SONSVALUE; a++) {// Q <- Sons of CS
				if (stateSons[a] == 0){
					break;
				}
				else {
					Enqueue(&queue, stateSons[a]);
					printf("%.5d ", stateSons[a]-900000);
					count++;
				}
			}
			history[historyIndex++] = stateCurrent;
			printf("<- %.5d \n", history[historyIndex - 1]-900000);
		}
	}

	DisposeQueue(&queue);
	printf("\n ���� Ƚ�� : %d \n", count);
	return 0;
}





void Sons(int state) {

	int son;
	int a;

	for (a = 0; a < SONSVALUE; a++)//stateSons[] �ʱ�ȭ
		stateSons[a] = 0;
	sonsArrayCount = 0;

	son = ChangeState(state, 1, 0);
	if (IsPossibleState(son)){
		stateSons[sonsArrayCount++] = son;
	}

	son = ChangeState(state, 2, 0);
	if (IsPossibleState(son)){
		stateSons[sonsArrayCount++] = son;
	}

	son = ChangeState(state, 0, 1);
	if (IsPossibleState(son)){
		stateSons[sonsArrayCount++] = son;
	}

	son = ChangeState(state, 0, 2);
	if (IsPossibleState(son)){
		stateSons[sonsArrayCount++] = son;
	}

	son = ChangeState(state, 1, 1);
	if (IsPossibleState(son)){
		stateSons[sonsArrayCount++] = son;
	}
}





int ChangeState(int state, int mi, int ca) {

	int result = state;

	if (result % 10 == 0) {	//�谡 ���ʿ� ���� ��
		if (HowMany(state, 4) >= mi && HowMany(state, 3) >= ca) //0���� ���� �� ���� 
			result = result - (mi * 10000) - (ca * 1000) + (mi * 100) + (ca * 10) + 1;
	}
	else {					//�谡 �����ʿ� ���� ��
		if (HowMany(state, 2) >= mi && HowMany(state, 1) >= ca) //0���� ���� �� ���� 
			result = result + (mi * 10000) + (ca * 1000) - (mi * 100) - (ca * 10) - 1;
	}

	return result;
}

bool IsPossibleState(int state) {

	bool isCan = true;
	int a;
	if (HowMany(state, 4) != 0 && (HowMany(state, 4) < HowMany(state, 3)) ||	//�����纸�� �������� �� ���� ��� �Ұ�
		HowMany(state, 2) != 0 && (HowMany(state, 2) < HowMany(state, 1))) {
		isCan = false;
	}
	
	for (a = 0; a < MAXHISTORY; a++) {	//�ߺ��� ����ΰ�� �Ұ�. 2�ܰ�
		if (state == history[a])
			isCan = false;
	}

	return isCan;
}











void InitQueue(Queue *queue, int qsize)
{
	queue->buf = (int *)malloc(sizeof(int)*qsize);
	queue->qsize = qsize;
	queue->front = queue->rear = 0; //front�� rear�� 0���� ����
	queue->count = 0;//���� ������ 0���� ����

}
int IsFull(Queue *queue)
{
	return queue->count == queue->qsize;//���� ������ qsize�� ������ �� �� ����
}
int IsEmpty(Queue *queue)
{
	return queue->count == 0;    //���� ������ 0�̸� �� ����
}
void Enqueue(Queue *queue, int data)
{
	if (IsFull(queue))//ť�� �� á�� ��
	{
		printf("ť�� �� á��\n");
		return;
	}
	queue->buf[queue->rear] = data;//rear �ε����� ������ ����
	queue->rear = NEXT(queue->rear, queue->qsize); //rear�� ���� ��ġ�� ����
	queue->count++;//���� ������ 1 ����
}
int Dequeue(Queue *queue)
{
	int re = 0;
	if (IsEmpty(queue))//ť�� ����� ��
	{
		printf("ť�� �����\n");
		return re;
	}
	re = queue->buf[queue->front];//front �ε����� ������ ���� re�� ����
	queue->front = NEXT(queue->front, queue->qsize);//front�� ���� ��ġ�� ����
	queue->count--;//���� ������ 1 ����
	return re;
}
void DisposeQueue(Queue *queue)
{
	free(queue->buf);
}

