#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define MAX (1024)


typedef struct osoba* pozicija;

struct osoba
{
	char ime[MAX];
	char prezime[MAX];
	int god_rod;
	pozicija next;
};



void UnosPocetak(char*, char*, int, pozicija);
void UnosKraj(char*, char*, int, pozicija);
pozicija Trazi(char*, pozicija);
void BrisiElement(char*, pozicija);
pozicija TraziPreth(char*, pozicija);
void Ispis(pozicija);

int main(void)
{
	struct osoba head;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int god_rod = 0;
	pozicija poz_trazi = NULL;

	head.next = NULL;

	UnosPocetak("Karla", "Brkan", 2000, &head);
	UnosKraj("Ivan", "Budisa", 2000, &head);
	UnosKraj("Gordana", "Batinic", 2000, &head);
	UnosKraj("Roko", "Galic", 1999, &head);

	poz_trazi=Trazi("Batinic", head.next);

	printf("Elementi liste su:\n");
	Ispis(&head);
	
	printf("\nTrazeni element je:%s\t%s\t%d\n", poz_trazi->ime, poz_trazi->prezime, poz_trazi->god_rod);

	BrisiElement("Galic", &head);

	printf("\nElementi liste nakon brisanja su:\n");
	Ispis(&head);
	

	system("pause");

	return 0;
}

void UnosPocetak(char* ime, char* prezime, int god_rod, pozicija p)
{
	pozicija q;


	q = (pozicija)malloc(sizeof(struct osoba));

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->god_rod = god_rod;
	q->next = p->next;
	p->next = q;
}

void UnosKraj(char* ime, char* prezime, int god_rod, pozicija p)
{
	pozicija q;

	q = (pozicija)malloc(sizeof(struct osoba));

	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->god_rod = god_rod;

	while (p->next!=NULL)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

}

pozicija Trazi(char* prezime, pozicija p)
{
	while (p!=NULL && strcmp(p->prezime, prezime) != 0)
	{
		p = p->next;
	}

	return p;
}

void Ispis(pozicija p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("%s\t%s\t%d\n", p->ime, p->prezime, p->god_rod);
		p = p->next;
	}
}

void BrisiElement(char* prezime, pozicija p)
{
	pozicija temp;
	p = TraziPreth(prezime, p);

	if (p == NULL)
		printf("Element ne postoji!");

	else
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}


}

pozicija TraziPreth(char* prezime, pozicija p)
{
	pozicija pret = p;
	p = p->next;

	while (p != NULL && strcmp(p->prezime, prezime) != 0)
	{
		pret = p;
		p = p->next;
	}

	if (NULL == p)
		return NULL;

	else return pret;

}
