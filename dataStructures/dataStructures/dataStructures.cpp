// dataStructures.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "List.h"

/*
Pytania:
Czy lista mo¿e znaæ swój rozmiar?				ODP mo¿e
Czy powinienem kiedykolwiek sprawdzac czy w liœcie istnieje tail bez heada?	ODP: po prostu mierz size

How to array?						ODP w sumie to piszê menad¿era do tablic a nie tablice



*/

void test1();

int main()
{
	int i;
	test1();
	scanf("%d", &i);
    return 0;
}

void test1()
{
	printf("Test one, list \n");
	List * list = new List;
	list->pushFront(1);
	list->pushFront(100);
	list->pushFront(123);
	list->insert((uint32_t)0, 13);
	list->insert(1, 26);
	list->insert(1, 39);
	list->insert(3, 666);
	list->pushBack(487);
	list->erase(13);
	//	Node* temp = list->insert(1, 256);
	list->printStructure();
	//	list->erase(temp);
	//	list->printStructure();
	printf("End of test one, list\n");
}

