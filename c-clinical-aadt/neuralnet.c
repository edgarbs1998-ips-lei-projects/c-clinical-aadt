#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#include "neuralnet.h"
#include "string.h"
#include "listTad.h"
#include "norm.h"

void initializeWeights(double weightIH[][HIDDEN_LAYER_SIZE+1], double deltaWeightIH[][HIDDEN_LAYER_SIZE+1], double wightHO[][OUTPUT_LAYER_SIZE+1], double deltaWeightHO[][OUTPUT_LAYER_SIZE+1]) {
	// Initialize weightIH and deltaWeightIH
	for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
		for (int i = 0; i <= INPUT_LAYER_SIZE; ++i) {
			deltaWeightIH[i][h] = 0.0;
			weightIH[i][h] = 0.5;
		}
	}

	// Initialize weightHO and deltaWeightHO
	for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
		for (int h = 0; h <= HIDDEN_LAYER_SIZE; ++h) {
			deltaWeightHO[h][o] = 0.0;
			wightHO[h][o] = 0.5;
		}
	}
}

double getInputByIndex(ListElem *elem, int index) {
	switch (index) {
	case 1:
		return elem->clinicalData.age;
		break;
	case 2:
		return elem->clinicalData.bmi;
		break;
	case 3:
		return elem->clinicalData.glucose;
		break;
	case 4:
		return elem->clinicalData.insulin;
		break;
	case 5:
		return elem->clinicalData.mcp1;
		break;
	default:
		return 0.0;
		break;
	}
}

void setOutputByIndex(ListElem* elem, int index, double value) {
	switch (index) {
	case 1:
		elem->clinicalData.disease_weight.c1 = value;
		break;
	case 2:
		elem->clinicalData.disease_weight.c2 = value;
		break;
	case 3:
		elem->clinicalData.disease_weight.c3 = value;
		break;
	case 4:
		elem->clinicalData.disease_weight.c4 = value;
		break;
	}
}

void calculateDiseaseType(ListElem* elem) {
	int diseaseType;
	double max;

	if (elem->clinicalData.disease_weight.c1 > elem->clinicalData.disease_weight.c2) {
		max = elem->clinicalData.disease_weight.c1;
		diseaseType = 1;
	}
	else {
		max = elem->clinicalData.disease_weight.c2;
		diseaseType = 2;
	}
	if (elem->clinicalData.disease_weight.c3 > elem->clinicalData.disease_weight.c4) {
		if (elem->clinicalData.disease_weight.c3 > max) {
			max = elem->clinicalData.disease_weight.c3;
			diseaseType = 3;
		}
	}
	else {
		if (elem->clinicalData.disease_weight.c4 > max) {
			max = elem->clinicalData.disease_weight.c4;
			diseaseType = 4;
		}
	}

	elem->clinicalData.disease_type = diseaseType;
}

double sigmoide(double x) {
	return 1.0 / (1.0 + exp(-x));
}

void exec(PtList normPatients, int normPatientsSize, double weightIH[][HIDDEN_LAYER_SIZE+1], double weightHO[][OUTPUT_LAYER_SIZE+1]) {
	ListElem elem;
	double sumH[INPUT_LAYER_SIZE+1];
	double sumO[OUTPUT_LAYER_SIZE+1];
	double hidden[HIDDEN_LAYER_SIZE+1];
	PtList output = listCreate(normPatientsSize);

	// Repeat for all patients
	for (int p = 0; p < normPatientsSize; ++p) {
		// Retrieve patient from the input list
		listGet(normPatients, p, &elem);

		// Compute hidden unit activations
		for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
			sumH[h] = weightIH[0][h];
			for (int i = 1; i <= INPUT_LAYER_SIZE; ++i) {
				sumH[h] += getInputByIndex(&elem, i) * weightIH[i][h];
			}
			hidden[h] = sigmoide(sumH[h]);
		}

		// Compute output init activations
		for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
			sumO[o] = weightHO[0][o];
			for (int h = 1; h < HIDDEN_LAYER_SIZE; ++h) {
				sumO[o] += hidden[h] * weightHO[h][o];
			}
			setOutputByIndex(&elem, o, sigmoide(sumH[o]));
		}

		// Calculate disease type
		calculateDiseaseType(&elem);

		// Add computed patient to the output list
		listAdd(output, p, elem);
	}

	//for (int rank = 0; rank < normPatientsSize; rank++) {
	//	listGet(output, rank, &elem);
	//	listElemNeuralnetPrint(elem);
	//}
}

//void train() {
//
//}

// Neuralnet menu
void showNeuralnetMenu(PtList ptList, PtList ptListTrain) {
	PtList normPatients = normalizeClinicalData(ptList);
	int normPatientsSize;
	listSize(normPatients, &normPatientsSize);
	PtList normTrain;

	double weightIH[INPUT_LAYER_SIZE+1][HIDDEN_LAYER_SIZE+1], deltaWeightIH[INPUT_LAYER_SIZE+1][HIDDEN_LAYER_SIZE+1];
	double weightHO[HIDDEN_LAYER_SIZE+1][OUTPUT_LAYER_SIZE +1], deltaWeightHO[HIDDEN_LAYER_SIZE +1][OUTPUT_LAYER_SIZE +1];

	initializeWeights(&weightIH, &deltaWeightIH, &weightHO, &deltaWeightHO);

	/* interpretador de comandos */
	String command;

	setlocale(LC_ALL, "PT");
	do {
		printf("\n===================================================================================");
		printf("\n                                     NEURALNET                                     ");
		printf("\n===================================================================================");
		printf("\nexec - Classifica e imprime os pacientes em 4 grupos de doenças com base nos seus dados clínicos.");
		printf("\ntrain - Treina a rede neuronal com os valores carregados através do comando LOADT.");
		printf("\nstop - Termina este processo da rede neuronal.");
		printf("\n\nCOMMAND> ");

		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "EXEC")) {
			exec(normPatients, normPatientsSize, weightIH, weightHO);
		}
		else if (equalsStringIgnoreCase(command, "TRAIN")) {
			//train();
		}
		else if (equalsStringIgnoreCase(command, "STOP")) {
			break;
		}
	} while (1);
}
