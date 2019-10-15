#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_BR_BOD (25)
#define MAX (230)

typedef struct popis;
typedef struct popis* ptr;

typedef struct popis
{
	char ime[MAX];
	char prezime[MAX];
	int bodovi;

}student;


int BrojRedakaDatoteke(const char*);
void UpisStudenata(struct popis*, const char*,int);
float RelBrBod(int);

int main(void)
{
	const char* imedatoteke = "studenti.txt";
	int br_r = 0;
	struct popis* ptr;

	br_r = BrojRedakaDatoteke(imedatoteke);
	printf("\nBroj redaka datoteke je: %d \n", br_r);

	ptr = (struct popis*)malloc(br_r*sizeof(struct popis));

	UpisStudenata(ptr, imedatoteke, br_r);



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

void UpisStudenata(struct popis* ptr, const char* imedatoteke, int br_stud)
{
	int n = 0;
	char naziv[MAX];

	
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "r");

	if (fp == NULL)
	{
		printf("Error");
		return 0;
	}

	while (!feof(fp))
	{
		for (n=0; n < br_stud; n++)
		{
			fscanf(fp,"%s",&ptr[n].ime);
			fscanf(fp,"%s",&ptr[n].prezime);
			fscanf(fp,"\t%d", &ptr[n].bodovi);
		}
	}
	fclose(fp);

	for (n=0; n < br_stud; n++)
	{
		printf("%s\t%s\t%d\t%f\n", ptr[n].ime, ptr[n].prezime, ptr[n].bodovi, RelBrBod(ptr[n].bodovi) );
	}
}

float RelBrBod(int br_bodova)
{
	float rel_br_bod;

	rel_br_bod = ((float)br_bodova / MAX_BR_BOD) * 100;
	
	return rel_br_bod;
}