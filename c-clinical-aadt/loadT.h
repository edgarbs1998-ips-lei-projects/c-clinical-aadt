#pragma once

#include "listTad.h"
#include "string.h"

int loadPatientTrainFile(String filePath, PtList patients);
int loadClinicalDataTrainFile(String filePath, PtList patients);
void loadTrainData(PtList patients);
