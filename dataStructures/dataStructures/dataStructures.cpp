// dataStructures.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "IContainer.h"
#include <algorithm>

/*
Pytania:
	1. Czy nie³adnie jest ukrywaæ nag³ówek z typem w nag³ówku interfejsu?
	2. Czy mój interfejs jest z³y?(drzewiaste nie maj¹ inserta itd., find w liœcie nie wyszed³ jak chcia³em)

TODO
	Kopiec					DONE
		dodawanie			done	
		usuwanie			done
		wyszukiwanie		done

	Init danych testowych	<-doing
	Wykonywanie pomiarów
	wypluwanie pomiarów

	Procedury testowe		ALL DONE except for heap(just one push and pop, search is... working)
		Test push/pop front
		Test push/pop back
		Test push/pop random
		Test find
		
	Maybe: 
		mem leaks?	
		BST Tree
*/
//
void testAndMeasure();



void testFront();
void test2();
void testHeap();
void initVariables(int mode);

int32_t* g_numbers;
IContainer* g_structure;
uint32_t g_amountOfNumbers = 50;

int main()
{
	
	int i;
	testHeap();
	scanf_s("%d", &i);
    return 0;
}

void initVariables(int mode)
{
	
	uint32_t maxValue=100;
	uint32_t minValue=10;
	switch (mode%3)
	{
	case 1:
		{
			g_amountOfNumbers = 50;
			maxValue = 100;
			minValue = 10;
			break;
		}
		
	case 2:
		{
			g_amountOfNumbers = 100000;
			break;
		}
	case 0: //nie puszczaæ za dnia!
		{
			g_amountOfNumbers = 50000000;
			maxValue = 100;
			minValue = 10;
			break;
		}
		
	}

	g_numbers = new int32_t[g_amountOfNumbers];
	for (uint32_t i = 0; i < g_amountOfNumbers;i++)
	{
		g_numbers[i] = rand() % maxValue + minValue;		// 4294967296 - 2147483648;
	}
	

}

void testAndMeasure()
{
	initVariables(2);
	g_structure = new Array;
	//test1();
	delete	g_structure;
	g_structure = new List;
	testFront();
}

void testFront()
{
	printf("Test one \n");
	for (uint32_t i = 0; i < g_amountOfNumbers;i++)
	{
		g_structure->pushFront(g_numbers[i]);

	}
	g_structure->printStructure();
	for (uint32_t i = 0; i < g_amountOfNumbers; i++)
	{
		g_structure->popFront();

	}
	g_structure->printStructure();
	printf("End of test one \n");
}

//I could add srand to alert order, but why?
void test2()
{
	printf("Test two, random inserting, list \n");
	IContainer *container= new Array;
//	Array *a = new Array;
	for (int i = 0; i < 10; i++)
	{
		container->pushRandom(i);
	}
	Array* a = (Array*)container;
	a->insert(102, 18);
	a->printStructure();
	a->remove(19);
			//a->insert(i, i);
	a->printStructure();
	printf("Found %d at %p\n", 9, a->find(9));
	printf("Found %d at %p\n", 5, a->find(5));
	printf("Found %d at %p\n", 13, a->find(13));
	printf("End of test two, list\n");
}



void testHeap()
{
	Heap* h = new Heap;
	for (uint32_t i = 0; i < 31; i++)
		h->pushBack(rand()%1000);
	h->print();
	for (uint32_t i = 0; i < 31; i++)
		h->popFront();
	h->print();
}

