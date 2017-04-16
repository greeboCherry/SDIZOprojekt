#pragma once
#include <stdint.h>
#include <iostream>
/*
represents graph by matrix of edges between verticles

*/
template <size_t amountOfVerticies>
class graphByMatrix 
{
	using maxEdgeValue = int16_t;		//determines how much memory should those damn wages take of my memory
private:
	size_t amountOfEdges;
	maxEdgeValue edges[amountOfVerticies][amountOfVerticies];
public:
	size_t getNumVerticies() const { return amountOfVerticies; }
	graphByMatrix() { 	memset(edges, 0, sizeof(edges));	}	//zero all edges so we know it's empty
	void printMatrix();	//print NxN rows representing edges
	void addEdge(size_t v1, size_t v2, bool directional=false);		
	void addEdge(size_t v1, size_t v2, maxEdgeValue wage);

};

