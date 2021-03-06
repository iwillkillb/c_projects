/*

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define MAXINT 99999999
struct Point {
	int x;
	int y;
};
int numPoint = 0;	//Number of Points.
Point zero;
Point* points;
int** memory;
int** distance;




int Distance(Point p1, Point p2) {
	double re;
	double rx, ry;
	rx = (p1.x > p2.x) ? p1.x - p2.x : p2.x - p1.x;
	ry = (p1.y > p2.y) ? p1.y - p2.y : p2.y - p1.y;
	rx *= rx;
	ry *= ry;

	re = rx + ry;
	re = sqrt(re);

	return (int)re;
}


int TSP(int cur, int vis) {
	int next;

	if (vis == (1 << numPoint) - 1)	return distance[cur][0];

	int& ret = memory[cur][vis];
	if (ret != 0)return ret;
	ret = MAXINT;

	for (next = 0; next <= numPoint; next++) {
		if (vis & (1 << next))	continue;
		if (distance[cur][next] == 0)continue;
		//ret = min(ret,TSP(next,vis | (1 << next)) + distance[cur][next]);
		ret = ret < TSP(next, vis | (1 << next)) + distance[cur][next] ?
			ret : TSP(next, vis | (1 << next)) + distance[cur][next];
	}
	return ret;
}








void InputDistances() {
	int a, b;

	for (a = 0; a<numPoint; a++) {
		for (b = 0; b<numPoint; b++) {
			distance[a][b] = Distance(points[a], points[b]);
			printf("%d ", distance[a][b]);
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------------

int main() {


	int a;
	zero.x = 0;
	zero.y = 0;


	//Input the number of points.
	printf("점의 개수는? ");
	scanf_s("%d", &numPoint);

	while (numPoint < 2) {
		printf("점의 개수는 2개보다 많아야 합니다. 다시 입력해주세요 : ");
		scanf_s("%d", &numPoint);
	}

	//Memory
	points = (Point *)malloc(sizeof(Point) * numPoint);
	memory = (int **)malloc(sizeof(int)*numPoint);
	distance = (int **)malloc(sizeof(int)*numPoint);
	for (a = 0; a<numPoint; a++) {
		memory[a] = (int *)malloc(sizeof(int) * 1 << (numPoint - 1));
		distance[a] = (int *)malloc(sizeof(int) * numPoint);
	}

	//Input Points XY.
	for (a = 0; a < numPoint; a++) {
		printf("%d번째 점의 좌표는? ", a + 1);
		scanf_s("%d %d", &points[a].x, &points[a].y);
	}
	printf("\n");


	InputDistances();


	printf("%d\n", TSP(0, 1));





	//return memory
	free(points);
	for (a = 0; a<numPoint; a++) {
		free(memory[a]);
		free(distance[a]);
	}
	free(memory);
	free(distance);
	return 0;
}*/