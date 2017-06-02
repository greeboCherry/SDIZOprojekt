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
{
	Knapsack sack(2, 5, 5, 10, 5, 10);

	std::cout << sack.fullness << std::endl << Knapsack::toString(sack.itemPool);
	std::cout << "Greedy result:"<< Knapsack::toString(sack.greedy());
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
