#pragma once
#include "IContainer.h"
#include <string>
/*
FYI it's a MAX heap
*/
class Heap : public IContainer
{
private:
	int32_t* buffer=NULL; 
	uint32_t size=0; 

public:
	~Heap() { clear(); }
	Heap() {}
	Heap(Heap& gold)
	{
		size = gold.size;
		buffer = new int32_t[size];
		memcpy(buffer, gold.buffer, size* sizeof int32_t);
	}
	uint32_t getSize(); 
	//checks if node of given @index is leaf
	bool isLeaf(uint32_t index);
	uint32_t getParentIndex(uint32_t index); 
	uint32_t getLeftChildIndex(uint32_t index);
	uint32_t getRightChildIndex(uint32_t index);

	//make swaps upward until heap is fixed, recursive 
	void heapifyUp(uint32_t index);
	//make swaps downward until heap is fixed, recursive 
	void heapifyDown(uint32_t index);
	
	//inserts @value as last element and restores the heap if needed
	void pushBack(int32_t value) override; 
	//removes first element and restores the heap (if needed)
	void popFront() override;
	//returns @value index, returns -1 if not found
	//might be not best
	int32_t find(int32_t value); 
	bool findIf(int32_t value) override;
						
	void clear();

	void print(std::string sp = "", std::string sn = "", int k = 0);

	[[deprecated("not working, not sure if should be working")]]
	void insert(int32_t value, uint32_t index);
	//not working, not likely to be working
	virtual void pushRandom(int32_t value) override;
	virtual void pushFront(int32_t value) override;
	virtual void popRandom() override;
	virtual void popBack() override;
	virtual void printStructure() override;

	
};


//n - node num
//
//left child = 2n+1
//right child = 2(n+1)
//parent = floor((n-1)/2) n>0
//is leaf = 2(n+1)>size