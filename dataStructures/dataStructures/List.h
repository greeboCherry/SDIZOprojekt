#pragma once

#include <stdint.h> //int32_t

class List
{
private:
	struct Node
	{
	friend class List;
	public:
		int32_t key;	//actual value
	protected:
		Node * _next = NULL;	//node toward the tail
		Node * _prev = NULL;	//node toward the head
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

	class Iterator : private Node
	{
	
	};
	
	//creates new element at front of @position	
	void insert(uint32_t position, int32_t value);
	//creates new element at front of @position
	void insert(Node * position, int32_t value);
	//removes the node @position
	void erase(Node * position);

	List::Node* find(int32_t key);
	//creates new element at the beginning of the list
	void pushFront(int32_t value);
	//prints the whole list, prints head and tail twice to be sure
	void printStructure();
	//tells if the list is empty
	
	bool isEmpty() { return (_head); }
};

