// graphAlgorithms.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "graphByMatrix.h"

/*
	Pytania:
	Czy muszê u¿ywaæ klucza na brak krawêdzi inny ni¿ zero?

	TODO: reprezentacja listowa

	Refki:
	https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
	https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
	https://en.wikipedia.org/wiki/A*_search_algorithm
	
*/

int main()
{
	graphByMatrix  *G = new graphByMatrix(10);

	std::cout << "\nthat's it, thank you\n";
	G->addEdge(2,3,5);
	G->printMatrix();
	std::cin >> new char();		//patent by in¿. Piotr Masek
    return 0;
}

