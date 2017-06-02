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
	while (1.25>randomLoot(itemNum, minItemSize, maxItemSize, minValue, maxValue))
	{
		maxItemSize++;
//		minItemSize++;
	}
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

std::vector<Item> Knapsack::greedy()
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
	result.reserve(unsigned int(myPool.size()/fullness));//I don't have idea for a better way to predict how big container we need
		
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
//	std::cout << Knapsack::toString(result);
	return result;
}
//aka przegl¹d zupe³ny
std::vector<Item> Knapsack::brute()
{
	std::vector<Item> result;

	std::vector<Item> thisTry;
	int bestResultValue = 0;
	int thisTryVolume;
	int thisTryValue;
	
	int stop = itemPool.size();
	std::vector<bool> takeList;
	takeList.resize(stop, false);
	stop *= stop;//we have n^2 possible combinations 
	for (int i = 0; i < stop; i++)	//run all possible combinations
	{
		thisTry.clear();
		thisTryVolume = 0;
		thisTryValue = 0;
		for (unsigned int j = 0; j < itemPool.size(); j++)	//follow 0-1 list of to take or not to take
		{
			auto it= itemPool.begin();
			if (takeList[j])
			{
				thisTry.push_back(*it);
				thisTryVolume += it->size;
				thisTryValue += it->value;
			}
		}
		if (thisTryVolume <= sizeLimit && thisTryValue>bestResultValue)
		{
			result = thisTry;
			bestResultValue = thisTryValue;
		}

	}
//	takeList
	/*
	add 1 to lowest=
			if there is zero, just make it one
1_:			else	make it zero, shift right 
					if it's zero, make it one
						else 
	
	1001010101010111
	+			   1
=	1001010101011000

	*/


	return  result;
}




std::string Knapsack::toString(const std::vector<Item>& sack)
{
	std::string result;
	result.reserve(sack.size() * 32 + 32);
	int i = 0;
	int totalValue = 0;
	int totalVolume = 0;
	for each (auto item in sack)
	{
		totalVolume += item.size;
		totalValue += item.value;
		result += "Item no. " + std::to_string(i) +"\t "+ std::to_string(item.value)+"$/" + std::to_string(item.size) + "l" + "="+ std::to_string(item.getRatio()) + "\n";
		i++;
	}
	result += "Total value: " + std::to_string(totalValue) + " total volume: " + std::to_string(totalVolume) + "\n";
	return result;
}

bool Knapsack::incerementBoolVector(std::vector<bool>& vector)
{
	auto itTL = vector.rbegin();

	if (*itTL==false)
	{
		*itTL = true;
		return true;
	}
	else//there was 1 already, we must carry over
	{
		while (*itTL)//and we carry it up until we meet 0
		{
			
			*itTL = false;
			itTL++;
			if (itTL == vector.rend())
			{
				return false; //overflow
			}
		}
		*itTL = true;
		return true;

	}

}
