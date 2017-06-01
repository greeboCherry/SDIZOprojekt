#include "TestUnit.h"
#include "graphByList.h"
#include "graphByMatrix.h"
#include <fstream>
#include <memory>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <windows.h>

using graphType = graphByList;

//using graphType = graphByMatrix;

void TestUnit::saveToFile(std::string fileName, std::string textContent)
{
	fileName = "output/" + fileName + ".txt";


	textContent = textContent +"\n";
	std::ofstream outfile(fileName, std::ofstream::out | std::ofstream::app);	//app starts writing at the end of file, out overwrites it
	if (outfile.is_open())
	{
		outfile.write(textContent.c_str(), textContent.size());
		outfile.close();
	}
	else
		std::cout << "Couldn't create file. Make sure that there is <output> folder in exe location.\nYour results\n" << textContent << std::endl;
}

void TestUnit::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("QueryPerformanceFrequency failed!\n");

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double TestUnit::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


void TestUnit::testG1Load()
{
	std::unique_ptr<IGraph> G = std::make_unique<graphType>(10);
	
	if (!G->loadGraphFromFileWithWages("input/G1.txt"))
	{
		std::cout << "Can't read output/G1.txt, tests not possible\n";
		return;
	}
	bool ok = true;
	std::map<uint32_t, maxEdgeValue> neighbours;
	G->getPaths(0, neighbours);
	if (neighbours.size() != 3)
		ok = false;

	G->getPaths(1, neighbours);
	if (neighbours.size() != 3)
		ok = false;
	G->getPaths(2, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	G->getPaths(3, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	G->getPaths(4, neighbours);
	if (neighbours.size() != 4)
		ok = false;

	G->getPaths(5, neighbours);
	if (neighbours.size() != 1)
		ok = false;

	G->getPaths(5, neighbours);
	if (neighbours.size() != 1)
		ok = false;

	G->getPaths(6, neighbours);
	if (neighbours.size() != 0)
		ok = false;

	G->getPaths(7, neighbours);
	if (neighbours.size() != 2)
		ok = false;

	std::cout << "testG1Load " << (ok ? "passed" : "failed") << std::endl;

}

void TestUnit::testG1AStar()
{
	std::unique_ptr<IGraph> G = std::make_unique<graphType>(10);

	if (!G->loadGraphFromFileWithWages("input/G1.txt"))
	{
		std::cout << "Can't read output/G1.txt, tests not possible\n";
		return;
	}
	auto path = G->AStar(0, 5);
	std::cout << "testG1AStar " << (path.size() == 4 ? "passed" : "failed") << " got " << path.size() << " expected 4" << std::endl;
}


void TestUnit::testRandomAStar()
{
	std::unique_ptr<IGraph> G = std::make_unique<graphType>(10);

	G->generateRandomGraph(40, true);
	auto path = G->AStar(0, 5);
	std::cout << "testRandomAStar didn't crash on plane(with heuristics)" << std::endl;
}

void TestUnit::testRandomBoruvka()
{
	std::unique_ptr<IGraph> G = std::make_unique<graphType>(10);
	G->generateRandomGraph(30, false);
}

void TestUnit::testRandomFF()
{
	std::unique_ptr<IGraph> G = std::make_unique<graphType>(10);
	G->generateRandomGraph(30, false);
	auto r = G->FordFulkerson(0, 4);
	std::cout << "testRandomFF didn't crash" << std::endl;
}

void TestUnit::testAndMeasure(uint32_t startSize/*=100*/, uint32_t endSize/*=1000*/, uint32_t deltaSize/*=100*/, uint32_t testCount /*= */)
{
	  auto gL= std::make_unique<graphByList>(1, false);
	  auto gM = std::make_unique<graphByMatrix>(1, false);
	  std::vector<Edge> edgeResult;

	  double Lresult, Mresult, LBresult, MBresult, LAresult, MAresult, LFFresult, MFFresult;
	std::string message;

	const uint8_t FFlimit = 16;

	for (uint32_t vertexCount = startSize; vertexCount <= endSize; vertexCount+=deltaSize)
	{
		std::cout << "Running in the " << vertexCount << "'s\n";
		for (uint8_t density = 25; density <= 100;density+=25)
		{//Boruvka, A*, Ford-Fulkerson
			LBresult = MBresult = LAresult = MAresult = LFFresult = MFFresult = 0;
			for (uint8_t t = 0; t < testCount; t++)
			{
			StartCounter();
			gL->resize(vertexCount);
			gL->generateRandomGraph(density);
			Lresult = GetCounter();
			message = "Generation for List type graph\t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t" + std::to_string(Lresult) + "\tms";
			saveToFile("ListGeneration", message);
			StartCounter();
			gM->resize(vertexCount);
			gM->generateRandomGraph(density);
			Mresult = GetCounter();
			message = "Generation of Matrix type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t" + std::to_string(Mresult) + "\tms";
			saveToFile("MatrixGeneration", message);

			StartCounter();
			gM->Boruvka();
			MBresult += GetCounter();
			StartCounter();
			edgeResult=gL->Boruvka();
			LBresult += GetCounter();
			
			StartCounter();
			gM->AStar(0, vertexCount/2);
			MAresult += GetCounter();
			StartCounter();
			gL->AStar(0, vertexCount / 2);;
			LAresult += GetCounter();

				
					StartCounter();
					gM->FordFulkerson(0, vertexCount / 2);
					MFFresult += GetCounter();
					StartCounter();
					gL->FordFulkerson(0, vertexCount / 2);;
					LFFresult += GetCounter();
				

			}//end of testCount loop
//Boruvka write
			MBresult /= testCount;
			message = "Boruvka for Matrix type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(MBresult) + "\tms";
			saveToFile("MatrixBoruvka", message);

			LBresult /= testCount;
			message = "Boruvka for List type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(LBresult) + "\tms";
			saveToFile("ListBoruvka", message);
//AStar write
			MAresult /= testCount;
			message = "AStar for Matrix type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(MAresult) + "\tms";
			saveToFile("MatrixAStar", message);

			LAresult /= testCount;
			message = "AStar for List type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(LAresult) + "\tms";
			saveToFile("ListAStar", message);

//Ford-Fulkerson write
			MFFresult /= FFlimit;
			message = "Ford-Fulkerson for Matrix type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(MFFresult) + "\tms";
			saveToFile("MatrixFF", message);

			LFFresult /= FFlimit;
			message = "Ford-Fulkerson for List type graph \t" + std::to_string(vertexCount) + "\tvertices and\t" + std::to_string(density) + "\t density took\t"
				+ std::to_string(LFFresult) + "\tms";
			saveToFile("LisFF", message);

		}
	}
// 
// 	resultString = "Raw init and deletion to\t\t\t\t " + std::to_string(gold->getSize()) +
// 		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
// 		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
// 		" ,insert value" + std::to_string(insertValue) + "\t\n";

}

