#include <stdio.h>
#include <string.h>

#include "normT.h"
#include "norm.h"
#include "listTad.h"
#include "utils.h"

PtList getNormalizeClinicalDataNeuralNet(PtList list) {
	PtList normalizedClinicalData;
	int k = NEURAL_NET_NORM_K;

	normalizedClinicalData = normalizeClinicalData(list, k);

	return normalizedClinicalData;
}

void printNormalizeClinicalDataNeuralNet(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	PtList normalizedClinicalData = getNormalizeClinicalDataNeuralNet(list);
	printNormalizedClinicalData(normalizedClinicalData, NEURAL_NET_NORM_K);

	// Libertar memória
	listDestroy(&normalizedClinicalData);
}