#pragma once
#include "IGraph.h"
#include <iostream>
/*
represents graph by matrix of edges between verticles

*/
class graphByMatrix : public IGraph
{
			//determines how much memory should those damn wages take of my memory

private:
	
	maxEdgeValue* edges;//dynamic array representing edges in FROM\TO fashion, @seealso addEdge

	
public:
	uint32_t getNumVerticies() const { return amountOfVerticies; }
	graphByMatrix(uint32_t verts, bool directional=false);
	graphByMatrix(const graphByMatrix& other);
	~graphByMatrix() { delete[]edges; }

	void printMatrix();	//print NxN rows representing edges
	/*
		@fromV - starting vertex
		@toV - ending vertex
		@wage - wage/cost/whatever of traversing from one to another
		@directed - if true, only starting to ending edge is marked
	*/
	virtual void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage=1) override;
	virtual void resize(uint32_t targetSize) override;

	// Inherited via IGraph
	virtual void getPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue> &neighbours) override;
	virtual IGraph* clone() override;

	// Inherited via IGraph
	virtual maxEdgeValue getPath(uint32_t from, uint32_t to) override;

	// Inherited via IGraph
	virtual void modifyPath(uint32_t from, uint32_t to, int32_t deltaValue) override;
};

