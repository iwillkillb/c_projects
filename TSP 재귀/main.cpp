#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <memory.h>

#include <windows.h>

#include <time.h>




#define MAX 150




int *xpoint;

int *ypoint;

int vertex, s = 1;

int point, depth = 0;




float during_t;

LARGE_INTEGER frequency, start_t, finish_t;




void greedy(int a);

int way(int b);




int main()

{
	int input;
	int i = 0;

	int txp = 0, typ = 0;

	printf("최대 점의 개수 : ");
	scanf("%d", &input);
	for(int a=2 ; a<=input ; a++){
	
	
	printf("number of vertexies ? : ");

	//scanf("%d", &vertex);
	vertex = a;



	xpoint = (int*)malloc(vertex);

	ypoint = (int*)malloc(vertex);

	

	xpoint[0] = 0;

	ypoint[0] = 0;

	




	for(i = 1; i < vertex; i++)

	{

		printf("vertex_%d point ? ex)17 2 ex1)xpoint ypoint : ", i);

		//scanf("%d %d", &txp , &typ);
		txp = i*10;
		typ = i*9;

		xpoint[i] = txp;

		ypoint[i] = typ;

	}

	

	point = 0;

	

	printf("포인트의 값: %d\n", point);




	srand(time(NULL));

    QueryPerformanceFrequency( &frequency );

	

	QueryPerformanceCounter( &start_t );




	while(s)

	{	

		greedy(point);

	}




	

	QueryPerformanceCounter( &finish_t );  // get finish time..

	

    during_t = ( (float)finish_t.QuadPart - (float)start_t.QuadPart ) / (float)frequency.QuadPart * (float)1000.0;

	

	if( during_t < 1000.) // print millisecond

        printf("* During Time .. %.4f(msec)\n", during_t);

    else if( during_t/1000. < 60.) // print second

        printf("* During Time .. %.1f(sec)\n", during_t/1000);

    else if( during_t/60000. < 60.) // print min

        printf("* During Time .. %.0f(min)\n", during_t/60000.);

    else  //print hour

        printf("* During Time .. %.0f(hour)\n", during_t/3600000.);




	xpoint=NULL;

	ypoint=NULL;

	free(xpoint);

	free(ypoint);
	
}

}




void greedy(int a)

{

	int t1;

	

	if(depth+1 == vertex)

	{

		s = 0;

	} else {

		t1 = way(point);

		printf("이동할 vertex는 : %d\n", point);

		depth++;

		greedy(point);

	}

}




int way(int b)

{

	int temp[MAX] = {0};

	int t[MAX] = {0};

	int i;

	int x, y;

	int t1;

	

	x = xpoint[b];

	y = ypoint[b];

	

	xpoint[b] = 0;

	ypoint[b] = 0;

	

	for(i = 1; i < vertex; i++)

	{

		if((xpoint[i] != 0)&&(ypoint[i] !=0))

		{

			temp[i] = (int)(pow((xpoint[i] - x) ,2) + pow((ypoint[i] - y), 2));

			temp[i] = (int)(sqrt(temp[i]));

		}

		else

		{

			continue;

		}

	}




	for(i = 0; i < vertex; i++)

	{

		t[i] = temp[i];

	}




	for(i = 0; i < vertex; i++)

	{

		if(t[i] != 0)

		{

			t1 = t[i];

			break;

		}

	}




	for(i = 0; i < vertex; i++)

	{

		if(temp[i] != 0)

		{

			if(temp[i] < t1)

			{

				t1 = temp[i];

			}

			else

			{

				t1 = t1;

			}

		}

	}




	printf("\n최소 거리 : %d ", t1);

	

	for(i = 0; i < vertex; i++)

	{

		if(temp[i] == t1)

		{

			point = i;

		}

	}

	

	return t1;

}

