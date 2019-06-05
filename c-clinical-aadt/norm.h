#pragma once

#include "listTad.h"

void normalize(float* x, float max, float min, float k);
PtList normalizeClinicalData(PtList list, int k);
void printNormalizedClinicalData(PtList list, int k);
void printNormalizeClinicalData(PtList patients);
