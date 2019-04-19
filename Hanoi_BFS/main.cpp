#include <stdio.h>

#define PIN_NUM 3											// 핀 개수
#define DISK_NUM 3											// 디스크 개수
#define DEPTH 1000

struct Hanoi_Structure{
	int Disk[DEPTH][PIN_NUM][DISK_NUM];						// Depth는 이전노드 (부모노드)들을 기억하기 위한 장소
	int depth;
};

Hanoi_Structure Hanoi[35000];								// Queue 메모리
Hanoi_Structure Temp;										// 현재 상태 (pop한 내용)

int top = -1;
int bottom = -1;

void initialize();											// 초기 상태 push
void printHanoiState(int state);							// 목표 상태를 찾았을 때 디스크를 옮기는 과정 출력
bool pop();													// pop
void checkMove();											// 현재 상태에서 디스크를 옮길 수 있는 모든 경우의 수 탐색
void push(int from, int to, int from_index, int to_index);	// push
bool checkGoalState();										// 현재 상태가 목표 상태인지 점검

int main(){
	int count = 0;

	initialize();
	while(top > bottom){
		pop();
		if(checkGoalState()){
			printf("Find\n");
			printf("bottom: %d\n", --bottom);
			printHanoiState(--bottom);
			break;
		}
		checkMove();
		//printf("%d\n", top);
	}
}

void initialize(){
	top++;
	Hanoi[top].depth = 0;
	for(int i = 0; i < DISK_NUM; i++){
		Hanoi[0].Disk[top][0][i] = DISK_NUM - i;
		Hanoi[0].Disk[top][1][i] = 0;
		Hanoi[0].Disk[top][2][i] = 0;
	}
	
}

void printHanoiState(int state){
	/*for(int dep = 0; dep <= Hanoi[state].depth; dep++){
		printf("%d번째 이동\n", dep);
		for(int i = DISK_NUM - 1; i >= 0; i--){
			for(int j = 0; j < 3; j++){
				if(Hanoi[state].Disk[dep][j][i] != 0) printf("\t%2d\t", Hanoi[state].Disk[dep][j][i]);
				else printf("\t  \t");
			}
			printf("\n");
		}
		printf("\t-a\t\t-b\t\t-c\t\n");
	}*/

	for(int dep = 0; dep <= Temp.depth; dep++){
		printf("%d번째 이동\n", dep);
		for(int i = DISK_NUM - 1; i >= 0; i--){
			for(int j = 0; j < 3; j++){
				if(Temp.Disk[dep][j][i] != 0) printf("\t%2d\t", Temp.Disk[dep][j][i]);
				else printf("\t  \t");
			}
			printf("\n");
		}
		printf("\t-a\t\t-b\t\t-c\t\n");
	}
}

bool pop(){
	Temp.depth = Hanoi[bottom].depth;
	bottom++;
	for(int dep = 0; dep <= Hanoi[bottom].depth; dep++){
		for(int height = 0; height < DISK_NUM; height++){
			Temp.Disk[dep][0][height] = Hanoi[bottom].Disk[dep][0][height];
			Temp.Disk[dep][1][height] = Hanoi[bottom].Disk[dep][1][height];
			Temp.Disk[dep][2][height] = Hanoi[bottom].Disk[dep][2][height];
		}
	}

	if(checkGoalState()) return true;
	else return false;

	return false;
}

void checkMove(){
	int height_index[PIN_NUM];
	int height_value[PIN_NUM];

	int check_pin;

	for(int pin = 0; pin < PIN_NUM; pin++){
		for(int height = 0; height < DISK_NUM; height++){
			if(Temp.Disk[Temp.depth][pin][height] == 0){
				height_index[pin] = height - 1;
				if(height == 0) height_value[pin] = -1;
				else height_value[pin] = Temp.Disk[Temp.depth][pin][height - 1];
				break;
			}
			else if(height == DISK_NUM - 1){
				height_index[pin] = height;
				height_value[pin] = Temp.Disk[Temp.depth][pin][height];
				break;
			}
		}
	}
	//printf("%d %d %d\n", height_index[0], height_index[1], height_index[2]);
	//printf("%d %d %d\n", height_value[0], height_value[1], height_value[2]);

	for(int pin = 0; pin < PIN_NUM; pin++){
		for(int shift = 1; shift < PIN_NUM; shift++){
			check_pin = (pin + shift) % PIN_NUM;
			if(height_value[pin] != -1){
				if((height_value[pin] < height_value[check_pin]) || height_index[check_pin] == -1){
					push(pin, check_pin, height_index[pin], height_index[check_pin]);
				}
			}
		}
	}
}

void push(int from, int to, int from_index, int to_index){
	int temp;
	
	top++;

	Hanoi[top].depth = Temp.depth + 1;

	for(int dep = 0; dep <= Temp.depth; dep++){
		for(int height = 0; height < DISK_NUM; height++){
			Hanoi[top].Disk[dep][0][height] = Temp.Disk[dep][0][height];
			Hanoi[top].Disk[dep][1][height] = Temp.Disk[dep][1][height];
			Hanoi[top].Disk[dep][2][height] = Temp.Disk[dep][2][height];
		}
	}

	for(int height = 0; height < DISK_NUM; height++){
		Hanoi[top].Disk[Hanoi[top].depth][0][height] = Temp.Disk[Temp.depth][0][height];
		Hanoi[top].Disk[Hanoi[top].depth][1][height] = Temp.Disk[Temp.depth][1][height];
		Hanoi[top].Disk[Hanoi[top].depth][2][height] = Temp.Disk[Temp.depth][2][height];
	}

	//temp = Hanoi[top].Disk[Hanoi[top].depth][from][from_index];
	Hanoi[top].Disk[Hanoi[top].depth][to][to_index + 1] = Hanoi[top].Disk[Hanoi[top].depth][from][from_index];
	Hanoi[top].Disk[Hanoi[top].depth][from][from_index] = 0;

}

bool checkGoalState(){
	bool check = true;
	
	for(int i = 0; i < DISK_NUM; i++){
		if(Temp.Disk[Temp.depth][PIN_NUM - 1][i] != DISK_NUM - i) check = false;
	}

	return check;
}
