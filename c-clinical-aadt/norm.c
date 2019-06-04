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
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	MinMax minMax;
	getMinMax(auxList, size, &minMax);

	for (int i = 0; i < size; ++i) {
		listGet(auxList, i, &elem);

		normalize(&(elem.clinicalData.age), minMax.maxAge, minMax.minAge, k);
		normalize(&(elem.clinicalData.bmi), minMax.maxBmi, minMax.minBmi, k);
		normalize(&(elem.clinicalData.glucose), minMax.maxGlucose, minMax.minGlucose, k);
		normalize(&(elem.clinicalData.insulin), minMax.maxInsuline, minMax.minInsuline, k);
		normalize(&(elem.clinicalData.mcp1), minMax.maxMcp1, minMax.minMcp1, k);

		listSet(auxList, i, elem, &elem);		
		
	}

	return auxList;
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

void printNormalizeClinicalData(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	PtList normalizedClinicalData;
	int k = 0;
	String input;

	// Pede ao utilizador o valor de K
	printf("\nIntroduza o valor de k: ");
	fgets(input, sizeof(input), stdin);
	input[strlen(input) - 1] = '\0';

	k = atoi(input);

	normalizedClinicalData = normalizeClinicalData(list, k);
	printNormalizedClinicalData(normalizedClinicalData, k);

	// Libertar memória
	listDestroy(&normalizedClinicalData);
}
