// graphAlgorithms.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "graphByMatrix.h"
#include "graphByList.h"
#include "TestUnit.h"
#include <memory>

/*
	Pytania:
	Czy muszê u¿ywaæ klucza na brak krawêdzi inny ni¿ zero?

	TODO: reprezentacja listowa

	Refki:
	https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

	https://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
	https://en.wikipedia.org/wiki/Prim%27s_algorithm

	https://en.wikipedia.org/wiki/A*_search_algorithm
	http://www.cc.gatech.edu/~echow/pubs/levdiff-aaai.pdf	A* herusitics with center concepts. Forget it, Euklisdes FTW
	
*/

int main()
{
	TestUnit testUnit;
	testUnit.testG1Load();
	testUnit.testG1AStar();
	std::unique_ptr<IGraph> GM = std::make_unique<graphByList>(4, false);
	GM->generateRandomGraph(100, 1 );
	GM->printMatrix();

// 	graphByMatrix  *G = new graphByMatrix(10);
// 	std::map<uint32_t, maxEdgeValue> paths;
// 
// 	G->loadGraphFromFile("input/G1.txt");
// 	G->printMatrix();
// 	G->getPaths(0, paths);
// 	for (auto it = paths.begin(); it != paths.end(); it++)
// 	{
// 		std::cout << "Vertex: " << it->second << "\t" << "Wage:" << it->first << std::endl;
// 	}

	std::cin >> new char();		//patent by in¿. Piotr Masek
    return 0;
}

