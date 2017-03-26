// dataStructures.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "IContainer.h"

/*
Pytania:
Czy lista mo¿e znaæ swój rozmiar?				ODP mo¿e
Czy powinienem kiedykolwiek sprawdzac czy w liœcie istnieje tail bez heada?	ODP: po prostu mierz size

How to array?						ODP w sumie to piszê menad¿era do tablic a nie tablice



*/

void test1();
void test2();

int main()
{
	int i;

	test2();
	scanf("%d", &i);
    return 0;
}

void test1()
{
	printf("Test one, list \n");
	List * list = new List;
	list->pushFront(1);
	list->pushFront(100);
	list->pushBack(123);
	printf("100, 1, 123\n");
	list->printStructure();
	list->insert((uint32_t)0, 13);
	list->erase(123);
	printf("13, 100, 1\n");
	list->printStructure();
	
	list->insert((uint32_t)0, 26);
	list->insert(1, 39);
	list->insert(3, 666);
	
	printf("26, 39, 13, 666, 100, 1\n");
	list->printStructure();
	/*
	list->pushBack(487);
	list->erase(13);
	//	Node* temp = list->insert(1, 256);
	list->printStructure();
	//	list->erase(temp);
	//	list->printStructure();
	*/
	printf("End of test one, list\n");
}

//I could add srand to alert order, but why?
void test2()
{
	printf("Test two, random inserting, list \n");
	IContainer *container= new Array;
//	Array *a = new Array;
	for (int i = 0; i < 100; i++)
	{
		container->pushRandom(i);
		//TODO find i as asserttion
	}
			//a->insert(i, i);
	container->printStructure();

	printf("End of test two, list\n");
}