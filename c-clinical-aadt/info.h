#pragma once

#include "listTad.h"

void importPatientsFromFile(char* filename, char* fileNameClinicalData, PtList patients);
int findPatientById(PtList list, int id, Patient* patient1, int* pos);
int getAge(Date actualdate, Date birthdate);
float incrementalAverage(float avg_n, int n, float v_n1);
void clearData(PtList *list);
void showData(PtList list);
void QuitProgram(PtList list);
