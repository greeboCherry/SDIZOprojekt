#pragma once
#include <stdint.h>
#include <map>
#include <list>
using maxEdgeValue = int16_t;

//using edge = std::pair<uint32_t, maxEdgeValue>;//represents edge by target vertex index and edge wage



class IGraph
{
protected:
	uint32_t amountOfVerticies=0;
	uint32_t amountOfEdges = 0;
public:
	 /*  returns number of paths going from given vertex and creates array of them in @neighbours map
	 @vertex - vertex which we check for outgoing edges
	 @neighbours - < wage of edge to vertex, vertex index>	 */
	virtual void GetPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue> &neighbours) = 0;
	virtual void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage = 1) = 0;
	/*
		Valid format:
	1st line:				edgesNum vertixesNum
	each following line:	fromVertex toVertex wage
	*/
	bool loadGraphFromFile(std::string path);

	std::list<uint32_t> AStar(uint32_t startIndex, uint32_t targetIndex);

	//helper function for A*, not sure what exactly is correct here, gonna try http://www.cc.gatech.edu/~echow/pubs/levdiff-aaai.pdf
	maxEdgeValue getHeuristic(uint32_t vertexIndex);

	IGraph();
	~IGraph();
};

