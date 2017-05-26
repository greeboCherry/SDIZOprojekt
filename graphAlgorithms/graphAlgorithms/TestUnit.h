#pragma once
#include <string>

class TestUnit
{

	double PCFreq = 0.0;
	__int64 CounterStart = 0;
public:

	double GetCounter();
	void testG1Load();
	void testG1AStar();
	void testRandomAStar();
	void testRandomBoruvka();
	void testRandomFF();
	void testAndMeasure(uint32_t startSize=100, uint32_t endSize=1000, uint32_t deltaSize=100, uint32_t testCount = 100);
	static  void saveToFile(std::string fileName, std::string textContent);

	void StartCounter();
};
