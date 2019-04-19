
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
int NUMPOINT = 0;			// ������ ��
float* distanceOfRoot;		// (0,0)���� �ش� �������� �Ÿ�
float** distanceEachOther;	// ���� ���ΰ��� �Ÿ�. �ش� ����� �ش� ������.

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
	float distance;	//���������� ����� �Ÿ�
	distance = distanceOfRoot[v[0]];	//���� ���� (0,0)���� ù��° �������� �Ÿ��� ���Ѵ�.

	if (v != 0) {
		printf("(0,0) -> ");
		for (int i = 0; i < size; i++) {
			if (i > 0)	//�� ������ �ڽ� ������ �������� �Ÿ��� ���Ѵ�.
				distance += distanceEachOther[v[i - 1]][v[i]];
			printf("%d -> ", v[i] + 1);
			if (i == size - 1)	//���������� ������ ������ (0,0)������ �Ÿ��� ���Ѵ�.
				distance += distanceOfRoot[v[i]];
		}
		printf("(0,0), �Ÿ��� �� : %.2f \n", distance);
		distance = 0;	//�Ÿ� ������ �ٽ� �ʱ�ȭ.
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

	Point* points;	//������ �迭. �̰� �������� �ϴ°� �ȵ�.
	int* numRoot;	//�Լ����� ����ϴ� �� ������ index
	float sumDistance = 0;
	int a, b;
	Point zero;	zero.x = 0;	zero.y = 0;	//(0,0) ����
	float time_gap = 0; //�ð�������
	time_t time_start = 0, time_end = 0;

	//Input the number of points.
	printf("���� �ִ� ������? ");
	scanf("%d", &NUMPOINT);

	while (NUMPOINT <= 2) {
		printf("���� ������ 2������ ���ƾ� �մϴ�. �ٽ� �Է����ּ��� : ");
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

	//�� ��ǥ�� �ڵ� ����
	for (a = 0; a < NUMPOINT; a++) {
		points[a].x = (float)a;
		points[a].y = (float)a;
	}
	//----------------------------------------------------

	for (a = 0; a < NUMPOINT; a++) {//�Ÿ��� �����ϴ� �迭�� �ʱ�ȭ
		distanceOfRoot[a] = Distance(zero, points[a]);

		for (b = 0; b < NUMPOINT; b++) {
			distanceEachOther[a][b] = Distance(points[a], points[b]);
		}
	}

	//���� �Լ����� ����ϴ� �κ�! Permutation ���� ����.
	for (a = 3; a <= NUMPOINT; a++) {
		time_start = clock();
		Permute(numRoot, 0, a);	//NEXT PERMUTATION !!
		time_end = clock();
		time_gap = (float)(time_end - time_start) / (CLOCKS_PER_SEC);
		printf("%2d�� -> ��� �ð� : %.10f \n", a, time_gap);
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
