#include "List.h"

#include <stdio.h>
#include <cstdlib>
#include <stdexcept>
void List::insert(uint32_t position, int32_t value)
{
	if (position == 0)
	{
		pushFront(value);
		return;
	}
	else if (position >= size)
	{
		pushBack(value);
		return;
	}
	else
	{
		position--;
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
}

void List::insert(Node * position, int32_t value)
{
	if (!_head)
	{
		pushFront(value);
		return;
	}
	else
		size++;
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

//
void List::pushFront(int32_t value)
{
	if (_head != NULL)
	{
		//if head already exists, we must set new head and re-link old head
		Node* temp = _head;
		_head = new Node;

			_head->_next = temp;
			temp->_prev = _head;
	}
		//if there is no head, there is no tail, so new Node is the only one
	else
		_head = _tail = new Node;
	//anyway we set values, and head has no _prev
	_head->key = value;
	_head->_prev = NULL;
	size++;
}

void List::pushBack(int32_t value)
{
	//if it's empty, use pushFront so we can skip some ifs here
	if (!_head)
	{
		pushFront(value);
		return;
	}
	Node* temp = _tail;
	_tail = new Node;
	temp->_next = _tail;
	_tail->_prev = temp;
	_tail->key = value;
	_tail->_next = NULL;
	size++;

}

void List::pushRandom(int32_t value)
{
	if (size)
	{
		int posistion = rand() % size;
		insert(posistion, value);
	}
	else
		pushFront(value);
}

bool List::findIf(int32_t value)
{
	return (find(value) > 0);
}

void List::erase(Node * position)
{
	if (position == _tail)
	{
	popBack();
	}
	else if(position == _head)
	{
		popFront();
	}
	else
	{
		Node* temp = position->_prev;
		temp->_next = position->_next;
		delete position;
		size--;

	}
}

void List::erase(uint32_t value)
{
	erase(find(value));
}

void List::popFront()
{
	Node* temp = _head->_next;
	if(temp)
	{
		temp->_prev = NULL;
	}
	delete _head;
	_head = temp;
	size--;

}

void List::popBack()
{
	Node* temp = _tail->_prev;
	temp->_next = NULL;
	delete _tail;
	_tail = temp;
	size--;
}

List::Node* List::find(int32_t key)
{
	List::Node* temp = _head;
	do 
	{
		if (temp->key == key) 
			return temp;
	} while (temp=temp->getNext());
	
		return NULL;
}




void List::printStructure()
{
	Node * it = _head;
	int counter = 0;
	printf("Size of this LIST is \t%i\n", size);
	printf("Head\t\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", (_head->key), _head->_prev, _head->_next, _head);
	do
	{
		printf("Node no. %d\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", counter, (it->key), it->_prev, it->_next, it);
		counter++;
	} while (it = it->getNext());
	printf("Tail\t\tKey:%d\t_prev:%p\t_next:%p\taddress:%p\n", (_tail->key), _tail->_prev, _tail->_next, _tail);
}

void List::popRandom()
{
	if (isEmpty())
		return;
	Node * it = _head;
	for (uint32_t i = rand() % size; i > 0;i--)
	{
		it = it->getNext();
	}
	if (it)
	{
		erase(it);
	}
	else
	{
		throw std::out_of_range("popRandom is wrong again");
	}
}
