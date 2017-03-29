// dataStructures.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "IContainer.h"
#include <algorithm>
#include <windows.h>

/*


mierzyæ jedn¹ t¹ sam¹ operacjê


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
void testAndShow();

void initVariables(int mode);
void testPushFront();	//no heap
void testPushBack();
void testPushRandom();	//no heap
void testPopFront();
void testPopBack();		//no heap
void testPopRandom();	//no heap
void testFindTrue();	
void testFindFalse();

void test2();


void StartCounter();
double GetCounter();

double PCFreq = 0.0;
__int64 CounterStart = 0;
int32_t* g_numbers;
IContainer* g_structure;
uint32_t g_amountOfNumbers = 50;
int32_t g_maxValue = 100;
int32_t g_minValue = 10;

int main()
{
	
	int i;
	testAndShow();
	printf("Give any integer to continue:\t");
	scanf_s("%d", &i);
    return 0;
}

void initVariables(int mode)
{
	g_amountOfNumbers = 50;
	g_maxValue=100;
	g_minValue=10;
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
			g_minValue = 10;
			g_maxValue = 100;
			break;
		}
		case 2:
		{
			g_minValue = -2147483648/2;
			g_maxValue = 2147483647/2;
			break;
		}
		case 3:
			g_minValue = -2147483648;
			g_maxValue = 2147483647;
			break;
		}
	}

	g_numbers = new int32_t[g_amountOfNumbers];
	for (uint32_t i = 0; i < g_amountOfNumbers;i++)
	{
		g_numbers[i] = g_minValue+ rand() % (g_maxValue - g_minValue + 1);		// 4294967296 - 2147483648;
	}
	

}

void testAndMeasure()
{
	initVariables(2);
	g_structure = new Array;
	//test1();
	delete	g_structure;
	g_structure = new List;
	testPushFront();
}

void testAndShow()
{
	double time;

	
	initVariables(2);			//put it to 1 for smaller sample
	g_structure = new Heap;		//replace it with another struct
	StartCounter();
	testPushBack();
	time = GetCounter();
	g_structure->printStructure();
	printf("PushFront for %d numbers in range \t [%d ; %d] done in \t%f ms \n", g_amountOfNumbers, g_minValue, g_maxValue, time);

	StartCounter();
	testFindTrue();
	time = GetCounter();
	printf("FindTrue for %d numbers in range \t [%d ; %d] done in \t%f ms \n", g_amountOfNumbers, g_minValue, g_maxValue, time);

	StartCounter();
	testPopFront();
	time = GetCounter();
	g_structure->printStructure();
	printf("PopFront for %d numbers in range \t [%d ; %d] done in \t%f ms \n", g_amountOfNumbers, g_minValue, g_maxValue, time);

}





void testPushFront()
{
	for (uint32_t i = 0; i < g_amountOfNumbers;i++)
	{
		g_structure->pushFront(g_numbers[i]);
	}
}


void testPushBack()
{
	for (uint32_t i = 0; i < g_amountOfNumbers; i++)
	{
		g_structure->pushBack(g_numbers[i]);
	}
}



void testPopFront()
{
	for (uint32_t i = 0; i < g_amountOfNumbers; i++)
	{
		g_structure->popFront();
	}
}


void testFindTrue()
{
	for (uint32_t i = 0; i < g_amountOfNumbers; i++)
	{
	//printf("%d",	g_structure->findIf(g_numbers[i]));	//print to check if all is positive
	}
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

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf( "QueryPerformanceFrequency failed!\n");

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}