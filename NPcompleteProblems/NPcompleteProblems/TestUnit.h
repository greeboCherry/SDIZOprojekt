#pragma once
class TestUnit
{
	double PCFreq = 0.0;
	__int64 CounterStart = 0;
public:
	TestUnit();
	~TestUnit();
	
	void StartCounter();
	double GetCounter();

	void showRandomKnapsack();
	void cornerCaseKnapsack();
	void testInputS1();
	void runOneBrute(int itemNum, int sackSize);
	
	void comapreBruteDynamicResults(int testNum);

	void testBoolsIncrement(int size);

	void testAndMeasure(int itemNum, int sackSize, int testNum, bool bTestBrute);
};

