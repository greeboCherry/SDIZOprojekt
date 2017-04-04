
#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "IContainer.h"
//#include "FileWriter.cpp"
#include "TestUnit.h"
#include <string>
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
		mem leaks	-none found
		BST Tree
*/

//run this to get all results in txt NYI
void testAndMeasure();
void testAndShow();

[[deprecated("Use TestUnit")]]void initVariables(int mode);
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


int32_t* g_numbers;
IContainer* g_structure;
uint32_t g_amountOfNumbers = 50;
int32_t g_maxValue = 100;
int32_t g_minValue = 10;

int main()
{
	
	//	FileWriter::saveToFile("hello.txt", "hello world?\n");	//test of save to file
	TestUnit* ts = new TestUnit();
//	ts->initVariables(2);
	
	
	ts->initVariables(8);
	//ts->testInsertArray(100000, 50000);
	for (int i = 1000; i < 50000; i+=1000)
	{
		ts->testSearch(i, 500);
	//		ts->testHeap(i, 500);
	//	ts->testInsertList(i , 500);	//there is no time
	//	ts->testInsertArray(i, 500);
		printf("Finished run on %d elements\n", i);
	}
	


//	Array* a = new Array;
//	a->initFromArray(ts->numbers, ts->amountOfNumbers);
//	a->printStructure();
	int i;
	//testAndShow();
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
	

	
	initVariables(2);			//put it to 1 for smaller sample
	g_structure = new Heap;		//replace it with another struct
	
	testPushBack();
	
	g_structure->printStructure();
	
	
	testFindTrue();
	
	
	testPopFront();
	
	g_structure->printStructure();

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

