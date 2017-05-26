#include "IGraph.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <limits>
#include <queue>
#include <memory>



bool IGraph::loadGraphFromFileWithWages(std::string path)
{
	std::fstream file(path, std::fstream::in);
	if (!file||!file.good())
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

void IGraph::generateRandomGraph(uint8_t density, bool onPlane)
{
	uint32_t minRand=0;
	uint32_t maxRand= std::numeric_limits<uint32_t>::max()/2;
	// delete[] coordinates;
	if (onPlane)
	{
		maxEdgeValue maxCoord = std::numeric_limits<maxEdgeValue>::max()/4;
		coordinates = new vector2[amountOfVerticies];
		for (uint32_t i = 0; i < amountOfVerticies;i++)
		{
			coordinates[i].x = rand() % maxCoord;
			coordinates[i].y = rand() % maxCoord;
		}
	}

	//generate cycle 
	uint32_t lastStop = amountOfVerticies - 1;
	for (uint32_t i = 0; i < lastStop; i++)
	{	
		//in initial cycle, we guarantee higher wages
	
		addEdge(i, i + 1,
			onPlane ? 
			vector2::getDistance(coordinates[i], coordinates[i + 1]) :
			minRand + rand() % (maxRand - minRand) + maxRand);
	}
	//close the cycle(last to first)	//I guess I could extract method here but time...
	addEdge(amountOfVerticies-1, 0, onPlane ?
		vector2::getDistance(coordinates[amountOfVerticies-1], coordinates[0]):
		minRand + rand() % (maxRand - minRand) + maxRand);
	
	int32_t edgesLeft = density*amountOfVerticies*(amountOfVerticies - 1) / (directed ? 1 : 2) / 100 - amountOfVerticies;
	amountOfEdges += amountOfVerticies;
	 std::vector <std::pair<uint32_t, uint32_t> > edgePool;	//holds edges available to choose from
	 
	 int initialPoolSize = amountOfVerticies*(amountOfVerticies - 1) / (directed ? 1 : 2) - amountOfVerticies;
	 if (initialPoolSize < 0)
		 return;
	 edgePool.reserve (initialPoolSize);
	 //add edges to pool to choose from.
	 for (uint32_t i = 0; i < amountOfVerticies; i++)
		 //todo: try if j=i allows for deletion of j>i
		 for (uint32_t j = 0 ; j < amountOfVerticies;j++)
		{
			if(i==j || i+1==j || (i == amountOfVerticies - 1 && j == 0) //self joining and those edges in cycle
				||( !directed&&(i==j+1||(i==0&&j==amountOfVerticies-1) || j>i) )		//reverse cycle in non-directed 
				)
			continue;
				
						
			edgePool.push_back(std::make_pair(i, j));
		}
	 uint32_t randomIndex, from, to;
	 while (edgesLeft>0)
	{
		randomIndex = rand() % edgePool.size();
		from = edgePool[randomIndex].first;
		to = edgePool[randomIndex].second;
		addEdge(from, to, onPlane ? 
			vector2::getDistance(coordinates[to], coordinates[from]):
			minRand + rand() % (maxRand - minRand));
		edgePool.erase(edgePool.begin() + randomIndex);
		edgesLeft--;
	}

}
//used in A* to hold disovered nodes
struct VertexValue
{
	uint32_t F, G, H, from;
	const uint32_t total() { return F; }
	VertexValue(maxEdgeValue g, int32_t h, int32_t from)
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

std::vector<uint32_t> IGraph::AStar(uint32_t startIndex, uint32_t targetIndex)
{
	std::vector<uint32_t> path;
	std::map<uint32_t, VertexValue> closed, open;//<indexNumber, f(n)=g(n)+h(n); closed holds those already checked, open - those not
	std::map<uint32_t, maxEdgeValue> neighbours; //<indexNumber, cost from current V to vertex of given index
	uint32_t currentIndex; //index to current vertex we are considering

	open.emplace(startIndex, VertexValue(0,0,startIndex));
	
	uint32_t lowestF;
	while (!open.empty())
	{
		lowestF = std::numeric_limits<uint32_t>::max();
		for (auto o : open)	//among open nodes, find the cheapest one to go	//TODO use stl find?
		{
			if (o.second.total()<lowestF)
			{
				currentIndex = o.first;
				lowestF = o.second.total();
			}
		}
		closed.emplace(currentIndex, open.at(currentIndex));
		open.erase(currentIndex);
		getPaths(currentIndex, neighbours);
		for each (auto n in neighbours)
		{
			if (n.first == targetIndex)	//If the node is the goal node, set its parent to the current node and store the final path.
			{
				path.push_back(targetIndex);
				path.push_back(currentIndex);
				do 
				{
					currentIndex = closed.at(currentIndex).from;
					path.push_back(currentIndex);
				} while (currentIndex!=startIndex);
				return path;
			}

			
			auto itc = closed.find(n.first);
				if (itc != closed.end())	//If the node is in the closed list, ignore it
					continue;	
				
			itc = open.find(n.first);
			if (itc == open.end())	//If the node is not in the closed list and the open list, set its parent to the current node and calculate its G and F value.
			{
				open.emplace(n.first, VertexValue(closed.at(currentIndex).G, getHeuristic(n.first, targetIndex), currentIndex));
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
//it exists purely for Boruvka's sake, really
struct b_Tree
{
	
	std::set<uint32_t> verticesIncluded;
	std::set<Edge> edgesInlcuded;
	b_Tree(uint32_t initialVertex) { verticesIncluded.emplace(initialVertex); }
	

	void merge(b_Tree& other)
	{
		for each (auto e in other.edgesInlcuded)
		{
			edgesInlcuded.emplace(e);
		}
		for each (auto v in other.verticesIncluded)
		{
			verticesIncluded.emplace(v);
		}

	}

	//helper function for Boruvka
	bool containsVertex(uint32_t vertexIndex)
	{

		auto it = verticesIncluded.find(vertexIndex);
		return (it != verticesIncluded.end());
	}
};
auto comp = [](Edge& a, Edge& b) { return a.wage > b.wage; };//comparator for min heap for Boruvka


std::vector<Edge> IGraph::Boruvka()
{
	std::map<uint32_t, maxEdgeValue> neigbours;
	std::vector<Edge> result;
	result.reserve(amountOfVerticies - 1);

	//1.Initialize a forest T to be a set of one - vertex trees, one for each vertex of the graph.
	std::list<b_Tree> forest;
	for (uint32_t i = 0; i < amountOfVerticies; i++)
	{
		forest.push_back(b_Tree(i));

	}
	do  //2.   While T has more than one component:
	{
		for (auto currentTree = forest.begin(); currentTree != forest.end(); /*no increment here because of if in body*/)
			/*for each (auto currentTree in forest)*/
		{
			std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> queue(comp);
			for each (uint32_t indexNumber in currentTree->verticesIncluded)
			{
				getPaths(indexNumber, neigbours);
				for each (auto path in neigbours)
				{
					queue.push(Edge(indexNumber, path.first, path.second));
				}
			}
			//now we have all edges of subtree in queue
			bool merged = 0;//flag
			while (!queue.empty() && !merged)
			{
				Edge currentEdge = queue.top();
				//if the cheapest edge leads outside of current tree - merge!
				if (currentTree->verticesIncluded.find(currentEdge.to) == currentTree->verticesIncluded.end())
				{
					//TODO try using std::find_if

					for (auto it = forest.begin(); it != forest.end(); it++)
					{
						// 						//debug
						// 						for (auto itd = forest.begin(); itd != forest.end(); itd++)
						// 						{
						// 							std::cout << std::addressof(*itd) << std::endl;
						// 						}
						// 						//end of debug
						if (it->containsVertex(currentEdge.to))
						{
							if (it == currentTree)	//should not be here, anyway, it can crash without coming here
								std::cout << "WTF? you shouldn't be here!!!!!!!!" << std::endl;
							it->merge(*currentTree);
							currentTree = forest.erase(currentTree);
							//currentTree=forest.erase(std::next(currentTree).base());	//zamiana reverse iteratora na zwyk³y i erase
							result.push_back(currentEdge);
							merged = 1;

							break;
						}
						//	else
						//		currentTree++;//iterating both at once or sth?

					}
				}
				queue.pop();	//else drop it and we'll try next one

			}
			if (forest.size() == 1)
				break;
		}
		//std::cout << "Boruvka iteration" << std::endl;
	} while (forest.size() > 1);


	result.size(); //todo: put sth here
//	forest[0].edgesInlcuded;
	return result;
}

bool IGraph::findRoute(uint32_t from, uint32_t to, std::vector<int32_t> &routingTable)
{
	std::vector<bool> visited;
	visited.resize(amountOfVerticies, false);
	std::queue<uint32_t> q;
	
	q.push(from);//queue for throwing vertices through
	visited.at(from) = true;
	routingTable[from] = -1;

	while (!q.empty())
	{
		uint32_t currentVertex = q.front();
		q.pop();
		std::map<uint32_t, maxEdgeValue> neighbours;
		getPaths(currentVertex, neighbours);
		for each (auto n in neighbours)
		{
			if (!visited[n.first])
			{
				q.push(n.first);
				routingTable[n.first] = currentVertex;
				visited[n.first] = true;
			}
		}
	}

	return (visited[to]); //return if path between verticies exists
}


uint32_t IGraph::FordFulkerson(uint32_t source, uint32_t sink)
{
	volatile uint32_t result=0;//maximum flow

	std::unique_ptr<IGraph> residualGraph(clone());

	std::vector<int32_t> routingTable;
	routingTable.resize(amountOfVerticies, 0);
	//find next route
	while (residualGraph->findRoute(source, sink, routingTable))
	{
		int32_t flow = std::numeric_limits<int32_t>::max();
		volatile uint32_t currentVertex = sink;
		volatile uint32_t temp;//we need two vertices to get paths, right?
		//backtrack and find flow from that route
		while (currentVertex != source)
		{
			temp = routingTable[currentVertex];
			flow = std::min(flow, (int32_t)residualGraph->getPath(currentVertex, temp));
			currentVertex = temp;
		}
		//backtrack again and update cost of all edges along
		currentVertex = sink;
		while (currentVertex != source)
		{
			temp = routingTable[currentVertex];
			residualGraph->modifyPath(currentVertex, temp, -flow);
			residualGraph->modifyPath(temp, currentVertex, -flow);
			currentVertex = temp;
		}
		result += flow;
	}

	return result;
}

maxEdgeValue IGraph::getHeuristic(uint32_t from, uint32_t to)
{
	if(coordinates)
	return vector2::getDistance(coordinates[from], coordinates[to]);
	else return 0;
}

IGraph::IGraph()
{
}


IGraph::~IGraph()
{
	//delete[] coordinates;
}
