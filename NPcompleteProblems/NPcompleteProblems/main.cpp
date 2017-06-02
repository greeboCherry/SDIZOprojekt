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
	tu.testBoolsIncrement(3);
	tu.showRandomKnapsack();

	std::cout << "Insert any char to exit\n";


	std::cin.get();

	return 0;
}




// 
// int main()
// {
//     return 0;
// }

