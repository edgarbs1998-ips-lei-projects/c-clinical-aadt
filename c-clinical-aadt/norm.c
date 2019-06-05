#include <stdio.h>
#include <string.h>

#include "norm.h"
#include "listTad.h"
#include "minMax.h"
#include "utils.h"

void normalize(float* x, float max, float min, float k) {
	(*x) = ((((*x) - min) / (max - min)) * (2 * k)) - k;
}

PtList normalizeClinicalData(PtList list, int k) {
	int size;
	listSize(list, &size);
	ListElem elem;

	MinMax minMax;
	getMinMax(list, size, &minMax);

	for (int i = 0; i < size; ++i) {
		listGet(list, i, &elem);

		normalize(&(elem.clinicalData.age), minMax.maxAge, minMax.minAge, k);
		normalize(&(elem.clinicalData.bmi), minMax.maxBmi, minMax.minBmi, k);
		normalize(&(elem.clinicalData.glucose), minMax.maxGlucose, minMax.minGlucose, k);
		normalize(&(elem.clinicalData.insulin), minMax.maxInsuline, minMax.minInsuline, k);
		normalize(&(elem.clinicalData.mcp1), minMax.maxMcp1, minMax.minMcp1, k);

		listSet(list, i, elem, &elem);
		
	}

	return list;
}

void printNormalizedClinicalData(PtList list, int k) {
	ListElem elem;
	int size;
	listSize(list, &size);

	printf("\nk=%d\n", k);
	printf("Ind. Age Bmi Glicose Insulin Mcp1\n");
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		printNormPatient(elem);
	}

	printf("\n");
	system("pause");
}

void printNormalizeClinicalData(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	// Initialize
	PtList auxList = copyList(patients);
	PtList normalizedClinicalData;

	// Pede ao utilizador o valor de K
	int k = 0;
	String input;

	printf("\n\nIntroduza o valor de k: ");
	gets(input, sizeof(input));

	k = atoi(input);

	// Handle data
	normalizedClinicalData = normalizeClinicalData(auxList, k);
	printNormalizedClinicalData(normalizedClinicalData, k);

	// Libertar memória
	listDestroy(&auxList);
}
