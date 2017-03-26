#include "Array.h"

#include <stdio.h>
#include <algorithm> //copy

void Array::insert(int32_t value, uint32_t index)
{
	if (isEmpty())
	{
		buffor = new int32_t[1]{ value };
		size = 1;
	}
	else if (index == 0)
	{
			pushFront(value);
	}
	else if (index == size)
	{
		pushBack(value);
	}
	else if (index < size)
	{
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffor

		memcpy(temp, buffor, sizeof int32_t * index);	//copying cells from 0 to index
		
		temp[index] = value;

		memcpy(temp+index+1, buffor+index, sizeof (int32_t) * (size-index));	//copying cells from 0 to index
		size++;
		delete[] buffor;
		buffor = temp;
		
	}
}

void Array::pushFront(int32_t value)
{
	if (isEmpty())
	{
		buffor = new int32_t[1]{ value };
		size = 1;
	}
	else
	{
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffor
		memcpy(temp+1, buffor, sizeof (int32_t) * size);	//copying all cells shifted by 1 position
		temp[0] = value;
		delete[] buffor;
		buffor = temp;
		
		size++;
	}

}
void Array::pushBack(int32_t value)
{
	if (isEmpty())
	{
		buffor = new int32_t[1]{ value };
		size = 1;
	}
	else
	{
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffor
		memcpy(temp, buffor, sizeof(int32_t) * size);	//copying all cells
		temp[size] = value;
		delete[] buffor;
		buffor = temp;

		size++;
	}


}

void Array::pushRandom(int32_t value)
{
	if (size)
	{
		int posistion = rand() % size;
		insert(posistion, value);
	}
	else
		pushFront(value);
}

void Array::printStructure()
{
	for (uint32_t i = 0; i < size;i++)
	{
		printf("%d \t ", buffor[i]);
	}

}
