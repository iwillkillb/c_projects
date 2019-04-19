#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	char History[50];
};

int main()
{
	struct Node Queue[1000];
	int nFront = 0, nRear = 0;
	int i,j;
	/*
	// 해가 있는 Instance
	char *ListA[3] = {"1", "10111", "10"};
	char *ListB[3] = {"111", "10", "0"};
	*/
	
	// 해가 없는 Instance
	char *ListA[3] = {"10", "011", "101"};
	char *ListB[3] = {"101", "11", "011"};
	
	char strTemp[50], strMadeA[200], strMadeB[200], strBackupA[200], strBackupB[200], strBackupTemp[50], str[2];
	int nCount, nLen, nCheck = 0, nNum, nExit = 0;

	// 구조체 초기화
	memset(&Queue, 0, sizeof(Node) * 1000);
	
	// 배열 초기화
	strTemp[0] = '\0';
	strMadeA[0] = '\0';
	strMadeB[0] = '\0';
	strBackupTemp[0] = '\0';
	
	strcpy(Queue[nFront++].History, strTemp);

	while(nFront != nRear)
	{
		if(Queue[nRear++].History[0] != '\0')
		{
			strcpy(strTemp, Queue[nRear-1].History);
			strcpy(strBackupTemp, strTemp);
		}
		
		// 처음 실행시 비교하기 위해....
		if(strlen(strTemp) == 0)
			nCount = 0;
		else
			nCount = strlen(strTemp);
		
		if(nCount > 0)
		{
			sprintf(str, "%c", strTemp[0]);
			nNum = atoi(str) - 1;
			strcpy(strMadeA, ListA[nNum]);
			strcpy(strMadeB, ListB[nNum]);
		}
		
		for(int j = 1; j < nCount; j++)
		{			
			sprintf(str, "%c", strTemp[j]);
			nNum = atoi(str) - 1;
			strcat(strMadeA, ListA[nNum]);
			strcat(strMadeB, ListB[nNum]);
		}
		
		// 문자열 추가하기 전(경우의 수 적용 전) 백업
		strcpy(strBackupA, strMadeA);
		strcpy(strBackupB, strMadeB);
		
		for(int i = 0; i < 3; i++)
		{
			int nLenA, nLenB;

			nCheck = 0;

			// 큐에서 가져온 값으로 돌려놓기
			strcpy(strMadeA, strBackupA);
			strcpy(strMadeB, strBackupB);
			strcpy(strTemp, strBackupTemp);
			
			nCount = strlen(strTemp);
			
			// 경우의 수에 따른 문자열 추가
			strcat(strMadeA, ListA[i]);
			strcat(strMadeB, ListB[i]);
			
			// 각각 만들어진 경우의 수 문자열 길이 구하기
			nLenA = strlen(strMadeA);
			nLenB = strlen(strMadeB);

			// 문자열이 작은 것에 비교 횟수를 맞추기 위해...
			if( nLenA <= nLenB)
				nLen = nLenA;
			else
				nLen = nLenB;
			
			// 일치하는 개수 카운트
			for(j = 0; j < nLen; j++)
			{
				if(strMadeA[j] == strMadeB[j])
					nCheck++;
			}
			
			// 일치하는 내용이 있다면....
			if(nCheck == nLen)
			{
				char str[2] = {0};
				itoa(i+1, str, 10);

				if(nCount+1 > 50)
					break;
				
				strTemp[nCount++] = str[0];
				strTemp[nCount] = '\0';
				
				strcpy(Queue[nFront++].History, strTemp);				

				// 자리와 문자열 길이까지 같다면 해를 찾은 것이므로 종료
				if(nCheck == nLenA && nCheck == nLenB)
				{
					nExit = 1;
					break;
				}
			}			
		}

		if(nExit == 1)
		{
			printf("Find it!!!\n해 : %s\n", strTemp);
			break;
		}
	}

	if(nExit == 0)
	{
		printf("해를 찾지 못했습니다.\n");
	}
	
}
