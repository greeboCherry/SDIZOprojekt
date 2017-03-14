#include "List.h"

#include <stdio.h>


//pierwsza implementacja, 
//TODO refactor jak ju¿ bêdzie insert
void List::pushFront(int32_t value)
{
	//jezeli juz cos mamy
	if (_head!=NULL)
	{
		//zapisanie adresu sterego head'a do temp'a
		Node* temp = _head;
		//tworzenie nowego wezla, przypisanie mu wartosci
		_head = new Node;
		
		//zaktualizowanie powi¹zañ temp'a jeœli istnieje
		if (temp)
		{
			_head->_next = temp;
			temp->_prev = _head;



		}
		//jeœli nie istnieje temp to head jest tailem
		else
			_tail = _head;
	}
	else
		//jezeli lista byla pusta
		_head = _tail = new Node;
	//przypisanie  wartosci
	_head->key = value;
	_head->_prev = NULL;
	
}
//prints the whole list, prints head and tail twice to be sure
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
