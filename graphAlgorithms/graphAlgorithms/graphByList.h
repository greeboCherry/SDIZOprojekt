#pragma once
#include "IGraph.h"
#include <vector>
#include <memory>
class graphByList :	public IGraph
{
	//each vertex[index] keeps map of vertices in has connection(first) and cost of those(second)
	std::unique_ptr<	std::vector < std::map<uint32_t, maxEdgeValue>> >  vertices; 
public:
	graphByList(uint32_t verts, bool directional=false);
	graphByList(const graphByList& other);
	~graphByList();

	// Inherited via IGraph
	virtual void getPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue>& neighbours) override;
	virtual void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage /*= 1*/) override;
	virtual void resize(uint32_t targetSize) override;
	virtual void printMatrix() override;
	virtual IGraph* clone() override;


	// Inherited via IGraph
	virtual maxEdgeValue getPath(uint32_t from, uint32_t to) override;


	// Inherited via IGraph
	virtual void modifyPath(uint32_t from, uint32_t to, int32_t deltaValue) override;

};

