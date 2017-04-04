#include "TestUnit.h"
#include <iomanip>
#include <ctime>
#include <chrono>


void TestUnit::initVariables(int mode)
{
	
		amountOfNumbers = 50;
		maxValue = 100;
		minValue = 10;
		
			switch (mode % 3)
			{
			case 0:
			{
				amountOfNumbers = 50;

				break;
			}

			case 1:
			{
				amountOfNumbers = 500000;
				break;
			}
			case 2:
			{
				amountOfNumbers = 200000;

				break;
			}

			}
			switch (mode / 3)
			{
			case 0:
			{
				minValue = 10;
				maxValue = 100;
				break;
			}
			case 1:
			{
				minValue = -(2147483648 / 2);
				maxValue = 2147483647 / 2;
				break;
			}
			case 2:
				minValue = -2147483648;
				maxValue = 2147483647;
				break;
			}
		

		numbers = new int32_t[amountOfNumbers];
		for (uint32_t i = 0; i < amountOfNumbers; i++)
		{
			numbers[i] = minValue + rand() % (maxValue - minValue);	
		}


	

}

void TestUnit::testInsertArray(int runLenght)
{
	double frontInsertTime,
		midInsertTime,
		backInsertTime;
	std::string frontInsertString, midInsertString, backInsertString;


	minValue = -2147483648 / 2;
	maxValue = 2147483647 / 2;


	const int amountOfStructures=256;
	Array* gold = new Array();

	gold->initFromArray(numbers, amountOfNumbers);
	//gold->printStructure();

	int32_t insertLocation = amountOfNumbers / 2;	//at what point we insert that number
	int32_t insertValue = 1;
	Array* structures[amountOfStructures];

	//cheat init array so then we can delete it before first iteration
	for (int i = 0; i < amountOfStructures; i++)
	{
		structures[i] = new Array(*gold);
	}

	//iterate through operations on bigger and bigger array
	for (int testCount = 0; testCount < runLenght; testCount++)
	{
			frontInsertTime=midInsertTime=backInsertTime=0;

			for (int i = 0; i < amountOfStructures; i++)
			{
				
				delete structures[i];
				structures[i] = new Array(*gold);
			}
			StartCounter();
			for (int i = 0; i < amountOfStructures; i++)
			{
				structures[i]->pushFront(insertValue);
			}
		frontInsertTime = GetCounter() / amountOfStructures;
		frontInsertString = "Front\t insert to " + std::to_string(structures[0]->getSize()) + " elements:\t" +  std::to_string(frontInsertTime)+"\tms\n";
			
			for (int i = 0; i < amountOfStructures; i++)
			{
				delete structures[i];
				structures[i] = new Array(*gold);
			}
			StartCounter();
			for (int i = 0; i < amountOfStructures; i++)
			{
			
				structures[i]->insert(insertValue,insertLocation);
			}
		midInsertTime = GetCounter() / amountOfStructures;
		midInsertString = "Mid\t insert to " + std::to_string(structures[0]->getSize()) + " elements:\t" + std::to_string(midInsertTime) + "\tms\n";

			for (int i = 0; i < amountOfStructures; i++)
			{
				delete structures[i];
				structures[i] = new Array(*gold);
			}
			StartCounter();
			for (int i = 0; i < amountOfStructures; i++)
			{
				structures[i]->pushBack(insertValue);
			}
		backInsertTime = GetCounter() / amountOfStructures;
		backInsertString = "Back\t insert to " + std::to_string(structures[0]->getSize()) + " elements:\t" + std::to_string(backInsertTime) + "\tms\n";



	//	std::time_t currentTime = std::time(NULL);
	//	std::string filename(std::asctime(std::localtime(&currentTime)));
		FileWriter::saveToFile("ArrayResults", frontInsertString);
		FileWriter::saveToFile("ArrayResults", midInsertString);
		FileWriter::saveToFile("ArrayResults", backInsertString);

		gold->pushRandom(testCount);
	}
	for (int i = 0; i < amountOfStructures; i++)
	{
		delete structures[i];
	}
	delete gold;
}

void TestUnit::testInsertArray(uint32_t structSize, uint32_t testCount/*, int32_t insertValue = 1;*/)
{
	if (structSize == 0)
		structSize = amountOfNumbers;
	int32_t insertLocation = structSize / 2;	//at what point we insert that number
	int32_t insertValue = 1;

	double	operationTime = 0.0;
	std::string resultString;
	
	Array* gold= new Array();
	gold->initFromArray(numbers, structSize);
	Array* container; 

	StartCounter();
	for (uint32_t i = 0; i < testCount;i++)
	{
		container = new Array(*gold);
		container->pushFront(insertValue);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Front\t insert(with init and deletion) to\t " + std::to_string(gold->getSize()) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile("ArrayInsertResults", resultString);

	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Array(*gold);
		container->insert(insertValue, insertLocation);
		delete container;
	}

	operationTime = GetCounter();
	resultString = "Mid\t insert(with init and deletion) to\t " + std::to_string(gold->getSize()) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile("ArrayInsertResults", resultString);


	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Array(*gold);
		container->pushBack(insertValue);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Back\t insert(with init and deletion) to\t " + std::to_string(gold->getSize()) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile("ArrayInsertResults", resultString);


	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Array(*gold);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Raw init and deletion to\t\t\t\t " + std::to_string(gold->getSize()) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile("ArrayInsertResults", resultString);

	FileWriter::saveToFile("ArrayInsertResults", "\nTested " + std::to_string(testCount)+ " times\n------------------------\n");
	

}

void TestUnit::testInsertList(uint32_t structSize, uint32_t testCount)
{
	if (structSize == 0)
		structSize = structSize;
	int32_t insertLocation = structSize / 2;	//at what point we insert that number
	int32_t insertValue = 1;

	double	operationTime = 0.0;
	std::string resultString, filenameString="ListInsertResults";

	//List* gold = new List();

	List* container;

	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new List();
		for (uint32_t i = 0; i < structSize; i++)
		{
			container->pushBack(numbers[i]);
		}
		container->pushFront(insertValue);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Front\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new List();
		for (uint32_t i = 0; i < structSize; i++)
		{
			container->pushBack(numbers[i]);
		}
		container->insert(insertValue, insertLocation);
		delete container;
	}

	operationTime = GetCounter();
	resultString = "Mid\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);


	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new List();
			for (uint32_t i = 0; i < structSize; i++)
		{
			container->pushBack(numbers[i]);
		}
		container->pushBack(insertValue);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Back\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);


	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new List();
		for (uint32_t i = 0; i < structSize; i++)
		{
			container->pushBack(numbers[i]);
		}
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Raw init and deletion to\t\t\t\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	FileWriter::saveToFile(filenameString, "\nTested " + std::to_string(testCount) + " times\n------------------------\n");


}

void TestUnit::testSearch(uint32_t structSize, uint32_t testCount)
{
	if (structSize == 0)
		structSize = structSize;

	double	operationTimes[3] = { 0.0, 0.0, 0.0 };
	std::string resultString, filenameString = "SearchResults";


	//initialize test structures
	IContainer* containers[3];
	containers[0] = new Array();
	containers[1] = new List();
	containers[2] = new Heap();
	for (int j = 0; j < 3; j++)
		for (uint32_t i = structSize; i > 0; i--)
		{
			containers[j]->pushBack(i);
		}
	for (int j = 0; j < 3; j++)
	{
		StartCounter();
		for (uint32_t i = 0; i < testCount; i++)
		{
			if (containers[j]->findIf(0))
				throw std::logic_error("There was no zero, you NEET!");
		}
		operationTimes[j]=GetCounter() / testCount;
	}

	resultString = "Search results\tArray\tList\tHeap\t" + std::to_string(testCount) + " tests\t" + std::to_string(structSize) + "\t\n "
		+ std::to_string(operationTimes[0]) + "\t" + std::to_string(operationTimes[1]) + "\t" + std::to_string(operationTimes[2]) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	
}

void TestUnit::testHeap(uint32_t structSize, uint32_t testCount)
{

	if (structSize == 0)
		structSize = amountOfNumbers;
	int32_t insertLocation = structSize / 2;	//at what point we insert that number
	int32_t insertValue = 1;

	double	operationTime = 0.0;
	std::string resultString, filenameString = "HeapResults";

	Heap* gold = new Heap();

	Heap* container;

	operationTime = GetCounter();
	resultString = "Mid\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);


	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Heap(*gold);
		container->pushBack(insertValue);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Back\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Heap(*gold);
		container->popFront();
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Back\t insert(with init and deletion) to\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	StartCounter();
	for (uint32_t i = 0; i < testCount; i++)
	{
		container = new Heap(*gold);
		delete container;
	}
	operationTime = GetCounter();
	resultString = "Raw init and deletion to\t\t\t\t " + std::to_string(structSize) +
		"\telements:\t" + std::to_string(operationTime) + "\tms\t" +
		"Test parameters: max value " + std::to_string(maxValue) + " ,min value " + std::to_string(minValue) +
		" ,insert value" + std::to_string(insertValue) + "\t\n";
	FileWriter::saveToFile(filenameString, resultString);

	FileWriter::saveToFile(filenameString, "\nTested " + std::to_string(testCount) + " times\n------------------------\n");



}

