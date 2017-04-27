#pragma once
#include <stdint.h>
#include <map>
using maxEdgeValue = int16_t;

//structure representing path or edge. other functions should know where it comes from.
struct Path
{
	uint32_t wage;	//wage index
	uint32_t	origin, destination; //inde xcal
};


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
	IGraph();
	~IGraph();
};

