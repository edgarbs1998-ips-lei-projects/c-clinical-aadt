#include <stdlib.h>
#include <string.h>

#include "avgT.h"
#include "avg.h"
#include "listTad.h"
#include "utils.h"

void printAverageClinicalDataNeuralNet(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoTrainDataWarning();
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
