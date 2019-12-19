#define _CRT_SECURE_NO_WARNINGS
#define N (1000)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct direktorij* poddirektorij;
typedef struct stog* pozicija;
typedef struct direktorij
{
	char ime[N];
	poddirektorij child;
	poddirektorij next;
}dir;

typedef struct stog
{
	poddirektorij adresa;
	pozicija next;
}stog;

void StvoriChild(poddirektorij d, char ime[]);
void StvoriNext(poddirektorij d, char ime[]);
void PushStog(pozicija p, poddirektorij adr);
poddirektorij PopStog(pozicija p);
poddirektorij posljednji(pozicija p);
void Ispis(poddirektorij p);
poddirektorij CheckIn(char input1[], char input2[], poddirektorij current, pozicija head, poddirektorij root);
int Find(poddirektorij current, char name[]);
poddirektorij Wanted(poddirektorij current, char name[]);

int main(void)
{
	poddirektorij current;
	stog head;
	head.next = NULL;
	dir root;
	root.next = NULL;
	char pocetni[N];
	char input1[N];
	char input2[N];
	char copy[N];

	printf("Unesite ime glavnog direktorija:\n");
	scanf("%s", pocetni);
	StvoriNext(&root, pocetni);
	printf("Root direktorij je: %s\n", pocetni);
	//memset(input, '\0', strlen(input));
	current = root.next;

	do
	{
		printf("Enter a command:\n");
		scanf("%s %s", input1, input2);
		strcpy(copy, input2);
		current = CheckIn(input1, input2, current, &head, &root);
		memset(input1, '\0', strlen(input1));
		memset(input2, '\0', strlen(input2));

	} while (strcmp(copy, "EXIT") != 0 && strcmp(copy, "exit") != 0);

	printf("You exited");

	return 0;
}

poddirektorij CheckIn(char input1[], char input2[], poddirektorij current, pozicija head, poddirektorij root)
{
	poddirektorij x;
	char name[N];

	if (strcmp(input1, "cd") == 0 && strcmp(input2, "") != 0)
	{
		int n;
		poddirektorij target;
		strcpy(name, input2);
		n = Find(current, name);
		if (n > 0)
		{
			target = Wanted(current, name);
			PushStog(&head, target);
		}
		else
			printf("\nNon-existent directory!\n");

		x = current;
	}

	else if (strcmp(input1, "cd") == 0 && strcmp(input2, "") == 0)
	{
		if (posljednji(&head) == NULL)
		{
			printf("\nError!\n");
			x = current;
		}
		else
		{
			x = PopStog(&head);
		}
	}

	else if (strcmp(input1, "dir") == 0 && strcmp(input2, "") == 0)
	{
		Ispis(current);
		x = current;
	}

	else if (strcmp(input1, "md") == 0 && strcmp(input2, "") != 0)
	{
		strcpy(name, input2);

		if (current->child != NULL)
		{
			StvoriNext(current->child, name);
		}
		else
			StvoriChild(current, name);

		x = current;
	}

	else
	{
		if (strcmp(input1, "EXIT") != 0 && strcmp(input1, "exit") != 0)
		{
			printf("\nUnknown command!\n");
		}
		x = current;
	}

	return x;
}



void StvoriChild(poddirektorij d, char ime[])
{
	poddirektorij p;
	p = (poddirektorij)malloc(sizeof(dir));

	strcpy(p->ime, ime);
	p->child = d->child;
	p->next = NULL;
	d->child = p;
}

void StvoriNext(poddirektorij d, char ime[])
{
	poddirektorij p;
	p = (poddirektorij)malloc(sizeof(dir));


	strcpy(p->ime, ime);
	p->next = d->next;
	d->next = p;
	p->child = NULL;

}

void PushStog(pozicija p, poddirektorij adr)
{
	pozicija q;
	q = (pozicija)malloc(sizeof(stog));

	q->adresa = adr;
	q->next = p->next;
	p->next = q;
}

poddirektorij PopStog(pozicija p)
{
	pozicija q;
	poddirektorij adr;

	p = p->next;

	if (p != NULL)
	{
		q = p;
		p->next = p->next->next;
		adr = q->adresa;
		free(p);
		return adr;
	}

	return 0;
}


poddirektorij posljednji(pozicija p)
{
	poddirektorij adr;

	while (p->next != NULL)
		p = p->next;

	adr = p->adresa;
	return adr;
}

void Ispis(poddirektorij p)
{
	printf("\t%s\n", p->child->ime);
	p = p->child->next;
	while (p != NULL)
	{
		printf("\t%s\n", p->ime);
		p = p->next;
	}
}

int Find(poddirektorij current, char name[])
{
	int n = 0;

	while (current != NULL)
	{
		if (strcmp(current->ime, name) == 0)
			n++;
		current = current->next;
	}

	return n;
}

poddirektorij Wanted(poddirektorij current, char name[])
{
	poddirektorij x;

	while (strcmp(current->ime, name) != 0)
	{
		x = current;
		current = current->next;
	}
	x = current->next;
	return x;
}

