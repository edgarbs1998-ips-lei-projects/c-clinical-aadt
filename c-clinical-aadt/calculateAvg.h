#pragma once

#include <stdlib.h>

typedef struct calculateAvg {
	float sumAge;
	int countAge;

	float sumBmi;
	int countBmi;

	float sumGlucose;
	int countGlucose;

	float sumInsulin;
	int countInsulin;

	float sumMcp1;
	int countMcp1;
} CalculateAvg;

CalculateAvg initializeCalculateAvg();
void addAgeToAvgCalculate(CalculateAvg* calculateAvg, float age);
void addBmiToAvgCalculate(CalculateAvg* calculateAvg, float bmi);
void addGlucoseToAvgCalculate(CalculateAvg* calculateAvg, float glucose);
void addInsulinToAvgCalculate(CalculateAvg* calculateAvg, float insulin);
void addMcp1ToAvgCalculate(CalculateAvg* calculateAvg, float mcp1);
