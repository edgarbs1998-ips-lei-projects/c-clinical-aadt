#include "calculateAvg.h"

CalculateAvg initializeCalculateAvg() {
	CalculateAvg calculateAvg;

	calculateAvg.sumAge = 0.0;
	calculateAvg.countAge = 0;

	calculateAvg.sumBmi = 0.0;
	calculateAvg.countBmi = 0;

	calculateAvg.sumGlucose = 0.0;
	calculateAvg.countGlucose = 0;

	calculateAvg.sumInsulin = 0.0;
	calculateAvg.countInsulin = 0;

	calculateAvg.sumMcp1 = 0.0;
	calculateAvg.countMcp1 = 0;

	return calculateAvg;
}

void addAgeToAvgCalculate(CalculateAvg* calculateAvg, float age) {
	calculateAvg->sumAge += age;
	calculateAvg->countAge++;
}

void addBmiToAvgCalculate(CalculateAvg* calculateAvg, float bmi) {
	calculateAvg->sumBmi += bmi;
	calculateAvg->countBmi++;
}

void addGlucoseToAvgCalculate(CalculateAvg* calculateAvg, float glucose) {
	calculateAvg->sumGlucose += glucose;
	calculateAvg->countGlucose++;
}

void addInsulinToAvgCalculate(CalculateAvg* calculateAvg, float insulin) {
	calculateAvg->sumInsulin += insulin;
	calculateAvg->countInsulin++;
}

void addMcp1ToAvgCalculate(CalculateAvg* calculateAvg, float mcp1) {
	calculateAvg->sumMcp1 += mcp1;
	calculateAvg->countMcp1++;
}
