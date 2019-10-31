
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
void UnosIza(char*, char*, char*, int, pozicija);
void UnosIspred(char*, char*, char*, int, pozicija);
void SortirajListu(pozicija);
void UpisDat(const char*, pozicija);
void CitaDat(const char*, char*, char*, int, pozicija);
int BrojRedakaDatoteke(const char*);
void BrisiSve(pozicija);

void Ispis(pozicija);

int main(void)
{
	struct osoba head;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int god_rod = 0;
	pozicija poz_trazi = NULL;

	head.next = NULL;
	const char* imedatoteke = "VezanaLista.txt";
	FILE* fp = NULL;


	UnosPocetak("Karla", "Brkan", 2000, &head);
	UnosKraj("Ivan", "Budisa", 2000, &head);
	UnosKraj("Gordana", "Batinic", 2000, &head);
	UnosKraj("Roko", "Galic", 1999, &head);

	poz_trazi = Trazi("Batinic", head.next);

	printf("Elementi liste su:\n");
	Ispis(&head);

	printf("\nTrazeni element je:%s\t%s\%d\n", poz_trazi->ime, poz_trazi->prezime, poz_trazi->god_rod);

	BrisiElement("Galic", &head);

	printf("\nElementi liste nakon brisanja su:\n");
	Ispis(&head);

	printf("\nElementi liste nakon dodavanja novog elementa iza:\n");
	UnosIza("Budisa", "Marija", "Gazibaric", 2002, &head);
	Ispis(&head);

	printf("\nElementi liste nakon dodavanja novog elementa ispred:\n");
	UnosIspred("Gazibaric", "Ivan", "Lovrenovic", 2000, &head);
	Ispis(&head);

	SortirajListu(&head);
	printf("\nElementi liste nakon sortiranja:\n");
	Ispis(&head);

	UpisDat(imedatoteke, &head);
	BrisiSve(&head);
	head.next = NULL;
	CitaDat(imedatoteke, ime, prezime, god_rod, &head);
	printf("\nNova lista je:\n");
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

	while (p->next != NULL)
	{
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

}

pozicija Trazi(char* prezime, pozicija p)
{
	while (p != NULL && strcmp(p->prezime, prezime) != 0)
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

void UnosIza(char* pret_prezime, char* ime, char* prezime, int god_rod, pozicija p)
{
	p = Trazi(pret_prezime, p);

	if (p == NULL)
	{
		printf("Error");
	}

	else
	{
		UnosPocetak(ime, prezime, god_rod, p);
	}

}

void UnosIspred(char* slj_prezime, char* ime, char* prezime, int god_rod, pozicija p)
{
	p = TraziPreth(slj_prezime, p);

	if (p == NULL)
	{
		printf("Error");
	}

	else
	{
		UnosPocetak(ime, prezime, god_rod, p);
	}
}

void SortirajListu(pozicija p)
{
	pozicija x, pret_x, temp, kraj;
	kraj = NULL;

	while (p->next != kraj)
	{
		pret_x = p;
		x = p->next;

		while (x->next != kraj)
		{
			if (strcmp(x->prezime, x->next->prezime) > 0)
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

void UpisDat(const char* imedatoteke, pozicija p)
{
	p = p->next;

	FILE* fp = NULL;
	fp = fopen(imedatoteke, "w");

	if (fp == NULL)
	{
		printf("Error");
		return 0;
	}

	while (p != NULL)
	{
		fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->god_rod);
		p = p->next;
	}
	fclose(fp);
}

void CitaDat(const char* imedatoteke, char* ime, char* prezime, int god_rod,pozicija p)
{
	int n = 0;
	int br_r = BrojRedakaDatoteke(imedatoteke);
	FILE* fp;


	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
	{
		printf("Error");
	}
	while (!feof(fp))
	{
		for (n = 0; n < br_r-1; n++)
		{
			fscanf(fp, " %s %s %d ", ime, prezime, &god_rod);
			UnosKraj(ime, prezime, god_rod, p);
		}
	}
	fclose(fp);
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

void BrisiSve(pozicija p)
{

	pozicija temp;
	
	p = p->next;

	while (p->next != NULL)
	{
		temp = p;
		p = p->next;
		free(temp);
	}

	if (p->next == NULL)
	{
		temp = p;
		free(temp);
	}


}
