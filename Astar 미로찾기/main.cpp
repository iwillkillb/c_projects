#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <math.h>
#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //원형 큐에서 인덱스를 변경하는 매크로 함수


//미로 관련 함수들---------------------------------------------------------
struct Point{
	int h,w;			//이 지점의 위치. maze[h][w]로 찾는다. 
	int cost;			//목적지까지의 비용. 과거 거리와 미래의 예측거리의 합 
	Point* pre = NULL;	//이전의 위치는? 
};
Point start, goal, now;	//출발점, 도착점, 현재 위치 
int** maze;	// 2차원배열 미로.
/*
	0 : 통로
	1 : 벽 
	2 : 출발점
	3 : 도착점 
*/
int mazeH, mazeW;	//미로의 행,열. 파일에 따라 동적배열하기위해 변수로 만듦. 

void MazeInit();	//미로를 초기화하는 함수 
void MazePrint();	//미로를 출력한다. 아이콘 변경 가능. 
void MazeFree();	//미로 배열의 메모리 반환(종료) 
void MazeSetStartAndGoal();	//미로의 출발점과 도착점을 설정. 
//-------------------------------------------------------------------------

//큐 관련 함수들-----------------------------------------------------------
typedef struct Queue //Queue 구조체 정의
{
	Point *buf;//저장소
	int qsize;
	int front; //꺼낼 인덱스(가장 오래전에 보관한 데이터가 있는 인덱스)
	int rear;//보관할 인덱스
	int count;//보관 개수

}Queue;
void InitQueue(Queue *queue, int qsize);//큐 초기화
int IsFull(Queue *queue); //큐가 꽉 찼는지 확인
int IsEmpty(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, Point data); //큐에 보관
Point Dequeue(Queue *queue); //큐에서 꺼냄
void DisposeQueue(Queue *queue);//큐 해제화

// 이 아래의 함수들은 제가 직접 만든거라, 오류가 있을 수 있습니다. 
bool IsPassed(Queue *queue, Point data);	//이 데이터가 큐에 있는가?
Point PrintQueue(Queue *queue);				//가장 오래된 데이터를 반환하되, 큐에 영향을 주지는 않는다.
void SortingQueue(Queue *queue);			//큐를 정렬한다. (선택정렬) 
//--------------------------------------------------------------------------

//인공지능 관련 함수들------------------------------------------------------
void Astar();
//--------------------------------------------------------------------------



int main() 
{
	MazeInit();
	
	
	MazePrint();
	MazeSetStartAndGoal();
	MazePrint();
	
	Astar();
	
	MazeFree();
	return 0;
}



void Astar(){
	Queue openList, closeList;	//사용법 : ...(*queue 자리에는 &queue를 넣는다.)
	int costPast = 0, costFuture = 0;	//비용.
	Point newPoint[4];				//추가할 칸 4방향 
	InitQueue(&openList, 100);	//Open 큐 초기화
	InitQueue(&closeList, 100);	//Close 큐 초기화
	Point p1;
	
	// 1. 현재 위치 open에 추가(시작할 때 1번만?)
	now = start;
	Enqueue(&openList,now);
	
	/*
	큐 사용 요령 
	Point p1;
	Enqueue(&openList,p1);		//큐에 집어넣기 
	p1 = Dequeue(&openList);	//큐에서 빼내기. 구조체이므로, 미리 구조체 변수를 선언해놓는게 좋음. 
	
	
	인공지능의 순서 
	
	1. 현재 위치 open에 추가(시작할 때 1번만?)
	
	2. 상>하>좌>우 중 통로이고(0), 이동하지 않은(close에 없는) 칸들을 open에 추가
		(위 조건으로 갈 수 있는 칸이 없으면 목적지를 찾지 못하고 종료!)
	
	3. 현재 칸은 open에서 close로. close에 추가된 칸이 목적지(3)인지 검사한다!
		(목적지이면, 목적지를 찾고 종료!)
	
	4. open에 추가된 칸들의 거리를 계산(F=G+H), 가장 짧은 칸을 선택하여 현재 칸으로.
	
	5. 2~4 반복
	*/
	
	while(1){
		// 2. 상>하>좌>우 중 통로이고(0), 이동하지 않은(close에 없는) 칸들을 open에 추가
		// (위 조건으로 갈 수 있는 칸이 없으면 목적지를 찾지 못하고 종료!)
		
		// 그리고 각 방향의 칸들의 거리비용(cost)을 계산해놓는다. 
		// costFuture : 이 위치와 목적지까지의 가로길이 차이 + 세로길이 차리
		// costPast : 지금까지 이동했던 횟수 
		// 이 두 거리 수치를 더해서 큐의 해당 데이터 cost에 보관한다. 
		
		/*
		if(배열의 가장자리인가?){
			if(해당 칸이 벽이 아닌가?  &&  이미 지나간 지점이 아닌, 새로운 지점인가?){
				newPoint.h = 해당 칸의 행 
				newPoint.w = 해당 칸의 열 
				costFuture = 해당 칸과 목적지까지의 가로길이 + 세로길이 
				newPoint.cost = 위의 costFuture와, 지금까지 지나온 횟수(costPast)를 더한다. 
				newPoint.pre = 해당 칸의 이전 단계는 현재 칸으로 설정한다. 
				
				Enqueue(&openList,newPoint); //위에서 만든 정보들을 토대로, 큐에 추가한다. 
			}
		}
		*/
		for(int a=0 ; a<3 ; a++){
			newPoint[a].h = 0;
			newPoint[a].w = 0;
			newPoint[a].cost = mazeH * mazeW;
		}
		
		p1 = now;
		printf("now[%d][%d], cost : %d \n", now.h,now.w,now.cost);
		
		if(now.h > 0){						// 맨 위의 행이 아니고, 
			p1.h = now.h-1;
			p1.w = now.w;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h-1][now.w] != 1  &&  !IsPassed(&closeList, p1)){	// 위의 칸으로 지나갈 수 있는 경우... 
				printf("위는 비었어.\n");
				newPoint[0].h = now.h-1;
				newPoint[0].w = now.w;
				costFuture = abs(newPoint[0].h - goal.h) + abs(newPoint[0].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[0].cost = costPast + costFuture;
				newPoint[0].pre = &now; 
				
				Enqueue(&openList,newPoint[0]);
			}
			else printf("위는 벽.\n");
		}
		else printf("위가 없어.\n");
			
		if(now.h < mazeH-1){				// 맨 아래의 행이 아니고, 
			p1.h = now.h+1;
			p1.w = now.w;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h+1][now.w] != 1  &&  !IsPassed(&closeList, p1)){	// 아래의 칸으로 지나갈 수 있는 경우... 
				printf("아래는 비었어.\n");
				newPoint[1].h = now.h+1;
				newPoint[1].w = now.w;
				costFuture = abs(newPoint[1].h - goal.h) + abs(newPoint[1].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[1].cost = costPast + costFuture;
				newPoint[1].pre = &now; 
				
				Enqueue(&openList,newPoint[1]);
			}
			else printf("아래는 벽.\n");
		}
		else printf("아래가 없어.\n");
		
		if(now.w > 0){						// 맨 왼쪽의 열이 아니고, 
			p1.h = now.h;
			p1.w = now.w-1;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h][now.w-1] != 1  &&  !IsPassed(&closeList, p1)){	// 왼쪽의 칸으로 지나갈 수 있는 경우... 
				printf("왼쪽은 비었어.\n");
				newPoint[2].h = now.h;
				newPoint[2].w = now.w-1;
				costFuture = abs(newPoint[2].h - goal.h) + abs(newPoint[2].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[2].cost = costPast + costFuture;
				newPoint[2].pre = &now; 
				
				Enqueue(&openList,newPoint[2]);
			}
			else printf("왼쪽은 벽.\n");
		}
		else printf("왼쪽은 없어.\n");
			
		if(now.w < mazeW-1){				// 맨 오른쪽의 열이 아니고, 
			p1.h = now.h;
			p1.w = now.w+1;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h][now.w+1] != 1  &&  !IsPassed(&closeList, p1)){	// 오른쪽의 칸으로 지나갈 수 있는 경우... 
				printf("오른쪽은 비었어.\n");
				newPoint[3].h = now.h;
				newPoint[3].w = now.w+1;
				costFuture = abs(newPoint[3].h - goal.h) + abs(newPoint[3].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[3].cost = costPast + costFuture;
				newPoint[3].pre = &now; 
				
				Enqueue(&openList,newPoint[3]);
			}
			else printf("오른쪽은 벽.\n");
		}
		else printf("오른쪽은 없어.\n");
		
		costPast++;	//한 칸씩 움직일 때마다 costPast는 1씩 증가. 
		
		// 3. 현재 칸은 open에서 close로. close에 추가된 칸이 목적지(3)인지 검사한다!
		p1 = Dequeue(&openList);
		Enqueue(&closeList, p1);
		SortingQueue(&openList);	// open큐를 정렬한다. 
		printf("p1위치 : [%d][%d]\n\n", p1.h, p1.w);
		if(p1.h==goal.h && p1.w==goal.w){	// (목적지이면, 목적지를 찾고 종료!)
			printf("=== GOAL !!! ===\n");
			break;
		}
		
		// 4. open에 추가된 칸들의 거리를 비교(F=G+H), 가장 짧은 칸을 선택하여 현재 칸으로.
		for(int a=0 ; a<3 ; a++){
			if(newPoint[a].cost < newPoint[a+1].cost)
				now = newPoint[a];
			else now = newPoint[a+1];
		}
	}
	
	
	
	
	
	
	
	DisposeQueue(&openList);	//Open 큐 닫기 
	DisposeQueue(&closeList);	//Close 큐 닫기 
}



void MazeInit(){
	FILE* file = fopen("maze.txt","r");	//미로 모양이 담긴 외부의 파일 
	char read;	//파일을 읽을 때 쓰는 임시 변수 
	int wCount=0,hCount=0, a,b;
	
	while(!feof(file)){	//첫번째 읽기 : 미로의 크기를 측정한다. 
		fscanf(file,"%c",&read);
		if(read == '\n'){
			hCount++;
		}
		else if(read != ' '){
			wCount++;
		}
	}
	fclose(file);
	
	mazeH = ++hCount;
	mazeW = (int)((wCount-1) / mazeH);
	printf("미로의 크기 : %d행 X %d열 \n",mazeH,mazeW);
	
	maze = (int **)malloc(sizeof(int *) * mazeH);	//위의 크기에 따라 미로 배열의 메모리 할당 
	for(a=0 ; a<mazeH ; a++){
		maze[a] = (int *)malloc(sizeof(int) * mazeW);
	}
	
	file = fopen("maze.txt","r");	//미로 모양이 담긴 외부의 파일 
	
	for(a=0 ; a<mazeH ; a++){	//두번째 읽기 : 미로의 데이터를 maze[][]에 입력시킨다. 
		for(b=0 ; b<mazeW ; b++){
			fscanf(file,"%d",&maze[a][b]);
		}
	}
	
	Sleep(1000);
	fclose(file);
}



void MazePrint(){
	system("cls");
	
	printf("  열 : ");
	for(int a=0 ; a<mazeW ; a++)
		printf("%2d",a);
	printf("\n");
	for(int a=0 ; a<mazeH ; a++){
			printf("%2d행 : ",a);
		for(int b=0 ; b<mazeW ; b++){
			switch(maze[a][b]){
				case 0:	//통로 
					printf("□");
					break;
				case 1:	//벽 
					printf("■");
					break;
				case 2:	//시작점 
					printf("ⓢ");
					break;
				case 3:	//도착점 
					printf("ⓖ");
					break;
				default:
					printf("? ");
					break;
			}
		}
		printf("\n");
	}
}



void MazeFree(){
	for(int a=0 ; a<mazeH ; a++){
		free(maze[a]);
	}
	free(maze);
}



void MazeSetStartAndGoal(){
	int inputH = -1, inputW = -1;
	
	printf("미로의 출발점은? (행,열) ");
	scanf("%d %d", &inputH, &inputW);
	while(inputH<0 || inputH>=mazeH   ||   inputW<0 || inputW>=mazeW   ||   maze[inputH][inputW] != 0){
		printf("범위 내에서, 벽이 아닌 곳으로 선택해주세요. (행,열) ");
		scanf("%d %d", &inputH, &inputW);
	}
	start.h = inputH;
	start.w = inputW;
	maze[start.h][start.w] = 2;
	
	printf("미로의 도착점은? (행,열) ");
	scanf("%d %d", &inputH, &inputW);
	while(inputH<0 || inputH>=mazeH   ||   inputW<0 || inputW>=mazeW   ||   maze[inputH][inputW] != 0){
		printf("범위 내에서, 벽이 아닌 곳으로, 시작점과 겹치지 않게 선택해주세요. (행,열) ");
		scanf("%d %d", &inputH, &inputW);
	}
	goal.h = inputH;
	goal.w = inputW;
	maze[goal.h][goal.w] = 3;
	printf("\n");
}








bool IsPassed(Queue *queue, Point data){
	Queue tempQueue = *queue;
	Point po;
	int a;
	
	while(!IsEmpty(&tempQueue)){
		po = Dequeue(&tempQueue);
		if(po.h==data.h && po.w==data.w)
			return true; 
	}
	
	return false;
}

Point PrintQueue(Queue *queue){
	Point re;
	re.h = 0;
	re.w = 0;
	if (IsEmpty(queue))//큐가 비었을 때
	{
		printf("큐가 비었음\n");
		return re;
	}
	re = queue->buf[queue->front];//front 인덱스에 보관한 값을 re에 설정
	return re;
}

void SortingQueue(Queue *queue){
	int a,b,c;
	Point temp;
	
	for(a=0 ; a<queue->count ; a++){
		b = a;
		for(c=a+1 ; c<queue->count ; c++){
			if(queue->buf[b].cost > queue->buf[c].cost){
				b = c;
			}
				
			temp = queue->buf[a];
			queue->buf[a] = queue->buf[b];
			queue->buf[b] = temp;
			
		}
	}
}



void InitQueue(Queue *queue, int qsize)
{
	queue->buf = (Point *)malloc(sizeof(Point)*qsize);
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
void Enqueue(Queue *queue, Point data)
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
Point Dequeue(Queue *queue)
{
	Point re;
	re.h = 0;
	re.w = 0;
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
