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

		http://cpp0x.pl/forum/temat/?id=21331
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

//run this to get all results in txt NYI
void testAndMeasure();



void testFrontBack();	//push front and pop back the struct
void testBackFront();
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
	g_amountOfNumbers = 50;
	uint32_t maxValue=100;
	uint32_t minValue=10;
	if (mode)
	{
		switch (mode % 3)
		{
		case 1:
		{
			g_amountOfNumbers = 50;

			break;
		}

		case 2:
		{
			g_amountOfNumbers = 100000;
			break;
		}
		case 0:
		{
			g_amountOfNumbers = 200000;

			break;
		}

		}
		switch (mode / 3)
		{
		case 1:
		{
			minValue = 10;
			maxValue = 100;
			break;
		}
		case 2:
		{
			minValue = -2147483648/2;
			maxValue = 2147483647/2;
			break;
		}
		case 3:
			minValue = -2147483648;
			maxValue = 2147483647;
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

