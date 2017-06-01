#include "Knapsack.h"
#include <random>
#include <algorithm>
#include <iostream>

Knapsack::Knapsack()
{
}


Knapsack::Knapsack(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue)
{
	sizeLimit = sackSize;
	randomLoot(itemNum, minItemSize, maxItemSize, minValue, maxValue);
}

Knapsack::~Knapsack()
{
}

float Knapsack::randomLoot(int itemNum, int minSize, int maxSize, int minValue, int maxValue)
{
	std::random_device rd; 
	std::mt19937 messmer(rd());
	std::uniform_int_distribution<int> sizeDist(minSize, maxSize);
	std::uniform_int_distribution<int> valueDist(minValue, maxValue);
	
	int totalSize = 0;

	itemPool.clear();
	itemPool.reserve(itemNum);
	for (int i = 0; i < itemNum; i++)
	{
		itemPool.push_back(Item(sizeDist(messmer), valueDist(messmer)));
		totalSize += itemPool[i].size;
	}
		
	fullness = (float)totalSize / (float)sizeLimit;

	return fullness;
}

void Knapsack::greedy()
{
	std::vector<Item> myPool(itemPool);	//make local copy to not fuck up the original
	int spaceLeft = sizeLimit;

	//sort your copy by ratio, ascending 
	std::sort(myPool.begin(), myPool.end(),	
		[](Item& a,  Item& b)
	{
		return a.getRatio() > b.getRatio();
	});
	//std::cout << Knapsack::toString(myPool);

	std::vector<Item> result;
	result.reserve(myPool.size()/fullness);//I don't have idea for a better way to predict how big container we need

	
	for (auto it = myPool.begin(); it != myPool.end(); it++)
	{
		if (it->size <= spaceLeft)
		{
			result.push_back(*it);
			spaceLeft -= it->size;
		}
		if(spaceLeft==0)
			break;;
	}
	std::cout << Knapsack::toString(result);
}

std::string Knapsack::toString(const std::vector<Item>& sack)
{
	std::string result;
	int i = 0;
	for each (auto item in sack)
	{
		result += "Item no. " + std::to_string(i) +"\t "+ std::to_string(item.value)+"$/" + std::to_string(item.size) + "l" + "="+ std::to_string(item.getRatio()) + "\n";
		i++;
	}
	return result;
}
