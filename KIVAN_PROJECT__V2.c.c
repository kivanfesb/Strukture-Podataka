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
			switch (niz[i])
			{
			case 48:
				Push(s, 0);
				break;

			case 49:
				Push(s, 1);
				break;

			case 50:
				Push(s, 2);
				break;

			case 51:
				Push(s, 3);
				break;
			case 52:
				Push(s, 4);
				break;

			case 53:
				Push(s, 5);
				break;
			case 54:
				Push(s, 6);
				break;

			case 55:
				Push(s, 7);
				break;
			case 56:
				Push(s, 8);
				break;

			case 57:
				Push(s, 9);
				break;

			}

		}
		else
			Operator(s, niz[i]);

		/*if (sscanf(fp, " %d %c", &x, &y))
			Push(s, x);
		else
		{
			//sscanf(imedatoteke, "%c", &y);
			Operator(s, y);
		}

		/*if (fscanf(fp, " %d", &x) >= 0 && fscanf(fp, " %d", &x) <= 9)
			Push(s, x);

		else
			y = (char)x;
		Operator(s, y);*/

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

