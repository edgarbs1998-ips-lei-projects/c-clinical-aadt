#pragma once

#include <stdlib.h>

#include "listTad.h"

#define INPUT_LAYER_SIZE 5
#define HIDDEN_LAYER_SIZE 5
#define OUTPUT_LAYER_SIZE 4

void showNeuralnetMenu(PtList ptList);
void initializeWeights(double* WeightIH[], double* DeltaWeightIH[], double* WeightHO[], double* DeltaWeightHO[]);
double getInputByIndex(ListElem* elem, int index);
void setOutputByIndex(ListElem* elem, int index, double value);
void calculateDiseaseType(ListElem* elem);
void exec(PtList normPatients, int normPatientsSize, double weightIH[][HIDDEN_LAYER_SIZE + 1], double weightHO[][OUTPUT_LAYER_SIZE + 1]);
double sigmoide(double x);