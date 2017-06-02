#pragma once
#include <vector>
#include <string>
struct Item
{
	int size = 0;
	int value = 0;
	Item() {};
	Item(int _size, int _value) :size(_size), value(_value) {}
	//returns how valuable is 1 unit of size/weight
	inline const float  getRatio() { return (float)value / (float)size; }


};
//
//http://www.micsymposium.org/mics_2005/papers/paper102.pdf
//


class Knapsack
{
	int sizeLimit;
	
		
public:
	float fullness;
	std::vector<Item> itemPool;
	Knapsack();
	Knapsack(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue);
	~Knapsack();
	//set new sizeLimit(volume, weight, whatever of Knapsack
	inline void resize(int newSize) { sizeLimit = newSize; }
	void loadItemsFromFile(std::string fileName);
	float randomLoot(int itemNum, int minSize, int maxSize, int minValue, int maxValue);

	std::vector<Item> greedy();

	std::vector<Item> brute();

	static std::string toString(const std::vector<Item>& sack);
//	std::vector<Item> 

	bool static incerementBoolVector(std::vector<bool>& vector);
};

