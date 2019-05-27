#include <stdlib.h>
#include <string.h>

#include "avg.h"
#include "list.h"
#include "map.h"
#include "sort.h"
#include "districtAvg.h"
#include "calculateAvg.h"

void averageClinicalData(PtList patients) {
	int size;
	listSize(patients, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(patients, i, &elem);
		listAdd(auxList, i, elem);
	}

	bubbleSortDistrict(auxList, size);

	PtMap mapDistrictAvg = mapCreate(22); // TODO Set this to be dynamic
	calculateDistrictAvg(auxList, size, mapDistrictAvg);

	mapPrint(mapDistrictAvg);
}

void calculateDistrictAvg(PtList patients, int listSize, PtMap mapDistrictAvg) {
	String currentDistrict = { 0 };
	CalculateAvg calculateAvg;
	ListElem elem;

	for (int i = 0; i < listSize; ++i) {
		listGet(patients, i, &elem);

		if (strcmp(currentDistrict, elem.district) != 0) {
			if (currentDistrict[0] != 0) {
				DistrictAvg createDistrict = createDistrictAvg(
					calculateAvg.sumAge / calculateAvg.countAge,
					calculateAvg.sumBmi / calculateAvg.countBmi,
					calculateAvg.sumGlucose / calculateAvg.countGlucose,
					calculateAvg.sumInsulin / calculateAvg.countInsulin,
					calculateAvg.sumMcp1 / calculateAvg.countMcp1
				);
				StringCode key = stringCodeCreate(currentDistrict);
				mapPut(mapDistrictAvg, key, createDistrict);
			}

			strcpy_s(currentDistrict, sizeof currentDistrict, elem.district);
			calculateAvg = createCalculateAvg();
		}

		addAgeToAvgCalculate(&calculateAvg, elem.clinicalData.age);
		addBmiToAvgCalculate(&calculateAvg, elem.clinicalData.bmi);
		addGlucoseToAvgCalculate(&calculateAvg, elem.clinicalData.glucose);
		addInsulinToAvgCalculate(&calculateAvg, elem.clinicalData.insulin);
		addMcp1ToAvgCalculate(&calculateAvg, elem.clinicalData.mcp1);
	}

	// TODO FUCK this
			DistrictAvg createDistrict = createDistrictAvg(
				calculateAvg.sumAge / calculateAvg.countAge,
				calculateAvg.sumBmi / calculateAvg.countBmi,
				calculateAvg.sumGlucose / calculateAvg.countGlucose,
				calculateAvg.sumInsulin / calculateAvg.countInsulin,
				calculateAvg.sumMcp1 / calculateAvg.countMcp1
			);
			StringCode key = stringCodeCreate(currentDistrict);
			mapPut(mapDistrictAvg, key, createDistrict);
}
