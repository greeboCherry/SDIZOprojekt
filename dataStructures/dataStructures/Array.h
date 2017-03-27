#pragma once

#include "IContainer.h"

class Array : public IContainer
{
private:
	
	int32_t* buffer=NULL;
	uint32_t size=0;
public:

     void insert(int32_t value, uint32_t index);
	 void remove(uint32_t index);
	 void pushFront(int32_t value) override;
	 void pushBack(int32_t value) override;
	 void pushRandom(int32_t value) override;

	 void printStructure() override;

	 bool isEmpty() { return size==0; }
};