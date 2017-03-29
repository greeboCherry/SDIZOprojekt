#include "Heap.h"
#include <cmath>//floor
#include <cstdlib>
#include <iostream>


uint32_t Heap::getSize()
{
	return size;
}

uint32_t Heap::getParentIndex(uint32_t index)
{
	return (uint32_t)floor((index - 1) / 2);
}

uint32_t Heap::getLeftChildIndex(uint32_t index)
{
	return 2 * index + 2;
}

uint32_t Heap::getRightChildIndex(uint32_t index)
{
	return 2 * index + 1;
}

void Heap::heapifyUp(uint32_t index)
{
	
	int32_t temp = buffer[index];						
	buffer[index] = buffer[getParentIndex(index)];		//replace "here" by parent value
	buffer[getParentIndex(index)] = temp;				//replace parent value by new inserted value
	index = getParentIndex(index);						//"here"(pointer goes up a level

	if (index && buffer[index] > buffer[getParentIndex(index)])	//if not root and greater than parent 
		heapifyUp(index);
	
		return;
}

void Heap::heapifyDown(uint32_t index)
{
	int32_t temp = buffer[index];
	uint32_t swapperIndex = 0;
	if (isLeaf(index))
		swapperIndex = getLeftChildIndex(index);		//your job here is done
	else if (getRightChildIndex(index)>=size)
		swapperIndex = getRightChildIndex(index);
	else if (buffer[getLeftChildIndex(index)] > buffer[getRightChildIndex(index)])
		swapperIndex = getLeftChildIndex(index);
	else
		swapperIndex = getRightChildIndex(index);
		
	if (buffer[swapperIndex] > temp || swapperIndex>size)
		return;//you shouldn't been here tbh

	buffer[index] = buffer[swapperIndex];
	buffer[swapperIndex] = temp;
	heapifyDown(swapperIndex);
	return;
}

void Heap::insert(int32_t value, uint32_t index)
{
	if (!size)	//hello root

	{
		buffer = new int32_t[++size]{ value };
		return;
	}
	if (index > size)//sorry, heap must be full
		index = size;

	int32_t* temp = new int32_t[size + 1];
	memcpy(temp, buffer, sizeof int32_t * index);	//copying cells from 0 to index
		temp[index] = value;
	memcpy(temp + index + 1, buffer + index, sizeof(int32_t) * (size - index));	//copying cells from index+1 to size

	delete[] buffer;
	buffer = temp;
	size++;
	print();
	if (buffer[index] > buffer[getParentIndex(index)])	//if  greater than parent 
	{
		if (index)					//and not root
			heapifyUp(index);
	}
		else
			heapifyDown(index);
	
}

bool Heap::isLeaf(uint32_t index)
{
	return getLeftChildIndex(index) > size;
}

void Heap::pushBack(int32_t value)
{
	uint32_t index = size; 
	int32_t* temp = new int32_t[size+1];

	memcpy(temp, buffer, sizeof(int32_t) * size);	//copying all cells

	temp[size] = value;
	delete[] buffer;
	buffer = temp;
	size++;
	if (size > 1)
	{
		if (value > buffer[getParentIndex(index)])
			heapifyUp(index);
	}
	
	
}

void Heap::popFront()
{
	if (size)
	{
		if (size > 1)
		{
			int32_t *temp = new int32_t[size-1];
			
			memcpy(temp + 1, buffer+1, sizeof(int32_t) * (size-2));	//copying all cells shifted by 1
			temp[0] = buffer[size - 1];
			delete[] buffer;
			buffer=temp ;
			heapifyDown(0);
		}
		else
		{
			delete[] buffer;
		}
		size--;
	}
		
	else
	{
		//Heap was empty
	}
}

uint32_t Heap::find(int32_t val)
{
	if (buffer[0] >= val)
		for (uint32_t i = 0; i < size; i++)
		{
			if (buffer[i] == val)
				return i;
		}
	return -1;
}

//https://en.wikipedia.org/wiki/Binary_heap



//shamelessly stolen from 
//http://eduinf.waw.pl/inf/alg/001_search/0113.php
//author: mgr Jerzy Wa³aszek
void Heap::print(std::string sp, std::string sn, int k)
{
	std::string cr, cl, cp, s;

	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
//	printf("Heap size is %d\n", size); //move to pritn structure
if(size)
	if (k < size)
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		print(s + cp, cr, 2 * k + 2);

		s = s.substr(0, sp.length() - 2);

		std::cout << s << sn << this->buffer[k] << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		print(s + cp, cl, 2 * k + 1);
	}
		
}