#include "TestUnit.h"
#include "FileWriter.cpp"
#include "Knapsack.h"
#include <ctime>
#include <chrono>
#include <windows.h>


#include <iostream>
TestUnit::TestUnit()
{
}


TestUnit::~TestUnit()
{
}


void TestUnit::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("QueryPerformanceFrequency failed!\n");

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double TestUnit::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void TestUnit::showRandomKnapsack()
{//(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue)
	Knapsack sack(30, 60, 1, 8, 5, 10);
// 	sack.itemPool.clear();
// 	sack.itemPool.push_back(Item(7, 75));
// 	sack.itemPool.push_back(Item(8, 150));
// 	sack.itemPool.push_back(Item(6, 250));
// 	sack.itemPool.push_back(Item(4, 35));
// 	sack.itemPool.push_back(Item(3, 10));
// 	sack.itemPool.push_back(Item(9, 100));
	std::cout << "Sack fullness:" <<sack.getFullness()<< std::endl <<"Sack size: "<<sack.getSizeLimit()<< Knapsack::toString(sack.itemPool)<<std::endl;
	std::cout << "Greedy result:\n"<< Knapsack::toString(sack.greedy());
	std::cout << "Bruteforce result:\n" << Knapsack::toString(sack.brute());
	std::cout << "Dynamic result:\n" << Knapsack::toString(sack.dynamic());
}

void TestUnit::cornerCaseKnapsack()
{
	Knapsack sack(5, 10, 1, 8, 5, 10);
		sack.itemPool.clear();
		sack.itemPool.push_back(Item(6, 9));
		sack.itemPool.push_back(Item(5, 10));
		sack.itemPool.push_back(Item(2, 8));
		sack.itemPool.push_back(Item(9, 7));
		sack.itemPool.push_back(Item(5, 10));
		
	std::cout << "Sack fullness:" << sack.getFullness() << std::endl << "Sack size: " << sack.getSizeLimit() << Knapsack::toString(sack.itemPool) << std::endl;
	std::cout << "Greedy result:\n" << Knapsack::toString(sack.greedy());
	std::cout << "Bruteforce result:\n" << Knapsack::toString(sack.brute());
	std::cout << "Dynamic result:\n" << Knapsack::toString(sack.dynamic());
}

void TestUnit::testInputS1()
{
	Knapsack sack(1);
	if (!sack.loadItemsFromFile("input/s1.txt"))
		return;

	std::cout << "Sack fullness:" << sack.getFullness() << std::endl << "Sack size: " << sack.getSizeLimit() << Knapsack::toString(sack.itemPool) << std::endl;
	std::cout << "Greedy result:\n" << Knapsack::toString(sack.greedy());
	std::cout << "Bruteforce result:\n" << Knapsack::toString(sack.brute());
	std::cout << "Dynamic result:\n" << Knapsack::toString(sack.dynamic());
}

void TestUnit::runOneBrute(int itemNum, int sackSize)
{
	StartCounter();
	Knapsack sack(itemNum, sackSize, 2, 8, 5, 10);
	std::cout << GetCounter();
	StartCounter();
	sack.brute();
	auto t = GetCounter();
	std::cout << "Brute took" << t << "ms";
}

void TestUnit::comapreBruteDynamicResults(int testNum)
{
	int errors = 0;
	for (int i = 0; i < testNum;i++)
	{
		
		Knapsack sack(4, 10, 3, 6, 20, 40);
		if (sack.evalute(sack.dynamic()) != sack.evalute(sack.brute()))
			errors++;
	}
	std::cout << "Finished comapreBruteDynamicResults()" ;
	std::cout << "Run " << testNum << " test, got " << errors << " errors\n";
}

void TestUnit::testBoolsIncrement(int size)
{
	std::vector<bool> bools;
	bools.resize(size, 0);

	while (Knapsack::incerementBoolVector(bools))
	{
		std::string str;
		str.reserve(size);
		for (int i = 0; i < size; i++)
		{
			str += (bools[i]) ? '1' : '0';
		}

		std::cout << str << std::endl;
	}

}

void TestUnit::testAndMeasure(int itemNum, int sackSize, int testNum, bool bTestBrute)
{
	double g_time =0, d_time = 0, b_time =0, c_time=0;
	for (int i = 0; i < testNum; i++)
	{
//		g_time = d_time = b_time;
		StartCounter();
		Knapsack sack(itemNum, sackSize, 5, sackSize, 10, 100);
		c_time += GetCounter();
		std::vector<Item> res;
		
		StartCounter();
		res = sack.greedy();
		g_time += GetCounter();
		

		StartCounter();
		res = sack.dynamic();
		d_time += GetCounter();

		if (bTestBrute) {
			StartCounter();
			res = sack.brute();
			b_time += GetCounter();
		}
	}
	g_time /= testNum;
	d_time /= testNum;
	if (bTestBrute) 
	b_time /= testNum;
	
	
	std::string message;

	message = "Time for item pool creation for\t" + std::to_string(sackSize) + "\tsack size and\t" + std::to_string(itemNum) + "\titems took\t" +
		std::to_string(c_time) + "\tms\n";
	FileWriter::saveToFile("creation", message);

	message = "Time for greedy algorithm running for\t" + std::to_string(sackSize) + "\tsack size and\t" + std::to_string(itemNum) + "\titems took\t" +
		std::to_string(g_time) + "\tms\n";
	FileWriter::saveToFile("greedy",message);

	message = "Time for dynamic algorithm running for\t" + std::to_string(sackSize) + "\tsack size and\t" + std::to_string(itemNum) + "\titems took\t" +
			std::to_string(d_time) + "\tms\n";
	FileWriter::saveToFile("dynamic", message);
	if (bTestBrute) {
		message = "Time for bruteforce algorithm running for\t" + std::to_string(sackSize) + "\tsack size and\t" + std::to_string(itemNum) + "\titems took\t" +
			std::to_string(b_time) + "\tms\n";
		FileWriter::saveToFile("brute", message);
	}
		return;

}
