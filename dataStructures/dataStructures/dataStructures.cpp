// dataStructures.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "List.h"

int main()
{
	int i;
	List * list = new List;
	list->pushFront(1);
	list->pushFront(100);
	list->pushFront(123);
	list->printStructure();
	printf("Hello world\n");
	scanf("%d", &i);
    return 0;
}

