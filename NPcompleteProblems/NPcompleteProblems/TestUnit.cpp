#include "TestUnit.h"
#include "Knapsack.h"

#include <iostream>
TestUnit::TestUnit()
{
}


TestUnit::~TestUnit()
{
}

void TestUnit::showRandomKnapsack()
{//(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue)
	Knapsack sack(5, 10, 1, 8, 5, 10);
	sack.itemPool.clear();
	sack.itemPool.push_back(Item(7, 75));
	sack.itemPool.push_back(Item(8, 150));
	sack.itemPool.push_back(Item(6, 250));
	sack.itemPool.push_back(Item(4, 35));
	sack.itemPool.push_back(Item(3, 10));
	sack.itemPool.push_back(Item(9, 100));
	std::cout << "Sack fullness:" <<sack.getFullness()<< std::endl <<"Sack size: "<<sack.getSizeLimit()<< Knapsack::toString(sack.itemPool)<<std::endl;
	std::cout << "Greedy result:\n"<< Knapsack::toString(sack.greedy());
	std::cout << "Bruteforce result:\n" << Knapsack::toString(sack.brute());
	std::cout << "Dynamic result:\n" << Knapsack::toString(sack.dynamic());
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
