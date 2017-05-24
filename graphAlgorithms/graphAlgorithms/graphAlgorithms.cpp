// graphAlgorithms.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "graphByMatrix.h"
#include "graphByList.h"
#include "TestUnit.h"
#include "Menu.h"
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
	for (uint32_t i = 0; i < 1;i++)
	{
		testUnit.testG1Load();
		testUnit.testG1AStar();
		testUnit.testRandomAStar();
		testUnit.testRandomBoruvka();
		testUnit.testRandomFF();
	}
	std::unique_ptr<Menu> menu = std::make_unique<Menu>();
	menu->mainMenu();
	//std::unique_ptr<IGraph> GM = std::make_unique<graphByMatrix>(100, true);


	//GM->generateRandomGraph(50, 1 );
	//GM->printMatrix();

//  	graphByMatrix  *G = new graphByMatrix(10);
//  	std::map<uint32_t, maxEdgeValue> paths;
// 
// 	G->generateRandomGraph(50, false);
// 	G->printMatrix();
// 	auto boRes=	G->Boruvka();
// 	G->getPaths(0, paths);
// 	for (auto it = paths.begin(); it != paths.end(); it++)
// 	{
// 		std::cout << "Vertex: " << it->second << "\t" << "Wage:" << it->first << std::endl;
// 	}
	std::cout << "That's it, give any char to continue";
	std::cin >> new char();
    return 0;
}

