#define _CRT_SECURE_NO_WARNINGS
#define TABLE_size (11)
#define MAX (1024)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HASHTABLE* pos;
typedef struct student* person;

struct HASHTABLE
{
	int HASH_key;
	pos next;
	pos sl_next;
	//sl_next :same letters next tj isti hash_key
	person next;
}HT;

struct student
{
	int id;
	const char* name;
	const char* surname;
	
}st;

void MakeHASH(int,char,char,pos);
int HASH(char,int);

int main(void)
{
	int n;
	char name[MAX];
	char surname[MAX];
	int id;
	pos First=&NULL;
	
	printf("Number of people who will be assigned a table postion:");
	scanf(%d,n);
	
do	{
		printf("Name Surname: ");
		scanf("%s %s",name, surname);
		printf("ID: ");
		scanf("%d",id);
	
		MakeHash(id,name[],surname[],First);
		n--;
	} while(n!=0);
	
	return 0;
}


int HASH(char surname[],int table_size)
{
	int n=0;
	int x=0;
	
	while((surname*!='\0')&&(x<6))
	{
		n+=surname*++;
		x++;
	}
	x=n%table_size;
	return x;
}

void MakeHASH(int id,char name[],char surname[],pos first)
{
	pos x;
	pos temp;
	int res;
	
	x=first->next;
	
	
	pos newpart; //new part of HASH table tj. new person
	
	newpart=(pos)malloc(sizeof(HASHTABLE));
	
	key=HASH(surname,TABLE_size);
	
	newpart->HASH_key=key;
	newpart->next->id=id;
	strcpy(newpart->next->name,name);
	strcpy(newpart->next->surname,surname);
	
	while(x->HASH_key<TABLE_size+1)
	{
		if(key>x->HASH_key)
		{
			//idi dalje u listi da nadjes gdje po red utreab bit pa tu stvori 
			temp=x;
			x=x->next;
			
		}
	
		else if(key<x->HASH_key)
		{	//napravi ispred tog u listi
			newpart->next=x;
			x=temp;
			x->next=newpart;
		}
		else
		{
			//jednaki su pa treba na tom mjestu ih povezati u listu
			res = strcmp(str1, str2);

   			if(res < 0)
			    {
      				//str1 prije dodje po abecedi
   				} 
			else if(res > 0)
				{
      				//str2 prije po abecedi
   				} 
			else 
				{
      				//isto prezime
      				//sad treba usporedba po imenu
  				}
			
		}
				
	}
	
}
