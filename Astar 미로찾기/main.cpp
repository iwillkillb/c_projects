#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <math.h>
#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //���� ť���� �ε����� �����ϴ� ��ũ�� �Լ�


//�̷� ���� �Լ���---------------------------------------------------------
struct Point{
	int h,w;			//�� ������ ��ġ. maze[h][w]�� ã�´�. 
	int cost;			//������������ ���. ���� �Ÿ��� �̷��� �����Ÿ��� �� 
	Point* pre = NULL;	//������ ��ġ��? 
};
Point start, goal, now;	//�����, ������, ���� ��ġ 
int** maze;	// 2�����迭 �̷�.
/*
	0 : ���
	1 : �� 
	2 : �����
	3 : ������ 
*/
int mazeH, mazeW;	//�̷��� ��,��. ���Ͽ� ���� �����迭�ϱ����� ������ ����. 

void MazeInit();	//�̷θ� �ʱ�ȭ�ϴ� �Լ� 
void MazePrint();	//�̷θ� ����Ѵ�. ������ ���� ����. 
void MazeFree();	//�̷� �迭�� �޸� ��ȯ(����) 
void MazeSetStartAndGoal();	//�̷��� ������� �������� ����. 
//-------------------------------------------------------------------------

//ť ���� �Լ���-----------------------------------------------------------
typedef struct Queue //Queue ����ü ����
{
	Point *buf;//�����
	int qsize;
	int front; //���� �ε���(���� �������� ������ �����Ͱ� �ִ� �ε���)
	int rear;//������ �ε���
	int count;//���� ����

}Queue;
void InitQueue(Queue *queue, int qsize);//ť �ʱ�ȭ
int IsFull(Queue *queue); //ť�� �� á���� Ȯ��
int IsEmpty(Queue *queue); //ť�� ������� Ȯ��
void Enqueue(Queue *queue, Point data); //ť�� ����
Point Dequeue(Queue *queue); //ť���� ����
void DisposeQueue(Queue *queue);//ť ����ȭ

// �� �Ʒ��� �Լ����� ���� ���� ����Ŷ�, ������ ���� �� �ֽ��ϴ�. 
bool IsPassed(Queue *queue, Point data);	//�� �����Ͱ� ť�� �ִ°�?
Point PrintQueue(Queue *queue);				//���� ������ �����͸� ��ȯ�ϵ�, ť�� ������ ������ �ʴ´�.
void SortingQueue(Queue *queue);			//ť�� �����Ѵ�. (��������) 
//--------------------------------------------------------------------------

//�ΰ����� ���� �Լ���------------------------------------------------------
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
	Queue openList, closeList;	//���� : ...(*queue �ڸ����� &queue�� �ִ´�.)
	int costPast = 0, costFuture = 0;	//���.
	Point newPoint[4];				//�߰��� ĭ 4���� 
	InitQueue(&openList, 100);	//Open ť �ʱ�ȭ
	InitQueue(&closeList, 100);	//Close ť �ʱ�ȭ
	Point p1;
	
	// 1. ���� ��ġ open�� �߰�(������ �� 1����?)
	now = start;
	Enqueue(&openList,now);
	
	/*
	ť ��� ��� 
	Point p1;
	Enqueue(&openList,p1);		//ť�� ����ֱ� 
	p1 = Dequeue(&openList);	//ť���� ������. ����ü�̹Ƿ�, �̸� ����ü ������ �����س��°� ����. 
	
	
	�ΰ������� ���� 
	
	1. ���� ��ġ open�� �߰�(������ �� 1����?)
	
	2. ��>��>��>�� �� ����̰�(0), �̵����� ����(close�� ����) ĭ���� open�� �߰�
		(�� �������� �� �� �ִ� ĭ�� ������ �������� ã�� ���ϰ� ����!)
	
	3. ���� ĭ�� open���� close��. close�� �߰��� ĭ�� ������(3)���� �˻��Ѵ�!
		(�������̸�, �������� ã�� ����!)
	
	4. open�� �߰��� ĭ���� �Ÿ��� ���(F=G+H), ���� ª�� ĭ�� �����Ͽ� ���� ĭ����.
	
	5. 2~4 �ݺ�
	*/
	
	while(1){
		// 2. ��>��>��>�� �� ����̰�(0), �̵����� ����(close�� ����) ĭ���� open�� �߰�
		// (�� �������� �� �� �ִ� ĭ�� ������ �������� ã�� ���ϰ� ����!)
		
		// �׸��� �� ������ ĭ���� �Ÿ����(cost)�� ����س��´�. 
		// costFuture : �� ��ġ�� ������������ ���α��� ���� + ���α��� ����
		// costPast : ���ݱ��� �̵��ߴ� Ƚ�� 
		// �� �� �Ÿ� ��ġ�� ���ؼ� ť�� �ش� ������ cost�� �����Ѵ�. 
		
		/*
		if(�迭�� �����ڸ��ΰ�?){
			if(�ش� ĭ�� ���� �ƴѰ�?  &&  �̹� ������ ������ �ƴ�, ���ο� �����ΰ�?){
				newPoint.h = �ش� ĭ�� �� 
				newPoint.w = �ش� ĭ�� �� 
				costFuture = �ش� ĭ�� ������������ ���α��� + ���α��� 
				newPoint.cost = ���� costFuture��, ���ݱ��� ������ Ƚ��(costPast)�� ���Ѵ�. 
				newPoint.pre = �ش� ĭ�� ���� �ܰ�� ���� ĭ���� �����Ѵ�. 
				
				Enqueue(&openList,newPoint); //������ ���� �������� ����, ť�� �߰��Ѵ�. 
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
		
		if(now.h > 0){						// �� ���� ���� �ƴϰ�, 
			p1.h = now.h-1;
			p1.w = now.w;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h-1][now.w] != 1  &&  !IsPassed(&closeList, p1)){	// ���� ĭ���� ������ �� �ִ� ���... 
				printf("���� �����.\n");
				newPoint[0].h = now.h-1;
				newPoint[0].w = now.w;
				costFuture = abs(newPoint[0].h - goal.h) + abs(newPoint[0].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[0].cost = costPast + costFuture;
				newPoint[0].pre = &now; 
				
				Enqueue(&openList,newPoint[0]);
			}
			else printf("���� ��.\n");
		}
		else printf("���� ����.\n");
			
		if(now.h < mazeH-1){				// �� �Ʒ��� ���� �ƴϰ�, 
			p1.h = now.h+1;
			p1.w = now.w;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h+1][now.w] != 1  &&  !IsPassed(&closeList, p1)){	// �Ʒ��� ĭ���� ������ �� �ִ� ���... 
				printf("�Ʒ��� �����.\n");
				newPoint[1].h = now.h+1;
				newPoint[1].w = now.w;
				costFuture = abs(newPoint[1].h - goal.h) + abs(newPoint[1].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[1].cost = costPast + costFuture;
				newPoint[1].pre = &now; 
				
				Enqueue(&openList,newPoint[1]);
			}
			else printf("�Ʒ��� ��.\n");
		}
		else printf("�Ʒ��� ����.\n");
		
		if(now.w > 0){						// �� ������ ���� �ƴϰ�, 
			p1.h = now.h;
			p1.w = now.w-1;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h][now.w-1] != 1  &&  !IsPassed(&closeList, p1)){	// ������ ĭ���� ������ �� �ִ� ���... 
				printf("������ �����.\n");
				newPoint[2].h = now.h;
				newPoint[2].w = now.w-1;
				costFuture = abs(newPoint[2].h - goal.h) + abs(newPoint[2].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[2].cost = costPast + costFuture;
				newPoint[2].pre = &now; 
				
				Enqueue(&openList,newPoint[2]);
			}
			else printf("������ ��.\n");
		}
		else printf("������ ����.\n");
			
		if(now.w < mazeW-1){				// �� �������� ���� �ƴϰ�, 
			p1.h = now.h;
			p1.w = now.w+1;
			printf("%d, ", IsPassed(&closeList, p1));
			if(maze[now.h][now.w+1] != 1  &&  !IsPassed(&closeList, p1)){	// �������� ĭ���� ������ �� �ִ� ���... 
				printf("�������� �����.\n");
				newPoint[3].h = now.h;
				newPoint[3].w = now.w+1;
				costFuture = abs(newPoint[3].h - goal.h) + abs(newPoint[3].w - goal.w);
				printf("costFuture : %d \n", costFuture);
				newPoint[3].cost = costPast + costFuture;
				newPoint[3].pre = &now; 
				
				Enqueue(&openList,newPoint[3]);
			}
			else printf("�������� ��.\n");
		}
		else printf("�������� ����.\n");
		
		costPast++;	//�� ĭ�� ������ ������ costPast�� 1�� ����. 
		
		// 3. ���� ĭ�� open���� close��. close�� �߰��� ĭ�� ������(3)���� �˻��Ѵ�!
		p1 = Dequeue(&openList);
		Enqueue(&closeList, p1);
		SortingQueue(&openList);	// openť�� �����Ѵ�. 
		printf("p1��ġ : [%d][%d]\n\n", p1.h, p1.w);
		if(p1.h==goal.h && p1.w==goal.w){	// (�������̸�, �������� ã�� ����!)
			printf("=== GOAL !!! ===\n");
			break;
		}
		
		// 4. open�� �߰��� ĭ���� �Ÿ��� ��(F=G+H), ���� ª�� ĭ�� �����Ͽ� ���� ĭ����.
		for(int a=0 ; a<3 ; a++){
			if(newPoint[a].cost < newPoint[a+1].cost)
				now = newPoint[a];
			else now = newPoint[a+1];
		}
	}
	
	
	
	
	
	
	
	DisposeQueue(&openList);	//Open ť �ݱ� 
	DisposeQueue(&closeList);	//Close ť �ݱ� 
}



void MazeInit(){
	FILE* file = fopen("maze.txt","r");	//�̷� ����� ��� �ܺ��� ���� 
	char read;	//������ ���� �� ���� �ӽ� ���� 
	int wCount=0,hCount=0, a,b;
	
	while(!feof(file)){	//ù��° �б� : �̷��� ũ�⸦ �����Ѵ�. 
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
	printf("�̷��� ũ�� : %d�� X %d�� \n",mazeH,mazeW);
	
	maze = (int **)malloc(sizeof(int *) * mazeH);	//���� ũ�⿡ ���� �̷� �迭�� �޸� �Ҵ� 
	for(a=0 ; a<mazeH ; a++){
		maze[a] = (int *)malloc(sizeof(int) * mazeW);
	}
	
	file = fopen("maze.txt","r");	//�̷� ����� ��� �ܺ��� ���� 
	
	for(a=0 ; a<mazeH ; a++){	//�ι�° �б� : �̷��� �����͸� maze[][]�� �Է½�Ų��. 
		for(b=0 ; b<mazeW ; b++){
			fscanf(file,"%d",&maze[a][b]);
		}
	}
	
	Sleep(1000);
	fclose(file);
}



void MazePrint(){
	system("cls");
	
	printf("  �� : ");
	for(int a=0 ; a<mazeW ; a++)
		printf("%2d",a);
	printf("\n");
	for(int a=0 ; a<mazeH ; a++){
			printf("%2d�� : ",a);
		for(int b=0 ; b<mazeW ; b++){
			switch(maze[a][b]){
				case 0:	//��� 
					printf("��");
					break;
				case 1:	//�� 
					printf("��");
					break;
				case 2:	//������ 
					printf("��");
					break;
				case 3:	//������ 
					printf("��");
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
	
	printf("�̷��� �������? (��,��) ");
	scanf("%d %d", &inputH, &inputW);
	while(inputH<0 || inputH>=mazeH   ||   inputW<0 || inputW>=mazeW   ||   maze[inputH][inputW] != 0){
		printf("���� ������, ���� �ƴ� ������ �������ּ���. (��,��) ");
		scanf("%d %d", &inputH, &inputW);
	}
	start.h = inputH;
	start.w = inputW;
	maze[start.h][start.w] = 2;
	
	printf("�̷��� ��������? (��,��) ");
	scanf("%d %d", &inputH, &inputW);
	while(inputH<0 || inputH>=mazeH   ||   inputW<0 || inputW>=mazeW   ||   maze[inputH][inputW] != 0){
		printf("���� ������, ���� �ƴ� ������, �������� ��ġ�� �ʰ� �������ּ���. (��,��) ");
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
	if (IsEmpty(queue))//ť�� ����� ��
	{
		printf("ť�� �����\n");
		return re;
	}
	re = queue->buf[queue->front];//front �ε����� ������ ���� re�� ����
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
void Enqueue(Queue *queue, Point data)
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
Point Dequeue(Queue *queue)
{
	Point re;
	re.h = 0;
	re.w = 0;
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
