// dataStructures.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "List.h"

/*
Pytania:
Czy lista mo¿e znaæ swój rozmiar?
Czy powinienem kiedykolwiek sprawdzac czy w liœcie istnieje tail bez heada?
Find nie chce mi zwracaæ Node'a
Hot to array?



*/


int main()
{
	int i;
	List * list = new List;
	list->pushFront(1);
	list->pushFront(100);
	list->pushFront(123);
	list->insert(1, 13);
	list->insert(1, 26);
	list->insert(1, 39);
	list->insert(1, 666);
//	Node* temp = list->insert(1, 256);
	list->printStructure();
//	list->erase(temp);
	list->printStructure();
	//printf("Hello world\n");
	scanf("%d", &i);
    return 0;
}

