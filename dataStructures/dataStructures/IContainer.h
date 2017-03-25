#pragma once

/*
Interface made to make tests easier, reqs:

*pushFront
*pushBack
*pushRandom
*/

class IContainer
{
public:
	virtual void pushFront(int32_t value) = 0;
	virtual void pushBack(int32_t value) = 0;
	virtual void pushRandom(int32_t value) = 0;

	virtual void printStructure() = 0;
};