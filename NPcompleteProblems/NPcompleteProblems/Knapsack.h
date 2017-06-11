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

class Knapsack
{
	int sizeLimit;
	float fullness;
		
public:

	float getFullness(){ return fullness; }
	int getSizeLimit() { return sizeLimit; }
	std::vector<Item> itemPool;
	Knapsack(int sackSize=1);
	Knapsack(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue);	//runs randomLoot(...)until fullnes >=1.25
	~Knapsack();

	inline void resize(int newSize) { sizeLimit = newSize; } 	//set new sizeLimit(volume, weight, whatever of Knapsack
	bool loadItemsFromFile(std::string path);	//format: sizeLimit, itemCount, [nth item size, nth item value]
	float randomLoot(int itemNum, int minSize, int maxSize, int minValue, int maxValue);	//generate random set of items with given starting values. 

	std::vector<Item> greedy();

	std::vector<Item> brute();

	std::vector<Item> dynamic();//http://www-users.mat.uni.torun.pl/~henkej/knapsack.pdf
	static std::string toString(const std::vector<Item>& sack);
	int evalute(const std::vector<Item>& sack);//asserts if value in vector of Items can fit inside this Knapsack if so, returns it's total value, else ret -1

	bool static incerementBoolVector(std::vector<bool>& vector);
};

