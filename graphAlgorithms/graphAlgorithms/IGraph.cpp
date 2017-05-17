#include "IGraph.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <limits>
//#include "FiboHeap.h"

bool IGraph::loadGraphFromFileWithWages(std::string path)
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

void IGraph::generateRandomGraph(uint8_t density)
{
	uint32_t minRand=0;
	uint32_t maxRand= std::numeric_limits<uint32_t>::max()/2;
	bool onPlane = 1;
	if (coordinates)
		onPlane = 0;
	//generate cycle 
	uint32_t lastStop = amountOfVerticies - 1;
	for (uint32_t i = 0; i < lastStop; i++)
	{	
		//in initial cycle, we guarantee higher wages
		addEdge(i, i + 1, onPlane ? minRand + rand() % (maxRand - minRand) +maxRand : vector2::getDistance(coordinates[i], coordinates[i + 1]));
	}
	//close the cycle(last to first)	//I guess I could extract method here but time...
	addEdge(amountOfVerticies-1, 0, onPlane ? minRand + rand() % (maxRand - minRand) + maxRand : vector2::getDistance(coordinates[amountOfVerticies-1], coordinates[0]));
	amountOfEdges = amountOfVerticies;
	int32_t edgesLeft = density*amountOfVerticies*(amountOfVerticies - 1) / (directional ? 1 : 2) / 100 - amountOfVerticies;
	 std::vector <std::pair<uint32_t, uint32_t> > edgePool;	//holds edges available to choose from
	 
	 int initialPoolSize = amountOfVerticies*(amountOfVerticies - 1) / (directional ? 1 : 2) - amountOfVerticies;
	 if (initialPoolSize < 0)
		 return;
	 edgePool.reserve (initialPoolSize);
	 for (uint32_t i = 0; i < amountOfVerticies; i++)	//I hope it will be optimized by complier
		 for (uint32_t j = 0 ; j < amountOfVerticies;j++)
		{
			if(i!=j && i+1!=j )
				if(!(i == 0 && j== amountOfVerticies - 1))
					if(!directional||(i<j))
						
			edgePool.push_back(std::make_pair(i, j));
		}
	 uint32_t randomIndex, from, to;
	 while (edgesLeft>0)
	{
		randomIndex = rand() % edgePool.size();
		from = edgePool[randomIndex].first;
		to = edgePool[randomIndex].second;
		addEdge(from, to, onPlane ? minRand + rand() % (maxRand - minRand) : vector2::getDistance(coordinates[to], coordinates[from]));
		edgePool.pop_back();
		edgesLeft--;
	}

}
//used in A* to hold disovered nodes
struct VertexValue
{
	uint32_t F, G, H, from;
	const uint32_t total() { return F; }
	VertexValue(maxEdgeValue g, uint32_t h, uint32_t from)
	{
		G = g; //cost to get from "from" vertex
		H = h; //lowest possible cost, guessed by heuristics
		F = G + H;
		this->from = from;
	}
	VertexValue() {};

	friend bool operator<(const VertexValue& l, const VertexValue& r) 
	{
		return l.F < r.F; //using total() gives error
	}
	
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
