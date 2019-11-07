#define _CRT_SECURE_NO_WARNINGS
#define MAX (1024)

#include<stdio.h>
#include<stdlib.h>

typedef struct polinom* pol;
typedef struct polinom
{
	int koef;
	int exp;
	pol next;
}polinom;

int BrojRedakaDatoteke(const char*);
void StvoriPolList(int, int, pol);
void CitajDat(const char*, pol);
void Sort(pol);
void Zbrajanje(pol, pol, pol);
void Ispis(pol);
void Mnozenje(pol, pol, pol);

int main(void)
{
	polinom head1, head2, zbrhead, mnozihead;
	const char* imedatoteke1 = "datoteka1.txt";
	const char* imedatoteke2 = "datoteka2.txt";
	head1.next = NULL;
	head2.next = NULL;
	zbrhead.next = NULL;
	mnozihead.next = NULL;


	CitajDat(imedatoteke1,&head1);
	CitajDat(imedatoteke2, &head2);

	printf("Prvi polinom:");	
	Sort(&head1);
	Ispis(&head1);
	printf("\nDrugi polinom:"); 
	Sort(&head2);
	Ispis(&head2);
	printf("\nNakon zbrajanja polinoma:");
	Zbrajanje(&head1, &head2, &zbrhead);
	Ispis(&zbrhead);
	printf("\nNakon mnozenja polinoma:");
	Mnozenje(&head1, &head2, &mnozihead);
	Ispis(&mnozihead);
	
	return 0;
}

int BrojRedakaDatoteke(const char* imedatoteke)
{
	int br_r = 0;
	char zn[MAX];
	FILE* fp = NULL;

	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
	{
		printf("Error");
		return 0;
	}

	while (!feof(fp))
	{
		fgets(zn, MAX, fp);
		br_r++;
	}

	fclose(fp);

	return br_r;
} 



void CitajDat(const char* imedatoteke, pol p)
{
	int koef = 0;
	int exp = 0;
	int br_r = BrojRedakaDatoteke(imedatoteke);
	int n;

	FILE* fp;
	fp = fopen(imedatoteke, "r");

	while (!feof(fp))
	{
		for (n = 0; n < br_r; n++)
		{
			fscanf(fp, "%d %d", &koef, &exp);
			StvoriPolList(koef, exp, p);
		}
	}
	fclose(fp);

}

void StvoriPolList(int koef, int exp, pol p)
{
	pol q;
	q = (pol)malloc(sizeof(struct polinom));

	q->koef = koef;
	q->exp = exp;

	while (p->next != NULL)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;
}

void Zbrajanje(pol p1, pol p2, pol zbr)
{
	pol temp;
	
	p1 = p1->next;
	p2 = p2->next;
	while (p1 != NULL && p2 != NULL)

	{
		if (p1->exp == p2->exp)
		{
			StvoriPolList(p1->koef + p2->koef,p1->exp,zbr);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->exp > p2->exp)
		{
			StvoriPolList(p1->koef, p1->exp, zbr);
			p1 = p1->next;
		}
		else
		{
			StvoriPolList(p2->koef, p2->exp, zbr);
			p2 = p2->next;
		}
	}

	if (p1 != NULL)
		temp = p1;
	else temp = p2;

	while (temp != NULL)
	{
		StvoriPolList(temp->koef,temp->exp, zbr);
		temp = temp->next;
	}
}

void Sort(pol p)
{
	pol x, pret_x, temp, kraj;
	kraj = NULL;

	while (p->next != kraj)
	{
		pret_x = p;
		x = p->next;

		while (x->next != kraj)
		{
			if (x->exp < x->next->exp)
			{
				temp = x->next;
				pret_x->next = temp;
				x->next = temp->next;
				temp->next = x;

				x = temp;
			}
			pret_x = x;
			x = x->next;
		}
		kraj = x;
	}

}

void Mnozenje(pol p1, pol p2, pol mn)
{
	p1 = p1->next;
	p2 = p2->next;
	pol temp = p2;
	
	while (p1!= NULL)
	{
		while (p2!= NULL)
		{
			StvoriPolList(p1->koef * p2->koef, p1->exp + p2->exp, mn);
			p2 = p2->next;
		}
		p2 = temp;
		p1 = p1->next;
	}
	
}

void Ispis(pol p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%dX^(%d)\t", p->koef, p->exp);
		p = p->next;
	}
}