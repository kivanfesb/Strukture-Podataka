#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct cvor* pozicija;
typedef struct cvor* stablo;

typedef struct cvor
{
	int el;
	stablo L;
	stablo R;
}cvor;

stablo Add(int, stablo);
stablo Delete(int, stablo);
void Ispis(stablo);
pozicija Min(stablo);
pozicija Search(int, stablo);


int main(void)
{
	cvor root;
	stablo s = NULL;
	pozicija ptr_el;
	root.L = NULL;
	root.R = NULL;
	int n, i, el, del_el, tr_el;

	printf("Unesite zeljeni broj elemenata binarnog stabla:\n");
	scanf("%d", &n);

	printf("Unesite elemente:\n");

	for (i = 0; i < n; i++)
	{
		scanf("%d", &el);
		s=Add(el, s);
	}
	

	printf("Elementi binarnong stabla su:\n");
	Ispis(s);

	printf("\nKoji element zelite izbrisati?\n");
	scanf("%d", &del_el);

	Delete(del_el, s);

	printf("\nElementi binarnong stabla nakon brisanja su:\n");
	Ispis(s);

	printf("\nKoji element trazite?\n");
	scanf("%d", &tr_el);

	ptr_el = Search(tr_el, s);
	return 0;
}

stablo Add(int el, stablo s)
{
	if (s == NULL)
	{
		s = (stablo)malloc(sizeof(cvor));
		s->el = el;
		s->L = NULL;
		s->R = NULL;
	}

	else if (el < s->el)
	{
		s->L = Add(el, s->L);
	}

	else
	{
		s->R = Add(el, s->R);
	}

	return s;

}

void Ispis(stablo s)
{
	if (s != NULL)
	{
		printf("%d", s->el);
		Ispis(s->L);
		Ispis(s->R);
	}
}

stablo Delete(int el, stablo s)
{
	stablo temp;

	if (s == NULL)
		printf("Trazeni element ne postoji!\n");

	else if (el < s->el)
	{
		s->L = Delete(el, s->L);
	}

	else if (el > s->el)
	{
		s->R = Delete(el, s->R);
	}

	else if (s->L != NULL && s->R != NULL)
	{
		temp = Min(s->R);
		s->el = temp->el;
		s->R = Delete(s->el, s->R);

	}

	else
	{
		temp = s;
		
		if (s->L == NULL)
			s = s->R;

		else
			s = s->L;

		free(temp);

	}

	return s;
}

pozicija Min(stablo s)
{
	if (s == NULL)
		return NULL;

	else if (s->L == NULL)
		return s;

	else
		return Min(s->L);
}

pozicija Search(int el, stablo s)
{
	if (s == NULL)
	{
		printf("Taj element ne postoji!\n");
		return NULL;
	}

	else if (el < s->el)
		return Search(el, s->L);

	else if (el > s->el)
		return Search(el, s->R);

	else
		return s;

}