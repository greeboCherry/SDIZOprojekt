#include "List.h"

#include <stdio.h>


void List::insert(uint32_t position, int32_t value)
{
	uint32_t counter = 0;
	Node * it = _head;
	do {
		if (counter == position)
		{
			insert(it, value);
			return;
		}
		counter++;
	} while (it = it->getNext());
	
}

void List::insert(Node * position, int32_t value)
{
		Node* temp = new Node;
	
		temp->key = value;
		temp->_prev = position;
		temp->_next = position->_next;
		position->_next = temp;
		if (temp->_next)
		{
			temp->_next->_prev = temp;
		}
		else
			_tail = temp;
}

void List::erase(Node * position)
{
	Node* temp = position->_prev;
	temp->_next = position->_next;
	delete position;
}

List::Node* List::find(int32_t key)
{
	List::Node* temp = _head;
	do 
	{
		if (temp->key == key) return temp;
	} while (temp=temp->getNext());
}


//pierwsza implementacja, 
//TODO refactor jak ju¿ bêdzie insert
void List::pushFront(int32_t value)
{
	if (_head!=NULL)
	{
		Node* temp = _head;
		_head = new Node;
		
		if (temp)
		{
			_head->_next = temp;
			temp->_prev = _head;
		}
		else
			_tail = _head;
	}
	else
		_head = _tail = new Node;

	_head->key = value;
	_head->_prev = NULL;	
}

void List::printStructure()
{
	Node * it = _head;
	int counter = 0;
	printf("Head\t\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", (_head->key), _head->_prev, _head->_next, _head);
	do
	{
		printf("Node no. %d\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", counter, (it->key), it->_prev, it->_next, it);
		counter++;
	} while (it = it->getNext());
	printf("Tail\t\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", (_tail->key), _tail->_prev, _tail->_next, _tail);
}
