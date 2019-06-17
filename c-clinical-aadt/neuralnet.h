#pragma once

#include "listTad.h"

#define INPUT_LAYER_SIZE 5
#define HIDDEN_LAYER_SIZE 5
#define OUTPUT_LAYER_SIZE 4

#define TRAIN_ETA_VALUE 0.1
#define TRAIN_ALPHA_VALUE 0.2

void initializeWeights(double weightIH[][HIDDEN_LAYER_SIZE + 1], double wightHO[][OUTPUT_LAYER_SIZE + 1]);
double getInputByIndex(ListElem* elem, int index);
void setOutputByIndex(ListElem* elem, int index, double value);
void calculateDiseaseType(ListElem* elem);
double sigmoide(double x);
PtList compute(PtList normPatients, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]);
void printOutout(PtList output, PtList target);
PtList train(PtList normPatientsTrain, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]);
void showNeuralnetMenu(PtList normPatients, PtList patientsTrain, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]);
void initializeNeuralnet(PtList patients, PtList patientsTrain);
