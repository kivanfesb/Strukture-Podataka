#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Lista* pol;
typedef struct Lista
{
	int el;
	pol next;
}lista;

void CitajDat(const char*, pol);
void StvoriList(int, pol);
void Ispis(pol);
void Unija(pol, pol, pol);
void Presjek(pol, pol, pol);

int main(void)
{
	const char* imedatoteke1 = "L1.txt";
	const char* imedatoteke2 = "L2.txt";
	lista head1, head2, hunija, hpresjek;
	head1.next = NULL;
	head2.next = NULL;
	hunija.next = NULL;
	hpresjek.next = NULL;


	CitajDat(imedatoteke1, &head1);
	CitajDat(imedatoteke2, &head2);
	printf("Lista 1 je:\n");
	Ispis(&head1);
	printf("\nLista 2 je:\n");
	Ispis(&head2);
	Unija(&head1, &head2, &hunija);
	printf("\nElementi unije su:\n");
	Ispis(&hunija);
	Presjek(&head1, &head2, &hpresjek);
	printf("\nElementi presjeka su:\n");
	Ispis(&hpresjek);
	printf("\n");

	system("pause");
	return 0;
}

void CitajDat(const char* imedatoteke, pol p)
{
	int n;
	FILE* fp;
	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
		printf("Error");

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &n);
		StvoriList(n, p);

	}
	fclose(fp);

}

void StvoriList(int el, pol p)
{
	pol q;
	q = (pol)malloc(sizeof(lista));

	q->el = el;

	q->next = p->next;
	p->next = q;

}

void Ispis(pol p)
{
	p = p->next;

	while (p!= NULL)
	{
		printf("%d\t", p->el);
		p = p->next;
	}

}

void Unija(pol l1, pol l2, pol unija)
{
	pol temp;
	l1 = l1->next;
	l2 = l2->next;

	while (l1!= NULL && l2!= NULL)
	{
		if (l1->el > l2->el)
		{
			StvoriList(l1->el, unija);
			l1 = l1->next;
		}

		else if (l1->el < l2->el)
		{
			StvoriList(l2->el, unija);
			l2 = l2->next;
		}

		else
		{
			StvoriList(l1->el, unija);
			l1 = l1->next;
			l2 = l2->next;
		}

	}

	if (l1 == NULL)
	{
		temp = l2;
		StvoriList(temp->el, unija);
	}
	else
	{
		temp = l1;
		StvoriList(temp->el, unija);
	}

}

void Presjek(pol l1, pol l2, pol presjek)
{
	l1 = l1->next;
	l2 = l2->next;

	while (l1 != NULL && l2 != NULL)
	{
		if (l1->el == l2->el)
		{
			StvoriList(l1->el, presjek);
			l1 = l1->next;
			l2 = l2->next;
		}

		else if (l1->el > l2->el)
		{
			l1 = l1->next;
		}

		else
			l2 = l2->next;

	}
}