#include "Knapsack.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <cassert>

Knapsack::Knapsack(int sackSize):sizeLimit(sackSize)
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
	
	std::vector<bool> takeList;
	takeList.resize(itemPool.size(), false);
	
	while (Knapsack::incerementBoolVector(takeList))//run all possible combinations(stops on register overflow)
	{
		thisTry.clear();
		thisTryVolume = 0;
		thisTryValue = 0;

		for (unsigned int j = 0; j < itemPool.size(); j++)	//follow 0-1 list of to take or not to take
		{
			
			auto it= itemPool.begin();
			if (takeList.at(j))
			{
				thisTry.push_back(itemPool[j]);
				thisTryVolume += itemPool[j].size;
				thisTryValue += itemPool[j].value;
			}
		}
		if (thisTryVolume <= sizeLimit && thisTryValue>bestResultValue)
		{
			result = thisTry;
			bestResultValue = thisTryValue;
		}
	}

	return  result;
}




std::vector<Item> Knapsack::dynamic()
{
	/*
	 S I Z E 
	I X X X X
	T X X X X
	E X X X X
	M X X X X
	(x,y)=[x + y * width]
	numeration starts from 0
	*/
	std::vector<Item> result;
	auto tempLimit = sizeLimit+1; //we need array [0;sizeLimit], not [0;sizeLimit-1]
	std::vector<int> valueMatrix;
	valueMatrix.resize(itemPool.size()*tempLimit,0);
	for (int i = 1; i < tempLimit; i++)
	{
		if (itemPool[0].size <= i)
		{
			valueMatrix[i] = itemPool[0].value;
		}
	}

	
	for (unsigned int i = 1; i < itemPool.size();i++)	//we set 0'th row above
		for (int j = 1; j < tempLimit; j++)	//for sack sizeLimit==0 we can't fit anything
		{
			if (itemPool[i].size>j)	//if item won't fit that size of knapsack, just copy values from row above
			{
				valueMatrix[j + i*tempLimit] = valueMatrix[j + (i - 1)*tempLimit];
			}
			else  //now if it fits
			{
					//add it
				if (itemPool[i].value + valueMatrix[j-itemPool[i].size+(i-1)*tempLimit] > valueMatrix[j + (i - 1)*tempLimit])
				{
					valueMatrix[j + i*tempLimit] = itemPool[i].value + valueMatrix[j - itemPool[i].size + (i - 1)*tempLimit];
				
				}
				else	//just replace
				{
					valueMatrix[j + i*tempLimit] = valueMatrix[j + (i - 1)*tempLimit];
				}
			}//it COULD be merged, but it's more clear to me this way
			
		}
	//-------------------DEBUG WRITE of this damn table!
/*
	for (unsigned int j = 0; j < itemPool.size(); j++)
	{
		for (int i = 0; i < tempLimit; i++)
		{
			std::cout << valueMatrix[i + j*tempLimit] << "\t";
		}
		std::cout << std::endl;
	}
*/
	//----------backtracking

int index = valueMatrix.size()-1;

while (index > 0 && valueMatrix[index]!=0)
{
	while (index > tempLimit&&valueMatrix[index] == valueMatrix[index - tempLimit])	//go up until border
	{
		index -= tempLimit;
	}
			//when you find trace of item you took, jump left by it's weight
 		result.push_back(itemPool[index / tempLimit]);
 		index -= tempLimit;
		index -= result[result.size() - 1].size;
}
	return result;
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

int Knapsack::evalute(const std::vector<Item>& sack)
{
	int totalValue = 0;
	int totalVolume = 0;
	for each (auto item in sack)
	{
		totalVolume += item.size;
		totalValue += item.value;
	}

	if(totalVolume <= sizeLimit)
		return totalValue;
	else return -1;
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
