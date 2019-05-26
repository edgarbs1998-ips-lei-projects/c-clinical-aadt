#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "patient.h"

char** split(char* string, int nFields, const char* delim);
void importPatientsFromFile(char* filename, char* fileNameClinicalData, PtList patients);
Patient createPatient(int id, Date birthDate, char gender, String hospital, String district);
Date dateCreate(int day, int month, int year);
void printPatient(PtPatient patient);
int findPatientById(PtList list, int id, Patient* patient1, int* pos);
