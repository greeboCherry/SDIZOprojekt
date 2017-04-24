#pragma once
#include <stdint.h>
using maxEdgeValue = int16_t;

//structure representing path or edge. other functions should know where it comes from.
struct Path
{
	maxEdgeValue wage;
	uint32_t	destination;
};

class IGraph
{
public:
	 //returns number of paths going from given node and creates array of them in @results variable
	 virtual uint32_t GetPaths(uint32_t node, Path* results)=0;



	IGraph();
	~IGraph();
};

