#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char sinyal[50];
	char kode[30];
}sinyal;


typedef struct elmt *alamatelmt;
typedef struct elmt{
	sinyal elmt;
	alamatelmt next;
}elemen;


typedef struct{
	elemen *first;
}list;


void createList(list *L);
int countElement(list L);
void addFirst(char sinyal[], char kode[], list*L);
void addAfter(elemen *prev, char sinyal[], char kode[], list *L);
void addLast(char sinyal[], char kode[], list *L);
void delFirst(list *L);
void delAfter(elemen *prev, list *L);
void delLast(list *L);
void printElement(list L);
void delAll(list *L);
void printElement(list L);
