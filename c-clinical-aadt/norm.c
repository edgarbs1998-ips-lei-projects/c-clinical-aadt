#include "norm.h"
#include "minMax.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "listTad.h"


PtList normalizeClinicalData(PtList patients) {
	int size;
	listSize(patients, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(patients, i, &elem);
		listAdd(auxList, i, elem);
	}

	String command;
	float k = 0;
	printf("Introduza o valor de k\n");

	fgets(command, sizeof(command), stdin);
	command[strlen(command) - 1] = '\0';
	k = atof(command);

	MinMax minMax;
	getMinMax(auxList, size, &minMax);
	
	printf("%5s %4s %4s %3s %3s %3s\n",
		"Ind", "Age", "Bmi", "Glicose", "Insulin", "Mpc1");

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

void normalize(float *x, float max, float min, float k) {
	(*x) = ((((*x) - min) / (max - min)) *(2 * k)) - k;
}


void listNormPrint(PtList list) {
	int size;
	listSize(list,&size);
	ListElem elem;
	if (list == NULL)
		printf("LIST NULL \n");
	else if ( /*listIsEmpty(list)*/ size == 0)
		printf("LIST EMPTY \n");
	else {
		for (int rank = 0; rank < size; rank++) {
			listGet(list, rank, &elem);
			printNormPatient(elem);
		}

	}
}


PtList normalizeClinicalDataNeuralNet(PtList patients) {
	int size;
	listSize(patients, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(patients, i, &elem);
		listAdd(auxList, i, elem);
	}

	float k = 5;

	MinMax minMax;
	getMinMax(auxList, size, &minMax);

	printf("%5s %4s %4s %3s %3s %3s\n",
		"Ind", "Age", "Bmi", "Glicose", "Insulin", "Mpc1");

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


