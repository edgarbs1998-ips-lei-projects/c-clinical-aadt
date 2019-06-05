#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>

#include "neuralnet.h"
#include "string.h"
#include "listTad.h"
#include "norm.h"
#include "normT.h"
#include "clinicalData.h"
#include "utils.h"

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
		diseaseType = DOENCA1;
	}
	else {
		max = elem->clinicalData.disease_weight.c2;
		diseaseType = DOENCA2;
	}
	if (elem->clinicalData.disease_weight.c3 > elem->clinicalData.disease_weight.c4) {
		if (elem->clinicalData.disease_weight.c3 > max) {
			max = elem->clinicalData.disease_weight.c3;
			diseaseType = DOENCA3;
		}
	}
	else {
		if (elem->clinicalData.disease_weight.c4 > max) {
			max = elem->clinicalData.disease_weight.c4;
			diseaseType = SEM_DOENCA;
		}
	}

	elem->clinicalData.disease_type = diseaseType;
}

double sigmoide(double x) {
	return 1.0 / (1.0 + exp(-x));
}

PtList compute(PtList normPatients, double weightIH[][HIDDEN_LAYER_SIZE+1], double weightHO[][OUTPUT_LAYER_SIZE+1]) {
	int normPatientsSize;
	listSize(normPatients, &normPatientsSize);

	ListElem elem;
	double sumH[INPUT_LAYER_SIZE+1];
	double sumO[OUTPUT_LAYER_SIZE+1];
	double hidden[HIDDEN_LAYER_SIZE+1];
	PtList outputList = listCreate(normPatientsSize);

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
		listAdd(outputList, p, elem);
	}

	return outputList;
}

void printOutout(PtList output) {
	int diseaseTypeCounter[OUTPUT_LAYER_SIZE] = { 0 };

	ListElem elem;
	int outputSize;
	listSize(output, &outputSize);

	printf("\nInd. Age Bmi Glicose Insulin Mcp1 NeuralNet Results\n");
	for (int i = 0; i < outputSize; i++) {
		listGet(output, i, &elem);
		listElemNeuralnetPrint(elem);

		++diseaseTypeCounter[elem.clinicalData.disease_type - 1];
	}

	printf("\n\nPatients Type Number\n");
	for (int i = 0; i < OUTPUT_LAYER_SIZE; ++i) {
		printf("Type %d: %3d\n", i+1, diseaseTypeCounter[i]);
	}

	printf("\n");
	system("pause");
}

//void train() {
//	if (listIsEmpty(ptListTrain) == 1) {
//		showNoTrainDataWarning();
//		return;
//	}
//
//  PtList auxPatientsTrain = copyList(patientsTrain);
//	PtList normTrain = normalizeClinicalData(auxPatientsTrain, NEURAL_NET_NORM_K);
//
//  listDestroy(&auxPatientsTrain);
//}

// Neuralnet menu
void showNeuralnetMenu(PtList normPatients, PtList patientsTrain, PtList outputList, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]) {
	/* interpretador de comandos */
	char option;
	int exit = 0;

	do {
		system("cls");

		printf("\n===================================================================================");
		printf("\n                                     NEURALNET                                     ");
		printf("\n===================================================================================");
		printf("\n1 - Classifica e imprime os pacientes em 4 grupos de doenças com base nos seus dados clínicos");
		printf("\n2 - Treina a rede neuronal com os valores carregados através do comando LOADT");
		printf("\n0 - Volta ao menu anterior, removendo da memória os dados referentes as redes neuronais");
		printf("\n\n");

		// Aguarda que o utilizador pressione um carater, ignora a tecla ENTER que causava comportamentos indesejados
		do {
			option = _getch();
		} while (option == 13 /* RETURN */);

		switch (option) {
		case '1':
			outputList = compute(normPatients, weightIH, weightHO);
			printOutout(outputList);

			listDestroy(&outputList);
			break;
		case '2':
			//train();
			break;
		case '0':
			exit = 1;
			break;
		}
	} while (exit == 0);
}

// Neuralnet initializer
void initializeNeuralnet(PtList patients, PtList patientsTrain) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	PtList auxPatients = copyList(patients);
	PtList normPatients = normalizeClinicalData(auxPatients, NEURAL_NET_NORM_K);
	PtList outputList = listCreate(NULL);

	double weightIH[INPUT_LAYER_SIZE + 1][HIDDEN_LAYER_SIZE + 1], deltaWeightIH[INPUT_LAYER_SIZE + 1][HIDDEN_LAYER_SIZE + 1];
	double weightHO[HIDDEN_LAYER_SIZE + 1][OUTPUT_LAYER_SIZE + 1], deltaWeightHO[HIDDEN_LAYER_SIZE + 1][OUTPUT_LAYER_SIZE + 1];

	initializeWeights(&weightIH, &deltaWeightIH, &weightHO, &deltaWeightHO);

	showNeuralnetMenu(normPatients, patientsTrain, outputList, weightIH, weightHO);

	// Libertar memória
	listDestroy(&auxPatients);
}
