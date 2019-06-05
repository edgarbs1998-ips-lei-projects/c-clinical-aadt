#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "load.h"
#include "string.h"
#include "listTad.h"
#include "date.h"
#include "patient.h"
#include "utils.h"

float incrementalAverage(float avg_n, int n, float v_n1) {
	if (n == 0) {
		return v_n1;
	}

	return ((avg_n * n) + (v_n1)) / (n + 1);
}

int findPatientById(PtList list, int id, Patient* patient, int* pos) {
	int size;
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, patient);
		if (patient->id == id) {
			*pos = i;
			return 1;
		}
	}
	return 0;
}

int getAge(Date actualdate, Date birthdate) {
	int age = actualdate.year - birthdate.year;
	if (actualdate.month < birthdate.month)
		age--;
	else if (actualdate.month == birthdate.month) {
		if (actualdate.day < birthdate.day)
			age--;
	}
	return age;
}

int loadPatientFile(String filePath, PtList patients) {
	FILE* f;
	int error = fopen_s(&f, filePath, "r"); //opens the file in read mode

	if (error) {
		printf("\n[ERROR] It was not possible to open the Patient file %s ...\n", filePath);
		return 0;
	}

	int patientID;
	char nextLine[1024];
	int countPatients = 0; //Patients count

	while (fgets(nextLine, sizeof(nextLine), f)) {
		if (strlen(nextLine) < 1)
			continue;

		nextLine[strlen(nextLine) - 1] = '\0';

		char** tokens = split(nextLine, 5, ";");
		//tokens[0] - id
		//tokens[1] - birthdate
		//tokens[2] - gender
		//tokens[3] - hospital
		//tokens[4] - district

		patientID = atoi(tokens[0]);

		int day, month, year;
		sscanf_s(tokens[1], "%d/%d/%d", &day, &month, &year);

		Date date = dateCreate(day, month, year);
		Patient newPatient = createPatient(patientID, date, tokens[2][0], tokens[3], tokens[4]);
		int size;
		listSize(patients, &size);
		listAdd(patients, size, newPatient);

		countPatients++;

		free(tokens);
	}
	fclose(f);

	return countPatients;
}

int loadClinicalDataFile(String filePath, PtList patients) {
	FILE* f;
	int error = fopen_s(&f, filePath, "r"); //opens the file in read mode

	if (error) {
		printf("\n[ERROR] It was not possible to open the ClinicalData file %s ...\n", filePath);
		return 0;
	}

	int patientID;
	char nextLine[1024];
	int clinicalDataCount = 0; //ClinicalData count

	while (fgets(nextLine, sizeof(nextLine), f)) {
		if (strlen(nextLine) < 1)
			continue;

		nextLine[strlen(nextLine) - 1] = '\0';

		char** tokens = split(nextLine, 6, ";");
		//tokens[0] - id
		//tokens[1] - date
		//tokens[2] - bmi
		//tokens[3] - glucose
		//tokens[4] - insulin
		//tokens[5] - mcp1

		int idPatient = atoi(tokens[0]);

		Patient tempPatient;

		int pos;
		if (findPatientById(patients, idPatient, &tempPatient, &pos) == 0) {
			printf("\n[ERROR] Could not find patient id %d! Ignoring this clinical data row...\n", idPatient);
			continue;
		};

		int day, month, year;
		sscanf_s(tokens[1], "%d/%d/%d", &day, &month, &year);
		Date registDate = dateCreate(day, month, year);

		tempPatient.clinicalData.age = (float)getAge(registDate, tempPatient.birthdate);
		tempPatient.clinicalData.bmi = incrementalAverage(tempPatient.clinicalData.bmi, tempPatient.clinicalData.clinicalDataCount, (float)atof(tokens[2]));
		tempPatient.clinicalData.glucose = incrementalAverage(tempPatient.clinicalData.glucose, tempPatient.clinicalData.clinicalDataCount, (float)atof(tokens[3]));
		tempPatient.clinicalData.insulin = incrementalAverage(tempPatient.clinicalData.insulin, tempPatient.clinicalData.clinicalDataCount, (float)atof(tokens[4]));
		tempPatient.clinicalData.mcp1 = incrementalAverage(tempPatient.clinicalData.mcp1, tempPatient.clinicalData.clinicalDataCount, (float)atof(tokens[5]));

		tempPatient.clinicalData.clinicalDataCount++;
		clinicalDataCount++;

		Patient oldElem;
		listSet(patients, pos, tempPatient, &oldElem);

		free(tokens);
	}
	fclose(f);

	return clinicalDataCount;
}

void loadData(PtList patients) {
	String filePatient, fileClinicalData;
	struct stat fileStat;

	printf("\n\nEnter the path of the Patient file: ");
	gets(filePatient, sizeof(filePatient));

	if (stat(filePatient, &fileStat) != 0) {
		printf("The entered file could not be found, please try again...\n\n");
		system("pause");
		return;
	}

	printf("\nEnter the path of the ClinicalData file: ");
	gets(fileClinicalData, sizeof(fileClinicalData));

	if (stat(fileClinicalData, &fileStat) != 0) {
		printf("The entered file could not be found, please try again...\n\n");
		system("pause");
		return;
	}

	int patientCount = loadPatientFile(filePatient, patients);
	int clinicalDataCount = loadClinicalDataFile(fileClinicalData, patients);

	printf("\nForam lidos %d pacientes e informação sobre %d dados clinicos\n\n", patientCount, clinicalDataCount);
	system("pause");
}
