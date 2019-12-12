#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


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


	
	return 0;
}


void CitajDat(const char* imedatoteke, pozicija s)
{
	int x;
	int xi;
	int rez;	
	char y;
	
	FILE* fp;
	fp = fopen(imedatoteke, "r");

	if (fp==NULL)
		printf("Error\n");

	while (!feof(fp))
	{
		x=getc(fp);
		if (x >= 48 && x <= 57)
		{
			switch (x)
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
			Operator(s, x);

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
	fclose(fp);
	
	rez = Pop(s);
	printf("Rezultat je :%d", rez);
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

