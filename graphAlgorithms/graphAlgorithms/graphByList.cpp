#include "graphByList.h"
#include <iostream>
graphByList::graphByList(uint32_t verts, bool directional/*=false*/)
{
	this->directed = directional;
	resize(verts);
}

graphByList::~graphByList()
{
}

void graphByList::getPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue>& neighbours)
{
		neighbours = vertices -> at(vertex);
}

void graphByList::addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage = 1)
{
	
	vertices->at(fromV).emplace(toV, wage);
	if (!directed)
		vertices->at(toV).emplace(fromV, wage);
}

void graphByList::resize(uint32_t targetSize)
{
	vertices = std::make_unique<std::vector < std::map<uint32_t, maxEdgeValue>> >();
	vertices->resize(targetSize);
	amountOfVerticies = targetSize;
}

void graphByList::printMatrix()
{
	uint32_t i = 0;
	for each (auto v in *vertices)
	{
		std::cout << "Vertex no. " << i<<" edges \t";
		for each (auto e in v)
		{
			std::cout << "(" << e.first << "|" << e.second << ")\t";
		}
		std::cout<<std::endl;
		i++;
	}
}
