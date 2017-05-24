#include "graphByList.h"
#include <iostream>
#include <stdexcept>
graphByList::graphByList(uint32_t verts, bool directional/*=false*/)
{
	this->directed = directional;
	resize(verts);
}

graphByList::graphByList(const graphByList& other)
{
	vertices = std::make_unique<std::vector < std::map<uint32_t, maxEdgeValue>> >();
	vertices->resize(other.vertices->size());
	std::copy(other.vertices->begin(), other.vertices->end(), vertices->begin());

	amountOfVerticies = other.amountOfVerticies;
	amountOfEdges = other.amountOfEdges;
	directed = other.directed;
	//vector2* coordinates; //let's skip this, ain't gonna be used, rly
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

IGraph* graphByList::clone()
{
// 	IGraph* copy;
// 	copy= new graphByList(*this);
// 
// 	return copy;
	//return new graphByList(static_cast<const graphByList&> (*this));
	return new graphByList(*this);
}

maxEdgeValue graphByList::getPath(uint32_t from, uint32_t to)
{
	auto it = vertices->at(from).find(to);
	if (it != vertices->at(from).end())
		return it->second;
	else
		throw std::logic_error("there is no such edge");

}

void graphByList::modifyPath(uint32_t from, uint32_t to, int32_t deltaValue)
{
	auto it=	vertices->at(from).find(to);
	if (it != vertices->at(from).end())
	{
		it->second += deltaValue;
		if (it->second == 0)
			vertices->at(from).erase(it);
	}
	else
		throw std::logic_error("there is no such edge");
}
