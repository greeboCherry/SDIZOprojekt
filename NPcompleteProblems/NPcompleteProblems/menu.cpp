#include "menu.h"
#include "Knapsack.h"
#include "TestUnit.h"
#include <iostream>
#include <vector>
#include <memory>


menu::menu()
{
}


menu::~menu()
{
}


void menu::mainMenu()
{
	char choice;
	std::vector<Item> itemsResult;
	std::unique_ptr<Knapsack> myKnapsack;

	std::cout << "+------------------------------------+\n"
		"|        NP-complete Problems        |\n"
		"|           SDiZO  project           |\n"
		"|            Marcin Koziel	          |\n"
		"|									  |\n"
		"+------------------------------------+\n\n"

		"                -MAIN MENU-           \n"
		"1 - Generate random item pool\n"
		"2 - Load item pool from file\n\n"

		"3 - Run bruteforce \n"
		"4 - Run greedy \n"
		"5 - Run dynamic\n"
		"9 - Test everything STUB\n"
		"0 - Exit\n";



	while (true)
	{
		std::cout << "--------------------------------------\n"
			"Choice: ";
		std::cin >> choice;

		switch (choice)
		{
		case '1': //Generate input
			int itemNum, sackSize, minValue, maxValue, minSize, maxSize;
			do
			{

				std::cout << std::endl << "Enter the number of items: ";
				std::cin >> itemNum;

				std::cout << "Enter the Knapsack capacity: ";
				std::cin >> sackSize;

				std::cout << "Enter the minimum and maximum value of single item";
				std::cin >> minValue >> maxValue;

				std::cout << "Enter the minimum and maximum size of single item";
				std::cin >> minSize >> maxSize;


			} while (0);			//TODO ensure values are positive
			//Knapsack(int itemNum, int sackSize, int minItemSize, int maxItemSize, int minValue, int maxValue);	//runs randomLoot(...)until fullnes >=1.25
			myKnapsack = std::make_unique<Knapsack>(itemNum, sackSize, minSize, maxSize, minValue, maxValue);
			std::cout<<Knapsack::toString(myKnapsack->itemPool)<<std::endl;

			break;
		case '2'://load
		{
			std::string filename;

			std::cout << std::endl << "give path to file: ";
			std::cin >> filename;

			myKnapsack = std::make_unique<Knapsack>();
			myKnapsack->loadItemsFromFile(filename);
			std::cout << Knapsack::toString(myKnapsack->itemPool) << std::endl;
		}
			break;
		case '3': //bruteforce

			itemsResult=myKnapsack->brute();
			std::cout << Knapsack::toString(itemsResult)<<std::endl;

			break;
		case '4': //greedy
			itemsResult = myKnapsack->greedy();
			std::cout << Knapsack::toString(itemsResult) << std::endl;

			break;

		case '5': //dynamic 
			itemsResult = myKnapsack->dynamic();
			std::cout << Knapsack::toString(itemsResult) << std::endl;
			break;

 		case '9'://run all the tests
 		{
			TestUnit tu;
			for (int sackSize = 10; sackSize <= 100; sackSize += 4)
				for (int itemNum = 32; itemNum <= 100; itemNum += 4)
				{
					std::cout << "Running in the " << itemNum << sackSize << "'s" << std::endl;
					tu.testAndMeasure(itemNum, sackSize, 100, 0 /*itemNum<=26*/);
				}
 		}
 		break;



		case '0': //Exit
			exit(0);
			break;
		default:
			std::cout << "Incorrect choice!" << std::endl;
		};
	}

}
