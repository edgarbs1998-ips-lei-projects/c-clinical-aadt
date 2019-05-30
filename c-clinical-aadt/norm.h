#pragma once
#include "listTad.h"

PtList normalizeClinicalData(PtList patients);
void normalize(float *x, float max, float min, float k);
void listNormPrint(PtList list);
PtList normalizeClinicalDataNeuralNet(PtList patients);