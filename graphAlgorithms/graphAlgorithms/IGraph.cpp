#include "IGraph.h"
#include <fstream>
#include <iostream>
#include <set>
#include <limits>

bool IGraph::loadGraphFromFile(std::string path)
{
	std::fstream file(path, std::fstream::in);
	if (!file)
	{
		std::cout << "Couldn't open file at: " << path.c_str() << std::endl;
		return false;
	}
	uint32_t fromV, toV, targetNumOfEdges;
	maxEdgeValue wage;
	file >> targetNumOfEdges >> amountOfVerticies;
	
	
	for (uint32_t i = 0; i < targetNumOfEdges; i++)
	{
		file >> fromV >> toV >> wage;
		addEdge(fromV, toV, wage);
	}
	file.close();
	return true;
}

struct VertexValue
{
	uint32_t F, G, H, from;
	uint32_t total() { return F; }
	VertexValue(maxEdgeValue g, uint32_t h, uint32_t from) 
	{
		G = g; //cost to get from "from" vertex
		H = h; //lowest possible cost, guessed by heuristics
		F = G + H; 
		this->from = from; }
	VertexValue() {};
};

std::list<uint32_t> IGraph::AStar(uint32_t startIndex, uint32_t targetIndex)
{
	std::list<uint32_t> path;
	std::map<uint32_t, VertexValue> closed, open;//<indexNumber, f(n)=g(n)+h(n); closed holds those already checked, open - those not
	std::map<uint32_t, maxEdgeValue> neighbours; //<indexNumber, cost from current V to vertex of given index
	uint32_t currentIndex; //index to current vertex we are considering

	open.emplace(startIndex, VertexValue(0,0,startIndex));
	
	uint32_t lowestF;
	while (!open.empty())
	{
		lowestF = std::numeric_limits<uint32_t>::max();
		for (auto o : open)	//among open nodes, find the cheapest one to go
		{
			if (o.second.total()<lowestF)
			{
				currentIndex = o.first;
				lowestF = o.second.total();
			}
		}
		closed.emplace(currentIndex, open.at(currentIndex));
		open.erase(currentIndex);
		GetPaths(currentIndex, neighbours);
		for each (auto n in neighbours)
		{
			if (n.first == targetIndex)	//If the node is the goal node, set its parent to the current node and store the final path.
			{
				path.push_front(targetIndex);
				path.push_front(currentIndex);
				do 
				{
					currentIndex = closed.at(currentIndex).from;
					path.push_front(currentIndex);
				} while (currentIndex!=startIndex);
				return path;
			}

			
			auto itc = closed.find(n.first);
				if (itc != closed.end())	//If the node is in the closed list, ignore it
					continue;	
				
			itc = open.find(n.first);
			if (itc == open.end())	//If the node is not in the closed list and the open list, set its parent to the current node and calculate its G and F value.
			{
				open.emplace(n.first, VertexValue(closed.at(currentIndex).G, getHeuristic(n.first), currentIndex));
			}
			else//If the node is not in the closed list but is in the open list, whether the path between it and the current node is quicker than its current path.
			{
				uint32_t n_g = n.second + closed.at(currentIndex).G;	//G of currently neighbor currently evaluated  
				if (itc->second.G > n_g)
					{
					 		itc->second.G = n_g;
							itc->second.from = currentIndex;
					}
			}
		}
	}

	return path;
}

maxEdgeValue IGraph::getHeuristic(uint32_t vertexIndex)
{
	return 0;	//NYI
}

IGraph::IGraph()
{
}


IGraph::~IGraph()
{
}
