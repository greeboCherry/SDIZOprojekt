#pragma once

#include <stdint.h> //int32_t

class List
{
private:

	struct Node
	{
	friend class List;
	private:
		int32_t key;	//actual value
		Node * _next = NULL;
		Node * _prev = NULL;
	public:
		Node* getPrev()
		{
			return _prev;
		}
		Node* getNext()
		{
			return _next;
		}
		int32_t getKey()
		{
			return key;
		}
		void setKey(int32_t newKey)
		{
			key = newKey;
		}

	};

	Node * _head = NULL;	//pointer to the first node
	Node * _tail = NULL;	//pointer to the last node

public:
	void insert(uint32_t position, int32_t value);
	//creates new element at the beginning of the list
	void pushFront(int32_t value);
	//prints the whole list, prints head and tail twice to be sure
	void printStructure();

};

