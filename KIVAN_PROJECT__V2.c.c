#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct stog* pozicija;
typedef struct stog
{
	int el;
	pozicija next;
}stog;

void CitajDat(const char*, pozicija);
void Push(pozicija, int);
int Pop(pozicija);
int Operator(pozicija, char);

int main(void)
{
	int rez;
	const char* imedatoteke = "postfix.txt";
	stog head;
	head.next = NULL;
	CitajDat(imedatoteke, &head);

	rez = Pop(&head);
	printf("%d", rez);
	
	return 0;
}


void CitajDat(const char* imedatoteke, pozicija s)
{
	int x;
	char niz[20];
	int rez;
	char y;

	FILE* fp;
	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
		printf("Error\n");

	while (!feof(fp))
	{
		fscanf(fp, " %s", niz);
	}
	fclose(fp);

	for (int i = 0; i < strlen(niz); i++)
	{
		if (niz[i] >= 48 && niz[i] <= 57)
		{
			Push(s, niz[i]-48);
		}
		else
			Operator(s, niz[i]);
	}	
}
	

void Push(pozicija s, int x)
{
	pozicija q;

	q = (pozicija)malloc(sizeof(stog));

	q->el = x;
	q->next = s->next;
	s->next = q;
}

int Pop(pozicija s)
{
	int b;
	pozicija temp;

	if (s->next != NULL)
	{
		temp = s->next;
		s->next = s->next->next;
		b = temp->el;
		free(temp);

		return b;
	}

	else return 0;
}

int Operator(pozicija s, char y)
{
	int x, z;
	int br;

	z = Pop(s);
	x = Pop(s);

	switch (y)
	{
	case '+':
		br = x + z;
		break;
	case '-':
		br = x - z;
		break;
	case '*':
		br = x * z;
		break;
	case '/':
		br = x / z;
		break;

	default:
		printf("Error!");
	}

	Push(s, br);
	return 0;
}

