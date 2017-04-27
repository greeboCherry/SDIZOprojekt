#include "IGraph.h"
#include <fstream>
#include <iostream>

bool IGraph::loadGraphFromFile(std::string path)
{
	std::fstream file(path, std::fstream::in);
	if (!file)
	{
		std::cout << "Couldn't open file at: " << path.c_str() << std::endl;
		return false;
	}
	uint32_t fromV, toV, targetNumOfEdges;
	maxEdgeValue wage;
	file >> targetNumOfEdges >> amountOfVerticies;
	
	
	for (uint32_t i = 0; i < targetNumOfEdges; i++)
	{
		file >> fromV >> toV >> wage;
		addEdge(fromV, toV, wage);
	}
	file.close();
	return true;
}

IGraph::IGraph()
{
}


IGraph::~IGraph()
{
}
