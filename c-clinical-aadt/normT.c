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

void printNormalizeClinicalDataNeuralNet(PtList patientsTrain) {
	if (listIsEmpty(patientsTrain) == 1) {
		showNoTrainDataWarning();
		return;
	}

	// Initialize
	PtList auxList = copyList(patientsTrain);
	PtList normalizedClinicalData;

	// Handle data
	normalizedClinicalData = getNormalizeClinicalDataNeuralNet(auxList);
	printNormalizedClinicalData(normalizedClinicalData, NEURAL_NET_NORM_K);

	// Libertar memória
	listDestroy(&auxList);
}