#include "graphByMatrix.h"


graphByMatrix::graphByMatrix(uint32_t verts, bool directional/*=false*/)
{
	this->directed = directional;
	resize(verts);
}

graphByMatrix::graphByMatrix(const graphByMatrix& other)
{
	amountOfVerticies = other.amountOfVerticies;
	amountOfEdges = other.amountOfEdges;
	directed = other.directed;
	//vector2* coordinates; //let's skip this, ain't gonna be used, rly
	edges = new maxEdgeValue[amountOfEdges];
	memcpy(edges, other.edges, sizeof(maxEdgeValue)*amountOfVerticies*amountOfVerticies);
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
	if(!directed)
		edges[fromV*amountOfVerticies + toV] = wage;
}

void graphByMatrix::resize(uint32_t targetSize)
{
	delete[] edges;
	edges = new maxEdgeValue[targetSize*targetSize];
	amountOfVerticies = targetSize;
	memset(edges, -1, sizeof(maxEdgeValue)*amountOfVerticies*amountOfVerticies);	//set all edges at:doesn't exist
}

void graphByMatrix::getPaths(uint32_t vertex, std::map<uint32_t, maxEdgeValue> &neighbours)
{
	neighbours.clear();
	const uint32_t row = vertex*amountOfVerticies;	//we don't want to multiply it every time loop goes by, right?
	for (uint32_t i = 0; i < amountOfVerticies; i++)
	{
		if (edges[row + i] > 0)
			neighbours.emplace(i, edges[row + i]);
	}
}

IGraph* graphByMatrix::clone()
{
	graphByMatrix* newMatrix = new graphByMatrix(this->amountOfVerticies, directed);
	newMatrix->edges = new maxEdgeValue[amountOfVerticies*amountOfVerticies];
	memcpy(newMatrix->edges, edges, amountOfVerticies*amountOfVerticies*sizeof(maxEdgeValue));
	return newMatrix;
//	return new graphByMatrix(*this);
}

maxEdgeValue graphByMatrix::getPath(uint32_t from, uint32_t to)
{
	return edges[to*amountOfVerticies + from];
}

void graphByMatrix::modifyPath(uint32_t from, uint32_t to, int32_t deltaValue)
{
	if (edges[to*amountOfVerticies + from] > 0)
		edges[to*amountOfVerticies + from] += deltaValue;
	else
		//		throw std::logic_error("there is no such edge");
		edges[to*amountOfVerticies + from] = 0;
}

/*
	T  O
F X X X X
R X X X X
O X X X X
M X X X X
(x,y)=[x * width + y]
*/