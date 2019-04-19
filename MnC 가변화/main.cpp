
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //원형 큐에서 인덱스를 변경하는 매크로 함수
#define SONSVALUE 100
#define MAXHISTORY 1000

struct State{
	State* pre;
	int intState;
};
State stateHistory[MAXHISTORY];
State data[MAXHISTORY][SONSVALUE] = {0};	//Final data. 오직 [0]열만이 자신의 부모포인터를 얻는다. 

int stateSons[SONSVALUE];	//현재 노드의 자식들
int sonsArrayCount = 0;
int history[MAXHISTORY];	//지금까지 거닐었던 노드들
int historyIndex = 0;

int valMi, valCa, sizeOfBoat;	//선교사 수, 식인종 수, 배 사이즈 
int stateInitial = 933000,		//초기상태 
	stateCurrent,
	stateGoal = 900331;			//목적상태 

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
	return (value / (int)pow(10, i)) % 10;
}
//--------------------------------------------------------------------------




//M&C 관련 함수들------------------------------------------------------------
void InputValues();
void Sons(int state);//해당 상태의 자식들 노드 정의. 1단계
bool IsPossibleState(int state);//이 상태가 가능한 상태인지 체크한다.
int ChangeState(int state, int mi, int ca);//사람을 옮긴 뒤의 상태를 구한다. 이동할 선교사, 식인종 수는 각각 mi, ca에 있다.
//--------------------------------------------------------------------------





//이후 데이터테이블 관리------------------------------------------------------------
void DataPrint(State (*data)[SONSVALUE]); 	//데이터테이블 출력 
void DataSetting(State (*data)[SONSVALUE]); 	//데이터테이블 세팅
void DataDelete(State (*data)[SONSVALUE], int deleteRows);	//데이터테이블 특정 행 삭제 
//--------------------------------------------------------------------------





int main(void)
{
	FILE *file;
	int a,b = 0;
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
		else {//CS!=GS, Q에서 어떻게 뺄까?
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
		printf("\n오류! 해를 찾지 못했습니다.\n\n");
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
	printf("선교사, 식인종의 수, 배의 정원 수를 순서대로 입력해주세요. (모두 2 이상) ");
	scanf("%d %d %d", &valMi, &valCa, &sizeOfBoat);
	
	while(valMi<2 || valCa<2 ||sizeOfBoat<2){
		printf("선교사, 식인종의 수, 배의 정원 수를 순서대로 입력해주세요. (모두 2 이상) ");
		scanf("%d %d %d", &valMi, &valCa, &sizeOfBoat);
	}
	
	stateInitial = 900000 + valMi*10000 + valCa*1000;
	stateGoal = 900001 + valMi*100 + valCa*10;
	printf("초기상태 : %d, 목표상태 : %d\n", stateInitial, stateGoal);
}

void Sons(int state) {

	int son;
	int a,b;

	for (a = 0; a < SONSVALUE; a++)//stateSons[] 초기화
		stateSons[a] = 0;
	sonsArrayCount = 0;
	
	for(a=1 ; a<=sizeOfBoat ; a++){
		for(b=0 ; b<=a ; b++){	//Is PossibleState? 그리고 배가 움직이지 않는 오류 수정했음. 
			son = ChangeState(state, a-b, b);
			if (IsPossibleState(son) && (HowMany(state,0) != HowMany(son,0)) ) {
				stateSons[sonsArrayCount++] = son;
			}
		}
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


