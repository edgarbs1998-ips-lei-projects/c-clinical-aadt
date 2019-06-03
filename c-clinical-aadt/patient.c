#include <string.h>
#include <stdio.h>

#include "patient.h"

Patient createPatient(int id, Date birthDate, char gender, String hospital, String district) {
	Patient patient;
	patient.id = id;
	patient.birthdate = birthDate;
	patient.gender = gender;
	strcpy_s(patient.hospital, sizeof(patient.hospital), hospital);
	strcpy_s(patient.district, sizeof(patient.district), district);
	patient.clinicalData.clinicalDataCount = 0;

	return patient;
}

void printPatient(Patient patient) {
	
	printf("%3d %02d/%02d/%2d %c %-37s %-18s %2.0f %7.4f %5.1f %7.4f %9.4f\n", 
		patient.id, patient.birthdate.day, patient.birthdate.month, patient.birthdate.year,
		patient.gender, patient.hospital, patient.district, patient.clinicalData.age,patient.clinicalData.bmi,
		patient.clinicalData.glucose,patient.clinicalData.insulin,patient.clinicalData.mcp1);
}

void printNormPatient(Patient patient) {
	printf("%5d %5.2f %5.2f %5.2f %5.2f %5.2f\n",
		patient.id,patient.clinicalData.age, patient.clinicalData.bmi,
		patient.clinicalData.glucose, patient.clinicalData.insulin, patient.clinicalData.mcp1);
}

void printNeuralnetPatient(Patient patient) {
	printf("%5d %5.2f %5.2f %5.2f %5.2f %5.2f %d [%7.5f %7.5f %7.5f %7.5f]\n",
		patient.id, patient.clinicalData.age, patient.clinicalData.bmi,
		patient.clinicalData.glucose, patient.clinicalData.insulin, patient.clinicalData.mcp1,
		patient.clinicalData.disease_type, patient.clinicalData.disease_weight.c1, patient.clinicalData.disease_weight.c2,
		patient.clinicalData.disease_weight.c3, patient.clinicalData.disease_weight.c4);
}
