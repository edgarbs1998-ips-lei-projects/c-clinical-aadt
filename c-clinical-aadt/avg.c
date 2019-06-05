#include <stdlib.h>
#include <string.h>

#include "avg.h"
#include "string.h"
#include "listTad.h"
#include "mapTad.h"
#include "sort.h"
#include "districtAvg.h"
#include "calculateAvg.h"
#include "utils.h"

void calculateDistrictAvg(PtMap mapDistrictAvg, CalculateAvg* calculateAvg, String currentDistrict) {
	DistrictAvg createDistrict = createDistrictAvg(
		calculateAvg->sumAge / calculateAvg->countAge,
		calculateAvg->sumBmi / calculateAvg->countBmi,
		calculateAvg->sumGlucose / calculateAvg->countGlucose,
		calculateAvg->sumInsulin / calculateAvg->countInsulin,
		calculateAvg->sumMcp1 / calculateAvg->countMcp1
	);
	MapKey key = stringCodeCreate(currentDistrict);
	mapPut(mapDistrictAvg, key, createDistrict);
}

int getDistrictsCount(PtList patients, int listSize) {
	int counter = 0;

	String currentDistrict = { 0 };
	ListElem elem;

	for (int i = 0; i < listSize; ++i) {
		listGet(patients, i, &elem);

		if (strcmp(currentDistrict, elem.district) == 0) {
			continue;
		}

		++counter;
		strcpy_s(currentDistrict, sizeof currentDistrict, elem.district);
	}

	return counter;
}

void prepareDistrictAvg(PtList patients, int listSize, PtMap mapDistrictAvg) {
	if (listSize < 1) {
		return;
	}

	CalculateAvg calculateAvg;
	String currentDistrict = { 0 };
	ListElem elem;

	for (int i = 0; i < listSize; ++i) {
		listGet(patients, i, &elem);

		if (strcmp(currentDistrict, elem.district) != 0) {
			if (currentDistrict[0] != 0) {
				calculateDistrictAvg(mapDistrictAvg, &calculateAvg, currentDistrict);
			}

			strcpy_s(currentDistrict, sizeof currentDistrict, elem.district);
			calculateAvg = initializeCalculateAvg();
		}

		addAgeToAvgCalculate(&calculateAvg, elem.clinicalData.age);
		addBmiToAvgCalculate(&calculateAvg, elem.clinicalData.bmi);
		addGlucoseToAvgCalculate(&calculateAvg, elem.clinicalData.glucose);
		addInsulinToAvgCalculate(&calculateAvg, elem.clinicalData.insulin);
		addMcp1ToAvgCalculate(&calculateAvg, elem.clinicalData.mcp1);
	}
	calculateDistrictAvg(mapDistrictAvg, &calculateAvg, currentDistrict);
}

PtMap averageClinicalData(PtList patients) {
	int size;
	listSize(patients, &size);
	bubbleSortDistrict(patients, size);

	int districtsCount = getDistrictsCount(patients, size);
	PtMap districtsAvg = mapCreate(districtsCount);
	prepareDistrictAvg(patients, size, districtsAvg);

	return districtsAvg;
}

void printAverageClinicalData(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	// Initialize
	PtList auxList = copyList(patients);
	PtMap mapDistrictAvg = averageClinicalData(auxList);

	// Print
	printf("\n\nDistrict                Age  Bmi Glucose Insulin MCP1\n");
	mapPrint(mapDistrictAvg);
	printf("\n");
	system("pause");

	// Libertar memória
	listDestroy(&auxList);
	mapDestroy(&mapDistrictAvg);
}
