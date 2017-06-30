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

	int32_t temp = buffer[index];						// use std::swap instead ?
	buffer[index] = buffer[getParentIndex(index)];		//replace "here" by parent value
	buffer[getParentIndex(index)] = temp;				//replace parent value by new inserted value
	index = getParentIndex(index);						//"here"(pointer goes up a level
														//getParentIndex(index) used twice. Make temporary instead.
														//-> uint32_t parentIndex = getParentIndex(index);
														//index != 0 is more readable. I dont like && in if 
														//statement, it hard to read (just my preference)
	if (index && buffer[index] > buffer[getParentIndex(index)])	//if not root and greater than parent 
		heapifyUp(index);
	
		return;
}

/*
I would rewrite it like this :

	if (index == 0) //Branch out negative flow first
		return;

	int32_t parentIndex = getParentIndex(index);
	if (buffer[index] <= buffer[parentIndex])
	{
		std::swap(buffer[index], buffer[parentIndex]);
		heapifyUp(index);
	}

*/

void Heap::heapifyDown(uint32_t index)
{
	int32_t temp = buffer[index]; // again std::swap
	uint32_t swapperIndex = 0; 	// kind of bad naming(what is swapper? :/)
								// indexToSwap or childIndex should be better (maybe im too picky)
	// So much else if :/
	if (isLeaf(index))
		swapperIndex = getLeftChildIndex(index);		//your job here is done
	else if (getRightChildIndex(index)>=size)
		swapperIndex = getRightChildIndex(index);
	else if (buffer[getLeftChildIndex(index)] > buffer[getRightChildIndex(index)])
		swapperIndex = getLeftChildIndex(index);
	else
		swapperIndex = getRightChildIndex(index);
	// maybe helper function like getHeapifyDownIndex would be better
	// like this:
	/*
	int32_t Heap::getHeapifyDownIndex(int32_t index)
	{
		int32_t leftIndex = getLeftChildIndex(index),
				rightIndex = getRightChildIndex(index); //Temporaries :)))))

		if (isLeaf(index))
			return leftIndex;

		if (rightIndex >= size)
			return rightIndex;

		if (buffer[leftIndex] > buffer[rightIndex])
			return leftIndex;
		
		return rightIndex;
	}
	*/
		
	if (buffer[swapperIndex] > temp || swapperIndex>size) //i would rewrite this similarly to heapify up
		return;//you shouldn't been here tbh

	buffer[index] = buffer[swapperIndex]; //std::swap again ?
	buffer[swapperIndex] = temp;
	heapifyDown(swapperIndex);
	return;
}

/*
I would rewrite it like this :
	
	int32_t childIndex = getHeapifyDownIndex(index);
	if (childIndex > size)
		return;

	if (buffer[index] >= buffer[childIndex])
	{
		std::swap(buffer[index], buffer[childIndex]);
		heapifyDown(index);
	}

*/

void Heap::insert(int32_t value, uint32_t index)
{
	if (size == 0)	//hello root, explicit comparision please ;)

	{
		buffer = new int32_t[++size]{ value }; 	// Why not say size is one explicitly: size = 1; buffer = new int32_t[size]{value};
												// ++size in a statement is hard to read
		return;
	}
	if (index > size)//sorry, heap must be full
		index = size; //You can just push_back -> less overhead + cleaner code

	int32_t* temp = new int32_t[size + 1];
	memcpy(temp, buffer, sizeof(int32_t) * index);	//copying cells from 0 to index
		temp[index] = value; //Some indentations problem, but i bet you know it
	memcpy(temp + index + 1, buffer + index, sizeof(int32_t) * (size - index));	//copying cells from index+1 to size

	delete[] buffer;
	buffer = temp;
	size++;
	print();
	if (buffer[index] > buffer[getParentIndex(index)])	//if  greater than parent 
	{
		if (index)					//and not root
			heapifyUp(index); //Why not check if index is a root in heapifyUp?
	}
		else 	//indetation is fucked up, also i find your lack of brackets in else statement disturbing #pdk
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
	if (size) // if(size == 0) return; seems better
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
		else // if(size == 1) delete[] buffer; size = 0; same as before
		{
			delete[] buffer;
		}
		size--;
	}
		
	else // Unnecessarry else statement :(
	{
		//Heap was empty
	}
}

int32_t Heap::find(int32_t value)
{
	if (buffer[0] >= value) //Brackes please
		for (int32_t i = 0; i < size; i++)
		{
			if (buffer[i] == value)
				return i;
		}
	return -1;
}

bool Heap::findIf(int32_t value)
{
	return find(value) >= 0;
}

void Heap::clear()
{
	delete[] buffer;
	size = 0;
}

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

void Heap::printStructure()
{
	printf("Heap size is %d\n", size); 
	print();
}



void Heap::popRandom()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Heap::popBack()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Heap::pushRandom(int32_t value)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Heap::pushFront(int32_t value)
{
	throw std::logic_error("The method or operation is not implemented.");
}
