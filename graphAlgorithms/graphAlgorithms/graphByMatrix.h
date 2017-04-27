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
	bool directional;
	
public:
	uint32_t getNumVerticies() const { return amountOfVerticies; }
	graphByMatrix(uint32_t verts, bool directional=false);
	void printMatrix();	//print NxN rows representing edges
	/*
		@fromV - starting vertex
		@toV - ending vertex
		@wage - wage/cost/whatever of traversing from one to another
		@directional - if true, only starting to ending edge is marked
	*/
	virtual void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage=1) override;

	// Inherited via IGraph
	virtual void GetPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue>& neighbours) override;

};

