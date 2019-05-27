#include <stdio.h>
#include <string.h>

#include "districtAvg.h"

DistrictAvg createDistrictAvg(float age, float bmi, float glucose, float insulin, float mcp1) {
	DistrictAvg districtAvg;

	districtAvg.age = age;
	districtAvg.bmi = bmi;
	districtAvg.glucose = glucose;
	districtAvg.insulin = insulin;
	districtAvg.mcp1 = mcp1;

	return districtAvg;
}

void printDistrictAvg(DistrictAvg* districtAvg) {
	printf("DistrictAvg {age: %.2f, mbi: %.2f, glucose: %.2f, insulin: %.2f, mcp1: %.2f} \n", districtAvg->age, districtAvg->bmi, districtAvg->glucose, districtAvg->insulin, districtAvg->mcp1);
}
