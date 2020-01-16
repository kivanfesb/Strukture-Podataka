#define _CRT_SECURE_NO_WARNINGS
#define TABLE_size (11)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HASHTABLE* pos;
typedef struct student* person;

struct HASHTABLE
{
	int HASH_key;
	pos next;
	person next;
}HT;

struct student
{
	int id;
	const char* name;
	const char* surname;
	
}st;

void MakeHASH(int,const char*,const char*,pos);
int HASH(const char*,int);

int main(void)
{
	
	
	return 0;
}


int HASH(const char* surname,int table_size)
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

void MakeHASH(int id,const char* name, const char* surname,pos first)
{
	pos x;
	pos prev;
	
	x=first->next;
	
	
	pos newpart;
	
	newpart=(pos)malloc(sizeof(HASHTABLE));
	
	key=HASH(surname,TABLE_size);
	
	newpart->next->id=id;
	strcpy(newpart->next->name,name);
	strcpy(newpart->next->surname,surname);
	
	while(first->HASH_key<TABLE_size+1)
	{
		if(key>x->HASH_key)
		{
			//idi dalje u listi da nadjes gdje po red utreab bit pa tu stvori 
			prev=x;
			x=x->next;
			
		}
	
		else if(key<x->HASH_key)
		{	//napravi ispred tog u listi
			newpart->next=x;
			prev->next=newpart;
		}
		else
		//jednaki su pa treba na tom mjestu ih povezati u listu
		
	}
	
}
