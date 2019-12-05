#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct list* pozicija;
typedef struct list
{
	int el;
	pozicija next;
}list;

void PushStog(pozicija);
void PushRed(pozicija);
int Pop(pozicija);
void Ispis(pozicija);

int main(void)
{
	list hstog;
	list hred;
	hstog.next = NULL;
	hred.next = NULL;
	int x;

	PushStog(&hstog);
	PushStog(&hstog);
	PushStog(&hstog);
	PushStog(&hstog);
	PushRed(&hred);
	PushRed(&hred);
	PushRed(&hred);
	PushRed(&hred);
	printf("Elementi stoga su:\n");
	Ispis(&hstog);
	printf("\nElementi reda su:\n");
	Ispis(&hred);
	printf("\nPop stog:\n");
	x=Pop(&hstog);
	printf("%d ", x);
	x=Pop(&hstog);
	printf("%d ", x);
	x=Pop(&hstog);
	printf("%d ", x);
	x=Pop(&hstog);
	printf("%d ", x);
	printf("\nPop red:\n");
	x=Pop(&hred);
	printf("%d ", x);
	x=Pop(&hred);
	printf("%d ", x);
	x=Pop(&hred);
	printf("%d ", x);
	x=Pop(&hred);
	printf("%d ", x);

	return 0;
}

void PushRed(pozicija p)
{
	pozicija q;
	q = (pozicija)malloc(sizeof(list));

	q->el = rand() % 101 + 10;

	while (p->next != NULL)
		p = p->next;

	q->next = p->next;
	p->next = q;

}

 void PushStog(pozicija p)
{
	 pozicija q;
	 q = (pozicija)malloc(sizeof(list));

	 q->el = rand() % 101 + 10;
	 q->next = p->next;
	 p->next = q;
}

 void Ispis(pozicija p)
 {
	 p = p->next;
	 while (p != NULL)
	 {
		 printf(" %d ", p->el);
		 p = p->next;
	 }
 }

int Pop(pozicija p)
{
	pozicija temp;
	int x;
	if(p->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		x = temp -> el;
		free(temp);
		return x;
	}


}