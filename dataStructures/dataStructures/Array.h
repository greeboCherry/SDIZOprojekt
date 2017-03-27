#pragma once

#include "IContainer.h"

class Array : public IContainer
{
private:
	
	int32_t* buffer=NULL;
	uint32_t size=0;
public:
	//insert @value to be at given @index
     void insert(int32_t value, uint32_t index);
	 void remove(uint32_t index);
	 //returns pointer to first occurrence of @value in table or NULL if it's not found
	 int32_t* find(int32_t value);// override;
	 void pushFront(int32_t value) override;
	 void pushBack(int32_t value) override;
	 void pushRandom(int32_t value) override;

	 void printStructure() override;

	 bool isEmpty() { return size==0; }
};