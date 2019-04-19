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
	// �ذ� �ִ� Instance
	char *ListA[3] = {"1", "10111", "10"};
	char *ListB[3] = {"111", "10", "0"};
	*/
	
	// �ذ� ���� Instance
	char *ListA[3] = {"10", "011", "101"};
	char *ListB[3] = {"101", "11", "011"};
	
	char strTemp[50], strMadeA[200], strMadeB[200], strBackupA[200], strBackupB[200], strBackupTemp[50], str[2];
	int nCount, nLen, nCheck = 0, nNum, nExit = 0;

	// ����ü �ʱ�ȭ
	memset(&Queue, 0, sizeof(Node) * 1000);
	
	// �迭 �ʱ�ȭ
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
		
		// ó�� ����� ���ϱ� ����....
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
		
		// ���ڿ� �߰��ϱ� ��(����� �� ���� ��) ���
		strcpy(strBackupA, strMadeA);
		strcpy(strBackupB, strMadeB);
		
		for(int i = 0; i < 3; i++)
		{
			int nLenA, nLenB;

			nCheck = 0;

			// ť���� ������ ������ ��������
			strcpy(strMadeA, strBackupA);
			strcpy(strMadeB, strBackupB);
			strcpy(strTemp, strBackupTemp);
			
			nCount = strlen(strTemp);
			
			// ����� ���� ���� ���ڿ� �߰�
			strcat(strMadeA, ListA[i]);
			strcat(strMadeB, ListB[i]);
			
			// ���� ������� ����� �� ���ڿ� ���� ���ϱ�
			nLenA = strlen(strMadeA);
			nLenB = strlen(strMadeB);

			// ���ڿ��� ���� �Ϳ� �� Ƚ���� ���߱� ����...
			if( nLenA <= nLenB)
				nLen = nLenA;
			else
				nLen = nLenB;
			
			// ��ġ�ϴ� ���� ī��Ʈ
			for(j = 0; j < nLen; j++)
			{
				if(strMadeA[j] == strMadeB[j])
					nCheck++;
			}
			
			// ��ġ�ϴ� ������ �ִٸ�....
			if(nCheck == nLen)
			{
				char str[2] = {0};
				itoa(i+1, str, 10);

				if(nCount+1 > 50)
					break;
				
				strTemp[nCount++] = str[0];
				strTemp[nCount] = '\0';
				
				strcpy(Queue[nFront++].History, strTemp);				

				// �ڸ��� ���ڿ� ���̱��� ���ٸ� �ظ� ã�� ���̹Ƿ� ����
				if(nCheck == nLenA && nCheck == nLenB)
				{
					nExit = 1;
					break;
				}
			}			
		}

		if(nExit == 1)
		{
			printf("Find it!!!\n�� : %s\n", strTemp);
			break;
		}
	}

	if(nExit == 0)
	{
		printf("�ظ� ã�� ���߽��ϴ�.\n");
	}
	
}
