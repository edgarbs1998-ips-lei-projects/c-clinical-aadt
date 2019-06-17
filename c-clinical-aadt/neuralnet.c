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

void initializeWeights(double weightIH[][HIDDEN_LAYER_SIZE+1], double wightHO[][OUTPUT_LAYER_SIZE+1]) {
	// Initialize weightIH
	for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
		for (int i = 0; i <= INPUT_LAYER_SIZE; ++i) {
			weightIH[i][h] = 0.5;
		}
	}

	// Initialize weightHO
	for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
		for (int h = 0; h <= HIDDEN_LAYER_SIZE; ++h) {
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

PtList compute(PtList normPatientsTrain, double weightIH[][HIDDEN_LAYER_SIZE+1], double weightHO[][OUTPUT_LAYER_SIZE+1]) {
	int normPatientsTrainSize;
	listSize(normPatientsTrain, &normPatientsTrainSize);

	ListElem elem;
	double sumH[INPUT_LAYER_SIZE+1];
	double sumO[OUTPUT_LAYER_SIZE+1];
	double hidden[HIDDEN_LAYER_SIZE+1];
	PtList outputList = listCreate(normPatientsTrainSize);

	// Repeat for all patients
	for (int p = 0; p < normPatientsTrainSize; ++p) {
		// Retrieve patient from the input list
		listGet(normPatientsTrain, p, &elem);

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
			for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
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

void printOutout(PtList output, PtList target) {
	//int diseaseTypeCounter[OUTPUT_LAYER_SIZE] = { 0 };
	int goodResults = 0;
	int badResults = 0;

	ListElem elemOutput;
	ListElem elemTarget;
	int outputSize;
	listSize(output, &outputSize);

	printf("\nInd. Age Bmi Glicose Insulin Mcp1 NeuralNet Results                   Original Results\n");
	for (int i = 0; i < outputSize; i++) {
		listGet(output, i, &elemOutput);
		listGet(target, i, &elemTarget);

		// Calculate disease type
		calculateDiseaseType(&elemTarget);
		
		printf("%3d %5.2f %5.2f %5.2f %5.2f %5.2f %d [%7.5f %7.5f %7.5f %7.5f] %d [%7.5f %7.5f %7.5f %7.5f]\n",
			elemOutput.id, elemOutput.clinicalData.age, elemOutput.clinicalData.bmi,
			elemOutput.clinicalData.glucose, elemOutput.clinicalData.insulin, elemOutput.clinicalData.mcp1,
			elemOutput.clinicalData.disease_type, elemOutput.clinicalData.disease_weight.c1, elemOutput.clinicalData.disease_weight.c2,
			elemOutput.clinicalData.disease_weight.c3, elemOutput.clinicalData.disease_weight.c4,
			elemTarget.clinicalData.disease_type, elemTarget.clinicalData.disease_weight.c1, elemTarget.clinicalData.disease_weight.c2,
			elemTarget.clinicalData.disease_weight.c3, elemTarget.clinicalData.disease_weight.c4);

		//++diseaseTypeCounter[elemOutput.clinicalData.disease_type - 1];

		if (elemOutput.clinicalData.disease_type == elemTarget.clinicalData.disease_type) {
			++goodResults;
		}
		else {
			++badResults;
		}
	}

	//printf("\n\nPatients Type Number\n");
	//for (int i = 0; i < OUTPUT_LAYER_SIZE; ++i) {
	//	printf("Type %d: %3d\n", i+1, diseaseTypeCounter[i]);
	//}

	printf("\n\nGood Results : %d  Bad Results : %d\n", goodResults, badResults);
	printf("Percentage Good Results = %.2f %%\n", goodResults * 100.0 / (goodResults + badResults));

	printf("\n");
	system("pause");
}

PtList train(PtList normPatientsTrain, double weightIH[][HIDDEN_LAYER_SIZE+1], double weightHO[][OUTPUT_LAYER_SIZE+1]) {
	int normPatientsTrainSize;
	listSize(normPatientsTrain, &normPatientsTrainSize);

	ListElem elem;
	double sumH[HIDDEN_LAYER_SIZE+1];
	double sumO[OUTPUT_LAYER_SIZE+1];
	double sumDOW[HIDDEN_LAYER_SIZE+1];
	double deltaO[OUTPUT_LAYER_SIZE+1];
	double deltaH[HIDDEN_LAYER_SIZE+1];
	double deltaWeightIH[INPUT_LAYER_SIZE + 1][HIDDEN_LAYER_SIZE + 1];
	double deltaWeightHO[HIDDEN_LAYER_SIZE + 1][OUTPUT_LAYER_SIZE + 1];
	double hidden[HIDDEN_LAYER_SIZE+1];
	double target[OUTPUT_LAYER_SIZE+1];
	PtList outputList = listCreate(normPatientsTrainSize);

	// Initialize deltaWeightIH and deltaWeightHO
	for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
		for (int i = 1; i <= INPUT_LAYER_SIZE; ++i) {
			deltaWeightIH[i][h] = 0.0;
		}
	}
	for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
		for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
			deltaWeightHO[h][o] = 0.0;
		}
	}

	// Repeat for all patients
	for (int p = 0; p < normPatientsTrainSize; ++p) {
		// Retrieve patient from the input list
		listGet(normPatientsTrain, p, &elem);

		// Retrieve target values for this patient
		target[1] = elem.clinicalData.disease_weight.c1;
		target[2] = elem.clinicalData.disease_weight.c2;
		target[3] = elem.clinicalData.disease_weight.c3;
		target[4] = elem.clinicalData.disease_weight.c4;

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
			for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
				sumO[o] += hidden[h] * weightHO[h][o];
			}
			double outputValue = sigmoide(sumH[o]);
			setOutputByIndex(&elem, o, outputValue);
			deltaO[o] = (target[o] - outputValue) * outputValue * (1.0 - outputValue);
		}

		// Back-propagate errors to hidden layer
		for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
			sumDOW[h] = 0.0;
			for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
				sumDOW[h] += weightHO[h][o] * deltaO[o];
			}
			deltaH[h] = sumDOW[h] * hidden[h] * (1.0 - hidden[h]);
		}

		// Update weights WeightIH
		for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
			deltaWeightIH[0][h] = TRAIN_ETA_VALUE * deltaH[h] + TRAIN_ALPHA_VALUE * deltaWeightIH[0][h];
			weightIH[0][h] += deltaWeightIH[0][h];
			for (int i = 1; i <= INPUT_LAYER_SIZE; ++i) {
				deltaWeightIH[i][h] = TRAIN_ETA_VALUE * getInputByIndex(&elem, i) * deltaH[h] + TRAIN_ALPHA_VALUE * deltaWeightIH[i][h];
				weightIH[i][h] += deltaWeightIH[i][h];
			}
		}

		// Update weights WeightHO
		for (int o = 1; o <= OUTPUT_LAYER_SIZE; ++o) {
			deltaWeightHO[0][o] = TRAIN_ETA_VALUE * deltaO[o] + TRAIN_ALPHA_VALUE * deltaWeightHO[0][o];
			weightHO[0][o] += deltaWeightHO[0][o];
			for (int h = 1; h <= HIDDEN_LAYER_SIZE; ++h) {
				deltaWeightHO[h][o] = TRAIN_ETA_VALUE * hidden[h] * deltaO[o] + TRAIN_ALPHA_VALUE * deltaWeightHO[h][o];
				weightHO[h][o] += deltaWeightHO[h][o];
			}
		}

		// Calculate disease type
		calculateDiseaseType(&elem);

		// Add computed patient to the output list
		listAdd(outputList, p, elem);
	}

	return outputList;
}

// Neuralnet menu
void showNeuralnetMenu(PtList patients, PtList normPatientsTrain, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]) {
	PtList outputList = listCreate(NULL);

	/* interpretador de comandos */
	char option;
	int exit = 0;

	do {
		system("cls");

		printf("\n===================================================================================");
		printf("\n                                     NEURALNET                                     ");
		printf("\n===================================================================================");
		printf("\n1 - Classifica e imprime os pacientes em 4 grupos de doenças com base nos seus dados clínicos (não treinado)");
		printf("\n2 - [WIP] Treina a rede neuronal com os valores carregados através do comando LOADT");
		printf("\n0 - Volta ao menu anterior, removendo da memória os dados referentes as redes neuronais");
		printf("\n\n");

		// Aguarda que o utilizador pressione um carater, ignora a tecla ENTER que causava comportamentos indesejados
		do {
			option = _getch();
		} while (option == 13 /* RETURN */);

		switch (option) {
		case '1':
			initializeWeights(weightIH, weightHO); // Temp code just to make sure weights are correctly set for the untrained neuralnet

			outputList = compute(normPatientsTrain, weightIH, weightHO);
			printOutout(outputList, normPatientsTrain);

			listDestroy(&outputList);
			break;
		case '2':
			outputList = train(normPatientsTrain, weightIH, weightHO);
			printOutout(outputList, normPatientsTrain);

			listDestroy(&outputList);
			break;
		case '0':
			exit = 1;
			break;
		}
	} while (exit == 0);
}

// Neuralnet initializer
void initializeNeuralnet(PtList patients, PtList patientsTrain) {
	if (listIsEmpty(patientsTrain) == 1) {
		showNoTrainDataWarning();
		return;
	}

	PtList auxPatientsTrain = copyList(patientsTrain);
	PtList normPatientsTrain = getNormalizeClinicalDataNeuralNet(auxPatientsTrain);

	double weightIH[INPUT_LAYER_SIZE + 1][HIDDEN_LAYER_SIZE + 1];
	double weightHO[HIDDEN_LAYER_SIZE + 1][OUTPUT_LAYER_SIZE + 1];

	initializeWeights(&weightIH, &weightHO);

	showNeuralnetMenu(patients, normPatientsTrain, weightIH, weightHO);

	// Libertar memória
	listDestroy(&auxPatientsTrain);
}
