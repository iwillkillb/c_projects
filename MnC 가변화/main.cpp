
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //���� ť���� �ε����� �����ϴ� ��ũ�� �Լ�
#define SONSVALUE 100
#define MAXHISTORY 1000

struct State{
	State* pre;
	int intState;
};
State stateHistory[MAXHISTORY];
State data[MAXHISTORY][SONSVALUE] = {0};	//Final data. ���� [0]������ �ڽ��� �θ������͸� ��´�. 

int stateSons[SONSVALUE];	//���� ����� �ڽĵ�
int sonsArrayCount = 0;
int history[MAXHISTORY];	//���ݱ��� �ŴҾ��� ����
int historyIndex = 0;

int valMi, valCa, sizeOfBoat;	//������ ��, ������ ��, �� ������ 
int stateInitial = 933000,		//�ʱ���� 
	stateCurrent,
	stateGoal = 900331;			//�������� 

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
	return (value / (int)pow(10, i)) % 10;
}
//--------------------------------------------------------------------------




//M&C ���� �Լ���------------------------------------------------------------
void InputValues();
void Sons(int state);//�ش� ������ �ڽĵ� ��� ����. 1�ܰ�
bool IsPossibleState(int state);//�� ���°� ������ �������� üũ�Ѵ�.
int ChangeState(int state, int mi, int ca);//����� �ű� ���� ���¸� ���Ѵ�. �̵��� ������, ������ ���� ���� mi, ca�� �ִ�.
//--------------------------------------------------------------------------





//���� ���������̺� ����------------------------------------------------------------
void DataPrint(State (*data)[SONSVALUE]); 	//���������̺� ��� 
void DataSetting(State (*data)[SONSVALUE]); 	//���������̺� ����
void DataDelete(State (*data)[SONSVALUE], int deleteRows);	//���������̺� Ư�� �� ���� 
//--------------------------------------------------------------------------





int main(void)
{
	FILE *file;
	int a,b = 0;
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
	
	int count = 0;
	
	InputValues(); 
	
	file = fopen("history.txt", "w");

	//Q <- IS
	Enqueue(&queue, stateInitial);
	history[0] = stateInitial;
	
	while (!IsEmpty(&queue)) {
		stateCurrent = Dequeue(&queue);	//CS <- Q
		if (stateCurrent / 10 == stateGoal / 10) {	//CS==GS -> End!
			history[historyIndex++] = stateCurrent;
			break;
		}
		else {//CS!=GS, Q���� ��� ����?
			Sons(stateCurrent);	//Init and Define stateSons[n]
			history[historyIndex++] = stateCurrent;
			
			fprintf(file, "%.5d\n", history[historyIndex - 1]);
			data[historyIndex - 1][b++].intState = history[historyIndex - 1];
			for (a = 0; a < SONSVALUE; a++) {// Q <- Sons of CS
				if (stateSons[a] == 0) {
					continue;
				}
				else {
					Enqueue(&queue, stateSons[a]);
					fprintf(file, "%.5d\n", stateSons[a] - 100000);
					data[historyIndex - 1][b++].intState = stateSons[a] - 100000;
					count++;
				}
			}
			fprintf(file, "-1\n");
			b = 0;
		}
	}
	
	if(history[historyIndex-1] != stateGoal){
		printf("\n����! �ظ� ã�� ���߽��ϴ�.\n\n");
	}
	fprintf(file, "%.5d\n", history[historyIndex-1]);
	data[historyIndex - 1][0].intState = history[historyIndex - 1];
	fprintf(file, "0\n");
	
	
	
	
	
	DataSetting(data);
	DataPrint(data);
	
	
	
	fclose(file);
	DisposeQueue(&queue);
	return 0;
}





void DataPrint(State (*data)[SONSVALUE]){
	int a,b;
	int count = 0;
	FILE* file = fopen("Final History.txt", "w");
	
	for(a=0 ; a<MAXHISTORY ; a++){	//All data[][] Print...
		if(data[a][0].intState != 0)
			printf("%d : ", data[a][0].intState);
		for(b=1 ; b<SONSVALUE ; b++){
			if(data[a][b].intState != 0)
				printf("%d ", data[a][b].intState);
		}
		printf("\n");
		
		if(data[a][0].intState == 0)
			break;
	}
	
	for(a=0 ; a<MAXHISTORY ; a++){	//How to set previous point.
		if(data[a][0].pre != NULL){
			printf("* %d->%d\n", data[a][0].pre->intState, data[a][0].intState);
			fprintf(file, "%d\n%d\n", data[a][0].pre->intState, data[a][0].intState * (-1));
			count++;
		}
	}
	fprintf(file, "0\n");
	fclose(file);
	printf("count : %d \n", count);
}

void DataSetting(State (*data)[SONSVALUE]){
	int a,b,c;
	int sum;
	State* preRows;
	bool same;
	
	
	for(a=0 ; a<historyIndex ; a++){
		for(b=1 ; b<SONSVALUE ; b++){
			for(c=a ; c<MAXHISTORY ; c++){
				if(data[a][b].intState-800000 == data[c][0].intState-900000){
					data[c][0].pre = &data[a][0];
					break;
				}
			}
		}
	}
}

void DataDelete(State (*data)[SONSVALUE], int deleteRows){
	int a,b;
	
	for(a=deleteRows ; a<MAXHISTORY-1 ; a++){
		for(b=0 ; b<SONSVALUE ; b++){
			data[a][b] = data[a+1][b];
		}
	}
}






void InputValues(){
	printf("������, �������� ��, ���� ���� ���� ������� �Է����ּ���. (��� 2 �̻�) ");
	scanf("%d %d %d", &valMi, &valCa, &sizeOfBoat);
	
	while(valMi<2 || valCa<2 ||sizeOfBoat<2){
		printf("������, �������� ��, ���� ���� ���� ������� �Է����ּ���. (��� 2 �̻�) ");
		scanf("%d %d %d", &valMi, &valCa, &sizeOfBoat);
	}
	
	stateInitial = 900000 + valMi*10000 + valCa*1000;
	stateGoal = 900001 + valMi*100 + valCa*10;
	printf("�ʱ���� : %d, ��ǥ���� : %d\n", stateInitial, stateGoal);
}

void Sons(int state) {

	int son;
	int a,b;

	for (a = 0; a < SONSVALUE; a++)//stateSons[] �ʱ�ȭ
		stateSons[a] = 0;
	sonsArrayCount = 0;
	
	for(a=1 ; a<=sizeOfBoat ; a++){
		for(b=0 ; b<=a ; b++){	//Is PossibleState? �׸��� �谡 �������� �ʴ� ���� ��������. 
			son = ChangeState(state, a-b, b);
			if (IsPossibleState(son) && (HowMany(state,0) != HowMany(son,0)) ) {
				stateSons[sonsArrayCount++] = son;
			}
		}
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


