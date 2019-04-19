#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //원형 큐에서 인덱스를 변경하는 매크로 함수
#define SONSVALUE 10
#define MAXHISTORY 100
int stateSons[SONSVALUE];	//현재 노드의 자식들
int sonsArrayCount = 0;
int history[MAXHISTORY];	//지금까지 거닐었던 노드들
int historyIndex = 0;

//큐 관련 함수들-----------------------------------------------------------
typedef struct Queue //Queue 구조체 정의
{
	int *buf;//저장소
	int qsize;
	int front; //꺼낼 인덱스(가장 오래전에 보관한 데이터가 있는 인덱스)
	int rear;//보관할 인덱스
	int count;//보관 개수

}Queue;

void InitQueue(Queue *queue, int qsize);//큐 초기화
int IsFull(Queue *queue); //큐가 꽉 찼는지 확인
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, int data); //큐에 보관
int Dequeue(Queue *queue); //큐에서 꺼냄
void DisposeQueue(Queue *queue);//큐 해제화
//--------------------------------------------------------------------------

int HowMany(int value, int i) {	//어느 수의 특정 자리수를 구하는 함수. i는 10의 제곱수.
	return (value / (int)pow(10,i)) % 10;
}

//M&C 관련 함수들------------------------------------------------------------
void Sons(int state);//해당 상태의 자식들 노드 정의. 1단계
bool IsPossibleState(int state);//이 상태가 가능한 상태인지 체크한다.
int ChangeState(int state, int mi, int ca);//사람을 옮긴 뒤의 상태를 구한다. 이동할 선교사, 식인종 수는 각각 mi, ca에 있다.
//--------------------------------------------------------------------------





int main(void)
{
	int i;
	int a;
	Queue queue;	//사용법 : ...(*queue 자리에는 &queue를 넣는다.)
	InitQueue(&queue, 100);//큐 초기화
	/*
		state : 상태 숫자 정의. 맨 윗자리는 int형으로 쓰기위해서일 뿐, 아무 의미 없다.
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
		else {//CS!=GS, Q에서 어떻게 뺄까?
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
	printf("\n 동작 횟수 : %d \n", count);
	return 0;
}





void Sons(int state) {

	int son;
	int a;

	for (a = 0; a < SONSVALUE; a++)//stateSons[] 초기화
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

	if (result % 10 == 0) {	//배가 왼쪽에 있을 때
		if (HowMany(state, 4) >= mi && HowMany(state, 3) >= ca) //0에서 빼는 것 방지 
			result = result - (mi * 10000) - (ca * 1000) + (mi * 100) + (ca * 10) + 1;
	}
	else {					//배가 오른쪽에 있을 때
		if (HowMany(state, 2) >= mi && HowMany(state, 1) >= ca) //0에서 빼는 것 방지 
			result = result + (mi * 10000) + (ca * 1000) - (mi * 100) - (ca * 10) - 1;
	}

	return result;
}

bool IsPossibleState(int state) {

	bool isCan = true;
	int a;
	if (HowMany(state, 4) != 0 && (HowMany(state, 4) < HowMany(state, 3)) ||	//선교사보다 식인종이 더 많은 경우 불가
		HowMany(state, 2) != 0 && (HowMany(state, 2) < HowMany(state, 1))) {
		isCan = false;
	}
	
	for (a = 0; a < MAXHISTORY; a++) {	//중복된 노드인경우 불가. 2단계
		if (state == history[a])
			isCan = false;
	}

	return isCan;
}











void InitQueue(Queue *queue, int qsize)
{
	queue->buf = (int *)malloc(sizeof(int)*qsize);
	queue->qsize = qsize;
	queue->front = queue->rear = 0; //front와 rear를 0으로 설정
	queue->count = 0;//보관 개수를 0으로 설정

}
int IsFull(Queue *queue)
{
	return queue->count == queue->qsize;//보관 개수가 qsize와 같으면 꽉 찬 상태
}
int IsEmpty(Queue *queue)
{
	return queue->count == 0;    //보관 개수가 0이면 빈 상태
}
void Enqueue(Queue *queue, int data)
{
	if (IsFull(queue))//큐가 꽉 찼을 때
	{
		printf("큐가 꽉 찼음\n");
		return;
	}
	queue->buf[queue->rear] = data;//rear 인덱스에 데이터 보관
	queue->rear = NEXT(queue->rear, queue->qsize); //rear를 다음 위치로 설정
	queue->count++;//보관 개수를 1 증가
}
int Dequeue(Queue *queue)
{
	int re = 0;
	if (IsEmpty(queue))//큐가 비었을 때
	{
		printf("큐가 비었음\n");
		return re;
	}
	re = queue->buf[queue->front];//front 인덱스에 보관한 값을 re에 설정
	queue->front = NEXT(queue->front, queue->qsize);//front를 다음 위치로 설정
	queue->count--;//보관 개수를 1 감소
	return re;
}
void DisposeQueue(Queue *queue)
{
	free(queue->buf);
}

