#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX (1024)


typedef struct osoba* Personposition;
struct osoba
{
	char name[MAX];
	char surname[MAX];
	Personposition next;
	
}Osoba;


typedef struct list* Countyposition;
struct list
{
	char name[MAX];
	char surname[MAX];
	char number[MAX];
	char county[MAX];
	Countyposition nextCounty;
	struct osoba person;

}Zupanija;


void ReadFile(char* fileName, Countyposition root);
void Add(char* name, char* surname, char* number, char* county, Countyposition newPerson);
void Allocation(char* name, char* surname, char* number, char* county, Countyposition newPerson);
void AllocationSameCounty(char* name, char* surname, Personposition root);
void Input(Countyposition root, char* fileName);
void Delete(Countyposition root);

int main(void)
{
	Countyposition root;
	char fileName[MAX];
	char fileToSave[MAX];
	printf("Unesite ime datoteke: ");
	scanf("%s",fileName);

	ReadFile(fileName,root);
	printf("Unesite ime datoteke za spremiti podatke: ");
	scanf("%s",fileToSave);
	Input(root,fileToSave);
	Delete(root);

	system("pause");
	return 0;
}

void ReadFile(char* fileName,Countyposition root)
{
	char ime[MAX];
	char prezime[MAX];
	char broj[MAX];
	char zupanija[MAX];
	char text[MAX];
	FILE* fp = NULL;

	fp = fopen(fileName,"r");

	if (!fp)
	{
		printf("Error!");
		return;
	}

	while (!feof(fp))
	{
		fgets(text, MAX, fp);
		sscanf(text,"%s %s %s %s",ime,prezime,broj,zupanija);
		Add(ime,prezime,broj,zupanija,root);
	}

	fclose(fp);
}

void Add(char* name, char* surname, char* number, char* county, Countyposition head)
{
	Countyposition newPerson = NULL;
	int x = 0;

	if (!head)
	{
		Allocation(name, surname, number, county, head);
		newPerson->nextCounty = head->nextCounty;
		head->nextCounty = newPerson;
	}

	x = strcmp(head->county, newPerson->county);

	if (x > 0)
	{
		Allocation(name, surname, number, county, head);
		head->nextCounty = newPerson->nextCounty;
		newPerson->nextCounty = head;
	}

	else if (x < 0)
	{
		head = head->nextCounty;
		Add(name, surname, number, county, head);
	}

	else
	{
		AllocationSameCounty(name,surname,&head->person);
	}
}

void Allocation(char* name,char* surname, char* number, char* county, Countyposition newPerson)
{
	newPerson = (Countyposition)malloc(sizeof(Zupanija));

	strcpy(newPerson->name,name);
	strcpy(newPerson->surname, surname);
	strcpy(newPerson->number, number);
	strcpy(newPerson->county,county);
	newPerson->person.next = nullptr;
	strcpy(newPerson->person.name,"0");
	strcpy(newPerson->person.surname, "0");
}

void AllocationSameCounty(char* name,char* surname,Personposition root)
{
	Personposition newPerson;
	newPerson = (Personposition)malloc(sizeof(osoba));

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname,surname);

	newPerson->next=root->next;
	root->next = newPerson;
}

void Input(Countyposition root,char* fileName)
{
	FILE* fp = NULL;

	fp = fopen(fileName,"w");

	if (!root)
	{
		fprintf(fp,"Error");
		return;
	}

	while (root != NULL)
	{
		fprintf(fp,"%s:\n",root->county);

		if (root->person.next != NULL)
		{
			while (root->person.next != NULL)
			{
				fprintf(fp,"%s %s",root->person.name,root->person.surname);
				root->person.next = root->person.next->next;
			}
		}
		else
			root = root->nextCounty;
	}
}

void Delete(Countyposition root)
{
	Countyposition temp;

	if (!root)
		free(root);

	while (root->nextCounty!= NULL)
	{
		temp = root;
		temp = root->nextCounty;
		root->nextCounty = temp->nextCounty;
		free(temp);
		root = root->nextCounty;
	}
}