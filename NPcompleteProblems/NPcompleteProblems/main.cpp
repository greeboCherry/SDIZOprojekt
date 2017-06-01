// NPcompleteProblems.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include <random>
#include <iostream>
#include "Knapsack.h"
static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
							  // initialize Mersennes' twister using rd to generate the seed
static std::mt19937 rng(rd());

int dice()
{
	static std::uniform_int_distribution<int> uid(1, 6); // random dice
	return uid(rng); // use rng as a generator
}

int main()
{
	std::vector<Knapsack> sacks;
	sacks.resize(2);
	sacks[0].resize(10);
	sacks[1].resize(100);

	 sacks[0].randomLoot(5, 1, 10, 0, 5);
	 sacks[1].randomLoot(10, 1, 10, 0, 50);


	std::cout << sacks[0].fullness <<std::endl<< Knapsack::toString(sacks[0].itemPool);
	std::cout << sacks[1].fullness << std::endl << Knapsack::toString(sacks[1].itemPool);
	std::cout << "Insert any char to exit\n";

	sacks[0].greedy();

	std::cin.get();
}




// 
// int main()
// {
//     return 0;
// }

