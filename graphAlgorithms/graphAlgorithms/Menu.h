#pragma once
#include <memory>
#include "IGraph.h"
class Menu
{
	std::unique_ptr<IGraph> graph;

public:
	Menu();
	~Menu();
	void mainMenu();
//	void MSTMenu();
//	void pathsMenu();
};

