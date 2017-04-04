#pragma once
#include <stdio.h>
#include "Array.h"
#include "List.h"
#include "Heap.h"
#include "IContainer.h"
#include "FileWriter.cpp"
#include <string>
#include <algorithm>
#include <windows.h>

class TestUnit
{

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

	uint32_t amountOfNumbers = 50;
	int32_t minValue = 10;
	int32_t maxValue = 100;
	

public:
	int32_t* numbers;
	IContainer* structure;
	

	void initVariables(int mode);

	void testInsertArray(int runLenght);
	void testInsertArray(uint32_t arraySize, uint32_t testCount);
	void testInsertList(uint32_t arraySize, uint32_t testCount);
	void testSearch(uint32_t arraySize, uint32_t testCount);
	void testHeap(uint32_t arraySize, uint32_t testCount);

	void StartCounter()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			printf("QueryPerformanceFrequency failed!\n");

		PCFreq = double(li.QuadPart) / 1000.0;

		QueryPerformanceCounter(&li);
		CounterStart = li.QuadPart;
	}
	double GetCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		return double(li.QuadPart - CounterStart) / PCFreq;
	}
};

