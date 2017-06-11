// NPcompleteProblems.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include <random>
#include <iostream>
#include "Knapsack.h"
#include "TestUnit.h"
#include "menu.h"
int main()
{

	TestUnit tu;
	menu klasaZmalej;
	klasaZmalej.mainMenu();
//	tu.testBoolsIncrement(5);
// 	for (int i = 0; i < 1;i++)
// 	{
// 		tu.showRandomKnapsack();
// 		std::cout << i << " didn't crash\n\n";
// 	}

//	tu.comapreBruteDynamicResults(1000);
//	tu.testInputS1();

	//5 liczb przedmiotow po 3 pojejmnosci
//  	for (int sackSize = 30; sackSize <= 90; sackSize += 30)
//  		for (int itemNum = 10; itemNum <= 30; itemNum += 5)
//  		{
//  			std::cout << "Running in the " << itemNum << sackSize << "'s" << std::endl;
//  			tu.testAndMeasure(itemNum, sackSize, 1);
//  		}
	//tu.testAndMeasure(30, 60, 1);

	
	//20.10 203 ms
	//21,10 441 ms
	//22,10 860 ms
	//23,10 1416 ms
	//24,10 2625 ms
	//25,10 4993 ms
	//tu.runOneBrute(200, 10);

	return 0;
}




// 
// int main()
// {
//     return 0;
// }

