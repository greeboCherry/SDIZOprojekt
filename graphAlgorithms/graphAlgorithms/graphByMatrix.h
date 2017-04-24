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
	uint32_t amountOfVerticies;
	uint32_t amountOfEdges=0;
	maxEdgeValue* edges;
	bool directional;
	
public:
	uint32_t getNumVerticies() const { return amountOfVerticies; }
	graphByMatrix(uint32_t verts, bool directional=false);
	void printMatrix();	//print NxN rows representing edges
	/*
		@fromV - starting vertex
		@toV - ending vertex
		@wage - wage/cost/whatever of traversing from one to another
		@directional - if true, starting to ending edge is marked
	*/
	void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage=1);




	// Inherited via IGraph
	virtual uint32_t GetPaths(uint32_t node, Path* results) override;

};

