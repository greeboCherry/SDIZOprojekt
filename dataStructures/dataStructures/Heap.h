#pragma once
#include "IContainer.h"
#include <string>
/*
FYI it's a MAX heap
*/
class Heap
{
private:
	int32_t* buffer=NULL; 
	uint32_t size=0; 

public:
	
	uint32_t getSize(); 
	//checks if node of given @index is leaf
	bool isLeaf(uint32_t index);
	uint32_t getParentIndex(uint32_t index); 
	uint32_t getLeftChildIndex(uint32_t index);
	uint32_t getRightChildIndex(uint32_t index);
	//make swaps upward until heap is fixed, recursive 
	void heapifyUp(uint32_t index);
	void heapifyDown(uint32_t index);

	void insert(int32_t value, uint32_t index);

	void pushBack(int32_t val); //dodaje element do kopca i ustawia go na wlasciwym miejscu

	void popFront(); //usuwa korzen i reorganizuje kopiec

	uint32_t find(int32_t val); //wyszukuje dana wartosc w kopcu i zwraca indeks node'a
							  //zwraca -1 jesli brak

	void print(std::string sp = "", std::string sn = "", int k = 0);

};


//n - node num
//
//left child = 2n+1
//right child = 2(n+1)
//parent = floor((n-1)/2) n>0
//is leaf = 2(n+1)>size