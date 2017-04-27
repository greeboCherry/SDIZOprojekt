#include "graphByMatrix.h"


graphByMatrix::graphByMatrix(uint32_t verts, bool directional/*=false*/)
{
	this->directional = directional;
	amountOfVerticies = verts;
	edges = new maxEdgeValue[verts*verts];		//to keep all data in one memory block we use 1d array, use [x * width + y] to acces (x,y)
	memset(edges, 0, sizeof(maxEdgeValue)*amountOfVerticies*amountOfVerticies);	//zero all edges so we know it's empty
	
}

void graphByMatrix::printMatrix()
{
	for (uint32_t i = 0; i < amountOfVerticies; i++)
			{
				for (uint32_t j = 0; j < amountOfVerticies; j++)
				{
					std::cout << edges[i*amountOfVerticies + j] << "\t";
				}

				std::cout << std::endl;
			}
}
/*
to make searching paths quicker(caching) let's assume form 
	T  O	
F X X X X
R X X X X
O X X X X
M X X X X
(x,y)=[x * width + y]
numeration starts from 0
*/
void graphByMatrix::addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage/*=1*/)
{
	edges[toV*amountOfVerticies + fromV] = wage;
	if(!directional)
		edges[fromV*amountOfVerticies + toV] = wage;
}

void graphByMatrix::GetPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue>& neighbours)
{
	neighbours.clear();
	const uint32_t row = vertex*amountOfVerticies;	//we don't want to multiply it every time loop goes by
	for (uint32_t i = 0; i < amountOfVerticies; i++)
	{
		if (edges[row + i] > 0)
			neighbours.emplace(i, edges[row + i]);
	}
}

//above: stl
//below: no stl and not working
/*
uint32_t graphByMatrix::GetPaths(uint32_t vertex, Path results[])
{
	//temp for the amount of edges going out of given vertex
	uint32_t result=0;
	const uint32_t row = vertex*amountOfVerticies;
	for (uint32_t i = 0; i < amountOfVerticies; i++)
	{
		if (edges[row + i] > 0)
			result++;
	}
	delete[] results;
	results = new Path[result];
	for (uint32_t i = 0; i < amountOfVerticies; i++)
	{
		if (edges[row + i] > 0)
		{
			results[i].wage = edges[row + i];
			results[i].destination = i;
		}

	}
	return result;
}
*/



