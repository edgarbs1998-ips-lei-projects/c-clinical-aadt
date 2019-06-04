#pragma once

#include "listTad.h"
#include "date.h"
#include "string.h"

int findPatientById(PtList list, int id, Patient* patient1, int* pos);
int getAge(Date actualdate, Date birthdate);
float incrementalAverage(float avg_n, int n, float v_n1);
int loadPatientFile(String filePath, PtList patients);
int loadClinicalDataFile(String filePath, PtList patients);
void loadData(PtList patients);
