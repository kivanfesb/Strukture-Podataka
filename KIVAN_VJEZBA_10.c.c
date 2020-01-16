#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cvor* stablo;
typedef struct cvor* pozicija;
typedef struct stog* spozicija;

typedef struct stog
{
	int znak;
	spozicija next;

}stog;

typedef struct cvor
{
	int op;
	stablo L;
	stablo R;
}cvor;

void Push(spozicija, int);
int Pop(spozicija);
void Read(const char*, spozicija, stablo);
void AddNum(int x, stablo s);
stablo AddOp(int, stablo, spozicija, stablo);
int InorderWrite(FILE*, stablo s);
void Write(const char*, stablo);

int main(void)
{
	const char* imedatoteke = "postfix.txt";
	cvor root;
	stablo s = NULL;
	root.L = NULL;
	root.R = NULL;
	stog head;
	head.next = NULL;

	Read(imedatoteke, &head, s);

	return 0;
}

void Read(const char* imedatoteke, spozicija s, stablo st)
{
	int x;
	char niz[20];
	char y;
	stablo temp;
	temp = NULL;

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
			Push(s, niz[i] - 48);
		}
		else
			st = AddOp(niz[i], st, s, temp);
	}
	Write(imedatoteke, st);

}

void Push(spozicija s, int x)
{
	spozicija q;

	q = (spozicija)malloc(sizeof(stog));

	q->znak = x;
	q->next = s->next;
	s->next = q;
}

int Pop(spozicija s)
{
	int b;
	spozicija temp;

	if (s->next != NULL)
	{
		temp = s->next;
		s->next = s->next->next;
		b = temp->znak;
		free(temp);

		return b;
	}

	else return 0;
}


stablo AddOp(int op, stablo st, spozicija s, stablo temp2)
{
	stablo temp1;
	temp1 = st;
	int x, y;

	st = (stablo)malloc(sizeof(cvor));
	st->op = op;
	st->L = NULL;
	st->R = NULL;

	x = Pop(s);
	y = Pop(s);

	if (x > 0 && x <= 9)
	{
		AddNum(x, st);
	}

	if (y > 0 && y <= 9)
	{
		AddNum(y, st);
	}

	if (temp1 != NULL)
	{
		if (st->R == NULL)
		{
			st->R = (stablo)malloc(sizeof(cvor));
			st->R = temp1;
		}

		else if (st->L == NULL)
		{
			st->L = (stablo)malloc(sizeof(cvor));
			st->L = temp1;
		}
		else
		{
			temp2 = temp1;
		}
	}

	if (temp2 != NULL)
	{
		if (st->R == NULL)
		{
			st->R = (stablo)malloc(sizeof(cvor));
			st->R = temp2;
		}

		else if (st->L == NULL)
		{
			st->L = (stablo)malloc(sizeof(cvor));
			st->L = temp2;
		}

	}

	return st;

}


void AddNum(int x, stablo s)
{
	if (s->R == NULL)
	{
		s->R = (stablo)malloc(sizeof(cvor));
		s->op = x;
		s->L = NULL;
		s->R = NULL;
	}

	else
	{
		s->L = (stablo)malloc(sizeof(cvor));
		s->op = x;
		s->L = NULL;
		s->R = NULL;

	}

}


void Write(const char* imedatoteke, stablo s)
{
	int n = 0;

	FILE* fp = NULL;
	fp = fopen(imedatoteke, "w");

	if (fp == NULL)
	{
		printf("Error");
	}

	InorderWrite(fp, s);

	fclose(fp);

}

int InorderWrite(FILE* fp, stablo s)
{
	fprintf(fp, "(");

	InorderWrite(fp, s->L);

	fprintf(fp, "%d", s->op);

	InorderWrite(fp, s->R);

	fprintf(fp, ")");

	return 0;
}