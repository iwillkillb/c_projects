
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
int NUMPOINT = 0;			// 점들의 수
float* distanceOfRoot;		// (0,0)부터 해당 점까지의 거리
float** distanceEachOther;	// 점들 서로간의 거리. 해당 행부터 해당 열까지.

struct Point {
	float x;
	float y;
};

float Distance(Point p1, Point p2) {
	float re;
	float rx, ry;

	rx = (p1.x > p2.x) ? p1.x - p2.x : p2.x - p1.x;	rx *= rx;
	ry = (p1.y > p2.y) ? p1.y - p2.y : p2.y - p1.y;	ry *= ry;

	re = rx + ry;		re = (float)sqrt(re);
	return re;
}

void Swap(int *data, int a, int b) {
	int swap;
	swap = data[a];
	data[a] = data[b];
	data[b] = swap;
}

void Print(const int *v, const int size)
{
	float distance;	//최종적으로 출력할 거리
	distance = distanceOfRoot[v[0]];	//가장 먼저 (0,0)부터 첫번째 점까지의 거리를 구한다.

	if (v != 0) {
		printf("(0,0) -> ");
		for (int i = 0; i < size; i++) {
			if (i > 0)	//각 점부터 자신 이전의 점까지의 거리를 더한다.
				distance += distanceEachOther[v[i - 1]][v[i]];
			printf("%d -> ", v[i] + 1);
			if (i == size - 1)	//마지막으로 마지막 점에서 (0,0)까지의 거리를 더한다.
				distance += distanceOfRoot[v[i]];
		}
		printf("(0,0), 거리의 합 : %.2f \n", distance);
		distance = 0;	//거리 변수는 다시 초기화.
	}
} // print

void RotateLeft(int *v, const int start, const int n)
{
	int i;
	int tmp = v[start];
	for (i = start; i<n - 1; i++) {
		v[i] = v[i + 1];
	}
	v[n - 1] = tmp;
} // rotateLeft

void Permute(int *v, const int start, const int n)
{

	if (start < n) {
		int i, j;
		for (i = n - 2; i >= start; i--) {
			for (j = i + 1; j < n; j++) {
				Swap(v, i, j);
				Permute(v, i + 1, n);
			} // for j
			RotateLeft(v, i, n);
		} // for i
	}
} // permute

  //======================================================

int main() {

	Point* points;	//점들의 배열. 이걸 전역으로 하는건 안됨.
	int* numRoot;	//함수들이 사용하는 각 점들의 index
	float sumDistance = 0;
	int a, b;
	Point zero;	zero.x = 0;	zero.y = 0;	//(0,0) 원점
	float time_gap = 0; //시간측정용
	time_t time_start = 0, time_end = 0;

	//Input the number of points.
	printf("점의 최대 개수는? ");
	scanf("%d", &NUMPOINT);

	while (NUMPOINT <= 2) {
		printf("점의 개수는 2개보다 많아야 합니다. 다시 입력해주세요 : ");
		scanf("%d", &NUMPOINT);
	}

	//Give memory
	numRoot = (int *)malloc(sizeof(int) * NUMPOINT);
	points = (Point *)malloc(sizeof(Point) * NUMPOINT);
	distanceOfRoot = (float *)malloc(sizeof(float) * NUMPOINT);
	distanceEachOther = (float **)malloc(sizeof(float *) * NUMPOINT);


	for (a = 0; a < NUMPOINT; a++) {
		numRoot[a] = a;
		distanceEachOther[a] = (float *)malloc(sizeof(float) * NUMPOINT);
	}

	//각 좌표들 자동 지정
	for (a = 0; a < NUMPOINT; a++) {
		points[a].x = (float)a;
		points[a].y = (float)a;
	}
	//----------------------------------------------------

	for (a = 0; a < NUMPOINT; a++) {//거리를 저장하는 배열들 초기화
		distanceOfRoot[a] = Distance(zero, points[a]);

		for (b = 0; b < NUMPOINT; b++) {
			distanceEachOther[a][b] = Distance(points[a], points[b]);
		}
	}

	//실제 함수들을 사용하는 부분! Permutation 측정 시작.
	for (a = 3; a <= NUMPOINT; a++) {
		time_start = clock();
		Permute(numRoot, 0, a);	//NEXT PERMUTATION !!
		time_end = clock();
		time_gap = (float)(time_end - time_start) / (CLOCKS_PER_SEC);
		printf("%2d개 -> 경과 시간 : %.10f \n", a, time_gap);
	}


	//Return Memory---------------
	free(numRoot);
	free(points);
	free(distanceOfRoot);
	for (a = 0; a < NUMPOINT; a++) {
		free(distanceEachOther[a]);
	}
	free(distanceEachOther);
	return 0;
}
