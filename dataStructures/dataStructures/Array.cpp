#include "Array.h"

#include <stdio.h>
#include <algorithm> //copy


//TODO Redisign this function to work on smaller amount of branches, just like remove()
void Array::insert(int32_t value, uint32_t index)
{
	if (isEmpty())
	{
		buffer = new int32_t[1]{ value };
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
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffer

		memcpy(temp, buffer, sizeof int32_t * index);	//copying cells from 0 to index
		
		temp[index] = value;

		memcpy(temp+index+1, buffer+index, sizeof (int32_t) * (size-index ));	//copying cells from index+1 to size
		size++;
		delete[] buffer;
		buffer = temp;
	}
	else
	{
		int32_t* temp = new int32_t[index + 1];
		
		memcpy(temp, buffer, sizeof int32_t * size);	//copying cells from 0 to index
		temp[index] = value;
		size = index + 1;
		delete[] buffer;
		buffer = temp;
	}
}

void Array::remove(uint32_t index)
{
	if (index >= size)
	{
		printf("\n\tERROR: index out of bounds\n");
		return;
	}
	int32_t* temp = new int32_t[size-1];
	memcpy(temp, buffer, (index)*sizeof(int32_t));
	memcpy(temp + index, buffer + index + 1, (size - index)*sizeof(int32_t));
	delete[] buffer;
	buffer = temp;
	size--;
}

int32_t* Array::find(int32_t value)
{
	for (uint32_t i = 0; i < size; i++)
	{
		if (buffer[i] == value)
			return &buffer[i];
	}
	return NULL;	//what should I return if there is no given value in structure?
}

bool Array::findIf(int32_t value)
{
	return (find(value)>0);
}

void Array::pushFront(int32_t value)
{
	if (isEmpty())
	{
		buffer = new int32_t[1]{ value };
		size = 1;
	}
	else
	{
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffer
		memcpy(temp+1, buffer, sizeof (int32_t) * size);	//copying all cells shifted by 1 position
		temp[0] = value;
		delete[] buffer;
		buffer = temp;
		
		size++;
	}

}
void Array::pushBack(int32_t value)
{
	if (isEmpty())
	{
		buffer = new int32_t[1]{ value };
		size = 1;
	}
	else
	{
		int32_t* temp = new int32_t[size + 1];		//this will soon became new buffer
		memcpy(temp, buffer, sizeof(int32_t) * size);	//copying all cells
		temp[size] = value;
		delete[] buffer;
		buffer = temp;

		size++;
	}


}

void Array::pushRandom(int32_t value)
{
	if (size)
	{
		int posistion = rand() % size;
		insert(value, posistion);
	}
	else
		pushFront(value);
}

void Array::popFront()
{
	remove(0);
}

void Array::printStructure()
{
	printf("Size of this ARRAY is \t%i\n", size);
	for (uint32_t i = 0; i < size;i++)
	{
		printf("%d\t", buffer[i]);

	}
	printf("\n");
}
