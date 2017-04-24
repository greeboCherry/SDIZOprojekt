#include "graphByMatrix.h"


graphByMatrix::graphByMatrix(uint32_t verts, bool directional/*=false*/)
{
	this->directional = directional;
	amountOfVerticies = verts;
	edges = new maxEdgeValue[verts*verts];		//to keep all data in one memory block we use 1d array, use [x * width + y] to acces (x,y)
	memset(edges, 0, sizeof(maxEdgeValue)*amountOfVerticies*amountOfVerticies);	//zero all edges so we know it's empty
	
				//	for (int i = 0; i < verts*verts;i++) { edges[i] = i;} //might be used for debugging
	std::cout << sizeof(maxEdgeValue)*amountOfVerticies*amountOfVerticies;
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

void graphByMatrix::addEdge(uint32_t fromV, uint32_t toV, maxEdgeValue wage/*=1*/)
{
	edges[fromV*amountOfVerticies + toV] = wage;
	if(!directional)
		edges[toV*amountOfVerticies + fromV] = wage;
	//well, i'm not sure yet if it's necessary 
	/*
	else
		edges[toV*amountOfVerticies + fromV] = -wage;
	*/
}

uint32_t graphByMatrix::GetPaths(uint32_t node, Path* results)
{
	return uint32_t();
}



