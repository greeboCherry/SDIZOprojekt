#include "TestUnit.h"
#include "graphByMatrix.h"

void TestUnit::testG1Load()
{
	IGraph *G = new graphByMatrix(10);
	
	if (!G->loadGraphFromFileWithWages("input/G1.txt"))
	{
		std::cout << "Can't read output/G1.txt, tests not possible\n";
		return;
	}
	bool ok = true;
	std::map<uint32_t, maxEdgeValue> neighbours;
	G->GetPaths(0, neighbours);
	if (neighbours.size() != 3)
		ok = false;

	G->GetPaths(1, neighbours);
	if (neighbours.size() != 3)
		ok = false;
	G->GetPaths(2, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	G->GetPaths(3, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	G->GetPaths(4, neighbours);
	if (neighbours.size() != 4)
		ok = false;

	G->GetPaths(5, neighbours);
	if (neighbours.size() != 1)
		ok = false;

	G->GetPaths(5, neighbours);
	if (neighbours.size() != 1)
		ok = false;

	G->GetPaths(6, neighbours);
	if (neighbours.size() != 0)
		ok = false;

	G->GetPaths(7, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	std::cout << "testG1Load " << (ok ? "passed" : "failed") << std::endl;

}

void TestUnit::testG1AStar()
{
	IGraph *G = new graphByMatrix(10);

	if (!G->loadGraphFromFileWithWages("input/G1.txt"))
	{
		std::cout << "Can't read output/G1.txt, tests not possible\n";
		return;
	}
	auto path = G->AStar(0, 5);
	std::cout << "testG1AStar " << (path.size()==4 ? "passed" : "failed") << " got " << path.size()<< " expected 4" <<std::endl;
}
