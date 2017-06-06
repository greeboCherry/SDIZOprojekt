// NPcompleteProblems.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include <random>
#include <iostream>
#include "Knapsack.h"
#include "TestUnit.h"

int main()
{
	TestUnit tu;
	//tu.testBoolsIncrement(5);
	for (int i = 0; i < 10;i++)
	{
		tu.showRandomKnapsack();
		std::cout << i << " didn't crush\n\n";
	}
	tu.comapreBruteDynamicResults(1000);
	
	std::cout << "Insert any char to exit\n";
	std::cin.get();

	return 0;
}




// 
// int main()
// {
//     return 0;
// }

