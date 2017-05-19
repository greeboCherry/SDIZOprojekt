#pragma once
#include <stdint.h>
#include <map>
#include <list>
#include <set>
//#include "boost/heap/fibonacci_heap.hpp"
using maxEdgeValue = int16_t;

//using edge = std::pair<uint32_t, maxEdgeValue>;//represents edge by target vertex index and edge wage


struct Edge
{
	uint32_t from, to;//represent index of vertices, from should be lower than to, to keep some order
	maxEdgeValue wage;
	Edge(uint32_t fromV, uint32_t toV, maxEdgeValue wageV)
	{
		if (fromV>toV)
		{
			std::swap(fromV, toV);
		}
		from = fromV;
		to = toV;
		wage = wageV;
	}
};

struct vector2
{
	maxEdgeValue x, y;	//max wage is described by 

	vector2() {};
	
	vector2(maxEdgeValue x, maxEdgeValue y)
	{
		this->x = x;
		this->y = y;
	}
	static maxEdgeValue getDistance(vector2 &from, vector2 &to)
	{
		return (maxEdgeValue) sqrt(pow((to.x - from.x), 2) + pow((to.y - from.y), 2));
	}
};

class IGraph
{
protected:
	uint32_t amountOfVerticies=0;
	uint32_t amountOfEdges = 0;
	bool directed;
	vector2* coordinates; //holds array of coordinates of vertices.
public:
	 /*  returns number of paths going from given vertex and creates array of them in @neighbours map
	 @vertex - vertex which we check for outgoing edges
	 @neighbours - < wage of edge to vertex, vertex index>	 */
	virtual void getPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue> &neighbours) = 0;
	//adds edge between vertices of given indexes, with given wage, edge will be directed based on "directed" member variable
	virtual void addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage = 1) = 0;
	//changes amount of vertices and ERASES all edges
	virtual void resize(uint32_t targetSize) =0;
	virtual void printMatrix() = 0;
	/*
		Valid format:
	1st line:				edgesNum vertixesNum
	each following line:	fromVertex toVertex wage
	*/
	bool loadGraphFromFileWithWages(std::string path);
	//give density in 1-100, else it might not work. @onPlane decides if method should generate coordinates for vertices, required for heuristics of A*
	void generateRandomGraph(uint8_t density, bool onPlane = 1);

	std::list<uint32_t> AStar(uint32_t startIndex, uint32_t targetIndex);

	//helper function for A*
	maxEdgeValue getHeuristic(uint32_t vertexIndex);

	IGraph();
	~IGraph();
};

