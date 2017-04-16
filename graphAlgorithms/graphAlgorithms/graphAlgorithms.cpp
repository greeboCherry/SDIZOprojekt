// graphAlgorithms.cpp : Defines the entry point for the console application.
//
#include "graphByMatrix.h"
/*
	
	TODO: wyjebaæ typedefa z grafu

*/

//#include "stdafx.h"


int main()
{
	auto  *G = new graphByMatrix<10>();

	std::cout << "\nthat's it, thank you\n";
	G->printMatrix();
	std::cin >> new char();		//patent by in¿. Piotr Masek
    return 0;
}

