#include "Menu.h"
#include "graphByList.h"
#include "graphByMatrix.h"
#include <string>
#include <iostream>


Menu::Menu()
{
	
}


Menu::~Menu()
{
}


void Menu::mainMenu()
{
	uint32_t startV, endV;
	std::vector<uint32_t> ARes;
	std::vector<Edge> BRes;
	uint32_t FFRes;
	std::string filename;
	bool directional, onPlane;
	char choice; //user choice
	char sub_choice;
	int vertices; //number of vertices
	int density; //density of the graph

	std::cout << "+------------------------------------+\n"
		"|          GRAPH  ALGORITHMS         |\n"
		"|           SDiZO  project           |\n"
		"|            Marcin Koziel	          |\n"
		"|      Menu stolen from Julia Szulc  |\n"
		"+------------------------------------+\n\n"

		"                -MAIN MENU-           \n"
		"1 - Generate graph\n"
		"2 - Load graph STUB\n\n"

		"3 - A*\n"
		"4 - Boruvka \n\n"
		"5 - Ford-Fulkerson"
		"0 - Exit\n";

	while (true)
	{
		std::cout << "--------------------------------------\n"
			"Choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case '1': //Generate input
			do
			{
				std::cout << std::endl << "Enter the number of vertices: ";
				std::cin >> vertices;
			
				std::cout << "Enter the graph's density (0,100]: ";
				std::cin >> density;

				std::cout << "Should the graph be on plane(required for A*) [0/1]: ";
				std::cin >> onPlane;

				std::cout << "Should the graph be directional[0/1]: ";
				std::cin >> directional;


			} while (vertices<0 || density > 100 || density < 0);

			do{
				std::cout << std::endl << "Choose representation. 1 - by List, 2 - by Matrix: ";
				std::cin >> sub_choice;
				
				switch (sub_choice)
				{
				case '1': graph = std::make_unique<graphByList>(vertices, directional);
					break;
				case '2': graph = std::make_unique<graphByMatrix>(vertices, directional);
					break;
				default:
					std::cout << std::endl << "Incorrect choice!" << std::endl;
					break;
				}

			} while (sub_choice!='1'&&sub_choice!='2');
			graph->generateRandomGraph(density, onPlane);
			graph->printMatrix();
			break;
		case '2'://load
			std::cout << "Should the graph be directional[0/1]: ";
			std::cin >> directional;

			std::cout << std::endl << "give path to file: ";
			std::cin >> filename;

			graph->resize(10);
			if (graph->loadGraphFromFileWithWages(filename))
				graph->printMatrix();
			else
				std::cout << "ERROR";
			
			break;
		case '3': //A*

			do {
				std::cout << std::endl << "Enter start and goal vertices: ";
				std::cin >> startV >> endV;
			}while (endV>=vertices || endV<0 ||startV>=vertices||startV<0);
			
				ARes=	graph->AStar(startV, endV);
				std::cout << "Path found: \n";
				for each (auto vertex  in ARes)
				{
					std::cout << vertex << ",";
				}
				std::cout<<std::endl;

			break;
		case '4': //Boruvka
			
			BRes = graph->Boruvka();
			std::cout << "Edges chosen[from-to(wage)]: \n";
			for each (auto edge in BRes)
			{
				std::cout << edge.from << "-"<<edge.to<<"("<<edge.wage<<")\t";
			}
			std::cout << std::endl;

			break;

		case '5': //FF
			do {
				std::cout << std::endl << "Enter start and goal vertices: ";
				std::cin >> startV >> endV;
			} while (endV >= vertices || endV < 0 || startV >= vertices || startV < 0);

			FFRes = graph->FordFulkerson(startV, endV);
			std::cout << "Maximum flow is: "<<FFRes <<  std::endl;

			break;
		
		case '6':

			if (graph->loadGraphFromFileWithWages("input/G2.txt"))
				graph->printMatrix();
			else
				std::cout << "ERROR";
		
		case '0': //Exit
			exit(0);
			break;
		default:
			std::cout << "Incorrect choice!" << std::endl;
		};
	}

}
