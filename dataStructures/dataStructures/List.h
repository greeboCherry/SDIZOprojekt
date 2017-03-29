#pragma once


#include "IContainer.h"
/*

*/
class List : virtual public IContainer
{
private:
		struct Node
		{
		friend class List;
		protected:
			int32_t key;	//actual value
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
	uint32_t size=0;	
public:

	//creates new element at front of @position	
	void insert(uint32_t position, int32_t value);
	//creates new element at front of @position
	void insert(Node * position, int32_t value);
	//creates new element at the beginning of the list
	void pushFront(int32_t value) override;
	//creates new element at the end of the list
	void pushBack(int32_t value) override;
	//creates new element inside the list
	void pushRandom(int32_t value) override;
	bool findIf(int32_t value) override;

	//removes the node @position
	void erase(Node * position);
	//removes the firs node of given value
	void erase(uint32_t value);
	//removes the head
	void popFront();
	//removes the tail
	void popBack();

	//returns the first node of given value
	List::Node* find(int32_t key);

	//prints the whole list, prints head and tail twice to be sure
	void printStructure();
	//tells if the list is empty
	bool isEmpty() { return size==0; }
};

