#include <stdlib.h>

#include "list.h"
#include "patient.h"

Patient createPatient(int id, Date birthDate, char gender, String hospital, String district) {
	Patient patient;
	patient.id = id;
	patient.birthdate = birthDate;
	patient.gender = gender;
	strcpy_s(patient.hospital, sizeof(patient.hospital), hospital);
	strcpy_s(patient.district, sizeof(patient.district), district);

	return patient;
}

void printPatient(Patient patient) {
	printf("%03d | %02d / %02d / %2d | %c | %-20s | %-20s \n", patient.id, patient.birthdate.day, patient.birthdate.month, patient.birthdate.year,
		patient.gender, patient.hospital, patient.district);
}

int findPatientById(PtList list, int id, Patient* patient, int* pos) {
	int size;
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, patient);
		if (patient->id == id) {
			pos = i;
			return 1;
		}
	}
	return 0;
}
