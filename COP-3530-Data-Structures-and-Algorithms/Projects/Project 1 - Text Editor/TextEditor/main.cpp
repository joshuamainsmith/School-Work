#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int max = 0;

typedef struct Node
{
	char data[100];
	struct Node* next;
	struct Node* prev;
	int line;
}node;


void insert(node* pointer, char data[100], int line)
{
	if (pointer == NULL || line < 1)
	{
		return;
	}
	
	node *prevNode, *newNode;
	newNode = (node*)malloc(sizeof(node));
	strcpy(newNode->data, data);	

	prevNode = NULL;
	
	while (pointer != NULL && pointer->line < line)
	{
		prevNode = pointer;
		pointer = pointer->next;	
	}

	if (prevNode == NULL)
	{
		while (pointer->next != NULL)
		{
			pointer = pointer->next;
		}

		pointer->next = (node*)malloc(sizeof(node));
		(pointer->next)->prev = pointer;
		pointer = pointer->next;
		strcpy(pointer->data, (pointer->prev)->data);
		pointer->line = (pointer->prev)->line + 1;
		pointer->next = NULL;

		max = pointer->line;

		pointer = pointer->prev;

		while ((pointer->prev)->line > 0)
		{
			strcpy(pointer->data, (pointer->prev)->data);
			pointer->line = (pointer->prev)->line + 1;			
			pointer = pointer->prev;
		}

		strcpy(pointer->data, data);
		pointer->line = 1;

		return;
	}

	else
	{
		prevNode->next = newNode;
		newNode->next = pointer;
		newNode->prev = prevNode;
		pointer->prev = newNode;
		newNode->line = prevNode->line + 1;
	}


	while (pointer != NULL)
	{		
		pointer->line = pointer->line + 1;
		max = pointer->line;
		pointer = pointer->next;
	}
}

void del(node* pointer, int line)
{
	while (pointer->next != NULL && (pointer->next)->line != line)
	{
		pointer = pointer->next;
	}

	if (pointer->next == NULL)
	{
		return;
	}

	node* temp;
	temp = pointer->next;
	pointer->next = temp->next;
	temp->prev = pointer;
	free(temp);
	
	max--;

	while (pointer->next != NULL)
	{
		pointer->next->line--;
		pointer = pointer->next;
	}

	return;
}

void insertEnd(node* pointer, char data[100])
{
	int i = 1;
	
	while (pointer->next != NULL)
	{
		pointer = pointer->next;
		pointer->line = i++;
	}
	
	pointer->next = (node*)malloc(sizeof(node));
	(pointer->next)->prev = pointer;
	pointer = pointer->next;
	strcpy(pointer->data, data);
	pointer->line = i++;
	pointer->next = NULL;

	max++;
}


int find(node* pointer, char key[100])
{
	int found = 0;
	pointer = pointer->next; 
	while (pointer != NULL)
	{
		if (strstr(pointer->data, key)) 
		{
			printf("%d %s\n", pointer->line, pointer->data);
			found = 1;
		}
		pointer = pointer->next;
	}

	if (found == 0)
	{
		printf("not found\n");
	}
	
	return 0;
}

int edit(node* pointer, int lineNum, char newLine[100])
{
	pointer = pointer->next; 
	while (pointer != NULL)
	{
		if (pointer->line == lineNum) 
		{
			strcpy(pointer->data, newLine);
			return 0;
		}
		pointer = pointer->next;
	}
	
	return 1;
}


int print(node* pointer)
{
	if (pointer == NULL)
	{
		return 1;
	}

	printf("%d %s", pointer->line, pointer->data);

	if (pointer->next != NULL)
	{
		printf("\n");
		print(pointer->next);
	}

	return 0;
}

void parseString(char * ptrLineStr, char buffer[100], char lineStr[100])
{
	int i = 0;
	
	for (i = 0; i <= strlen(ptrLineStr) - 1; i++)
	{
		if (ptrLineStr[i] != '\"')
			lineStr[i - 1] = ptrLineStr[i];
	}
	lineStr[strlen(ptrLineStr) - 2] = '\0';
}

int parseLineNum(char buffer[100], char lineNum[4])
{
	int i = 0, iLineNum = 0;
	while (buffer[i] != '\"' && buffer[i] != '\0')
	{
		if (buffer[i] == '-')
		{
			return -1;
		}
		if (buffer[i] >= 48 && buffer[i] <= 57)
		{
			strncat(lineNum, &buffer[i], 1);
		}
		i++;
	}
	iLineNum = atoi(lineNum);

	return iLineNum;
}

int check(node* pointer, int line)
{
	if (pointer == NULL)
	{
		return 1;
	}

	while (pointer->next != NULL)
	{
		pointer = pointer->next;
	}

	if (pointer->line < line)
	{
		return 1;
	}

	return 0;
}

int main()
{	
	node* start, * temp;
	start = (node*)malloc(sizeof(node));
	temp = start;
	temp->next = NULL;
	temp->prev = NULL;

	char buffer[100];
	char command[10];
	char *ptrLineStr, lineStr[100], lineNum[4];
	int i = 0, iLineNum = 0, err = 0;

	while (!strstr(command, "quit"))
	{
		scanf("%[^\n]%*c", &buffer);
		ptrLineStr = strstr(buffer, "\"");

		// Get Command
		memcpy(command, &buffer, 9);

		if (strstr(command, "insertEnd"))	// done
		{
			// command string
			parseString(ptrLineStr, buffer, lineStr);
			insertEnd(start, lineStr);
		}

		else if (strstr(command, "insert"))
		{
			// command line string
			parseString(ptrLineStr, buffer, lineStr);
			iLineNum = parseLineNum(buffer, lineNum);
			err = check(start->next, iLineNum);

			if (iLineNum < 1 || iLineNum > max)
			{
				err = 1;
			}
			
			if (iLineNum == max + 1)
			{
				insertEnd(start, lineStr);
			}

			else if (!err)
			{
				insert(start->next, lineStr, iLineNum);
			}
			err = 0;
		}

		else if (strstr(command, "delete"))	// done
		{
			// command line
			iLineNum = parseLineNum(buffer, lineNum);

			if (iLineNum >= 1 || iLineNum <= max)
				del(start, iLineNum);
		}

		else if (strstr(command, "edit"))	// done
		{
			// command line string
			parseString(ptrLineStr, buffer, lineStr);
			iLineNum = parseLineNum(buffer, lineNum);
			if (iLineNum >= 1 || iLineNum <= max)
				edit(start, iLineNum, lineStr);
		}

		else if (strstr(command, "search"))	// done
		{
			// command string
			parseString(ptrLineStr, buffer, lineStr);
			find(start, lineStr);
		}

		else if (strstr(command, "print"))	// done
		{
			// command
			err = print(start->next);

			if (err == 0)
			{
				printf("\n");
			}
		}

		// Clear line number for next use
		memset(&lineNum[0], 0, sizeof(lineNum));
		if (!strstr(command, "quit"))
		{
			memset(command, 0, sizeof command);
		}
		memset(buffer, 0, sizeof buffer);

	}

}