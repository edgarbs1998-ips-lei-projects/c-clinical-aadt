#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loadT.h";
#include "info.h"
#include "listTad.h"
#include "patient.h"
#include "utils.h"


//LOADT
void importDataNeuralNet(char* fileNamePatientsTrain, char* fileNameClinicalDataTrain, PtList patients) {
	FILE* f;
	int error = fopen_s(&f, fileNamePatientsTrain, "r"); //opens the file in read mode

	if (error) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatientsTrain);
		return;
	}

	int patientID;
	char nextLine[1024];
	int countPatients = 0; //Patients count
	int clinicalDataCount = 0; //ClinicalData count

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

		free(tokens);
		countPatients++;
	}


	FILE* f2;
	int error2 = fopen_s(&f2, fileNameClinicalDataTrain, "r"); //opens the file in read mode

	if (error2) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatientsTrain);
		return;
	}

	char nextLine2[1024];

	while (fgets(nextLine2, sizeof(nextLine2), f2)) {
		if (strlen(nextLine2) < 1)
			continue;

		nextLine[strlen(nextLine2) - 1] = '\0';

		char** tokens = split(nextLine2, 11, ";");
		//tokens[0] - id
		//tokens[1] - date
		//tokens[2] - bmi
		//tokens[3] - glucose
		//tokens[4] - insulin
		//tokens[5] - mcp1
		//tokens[6] - type_disease
		//tokens[7] - c1
		//tokens[8] - c2
		//tokens[9] - c3
		//tokens[10] - c4

		int idPatient = atoi(tokens[0]);

		Patient patient1;

		int pos;
		if (findPatientById(patients, idPatient, &patient1, &pos) == 0) {
			printf("Error finding patient id!\n");
			system("pause");
			return;
		};


		int day, month, year;
		sscanf_s(tokens[1], "%d/%d/%d", &day, &month, &year);
		Date registDate = dateCreate(day, month, year);

		patient1.clinicalData.age = (float)getAge(registDate, patient1.birthdate);
		patient1.clinicalData.bmi = incrementalAverage(patient1.clinicalData.bmi, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[2]));
		patient1.clinicalData.glucose = incrementalAverage(patient1.clinicalData.glucose, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[3]));
		patient1.clinicalData.insulin = incrementalAverage(patient1.clinicalData.insulin, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[4]));
		patient1.clinicalData.mcp1 = incrementalAverage(patient1.clinicalData.mcp1, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[5]));
		patient1.clinicalData.disease_type = tokens[6];
		patient1.diseaseType.c1 = atof(tokens[7]);
		patient1.diseaseType.c2 = atof(tokens[8]);
		patient1.diseaseType.c3 = atof(tokens[9]);
		patient1.diseaseType.c4 = atof(tokens[10]);

		patient1.clinicalData.clinicalDataCount++;
		clinicalDataCount++;

		Patient oldElem;
		listSet(patients, pos, patient1, &oldElem);

	}
	fclose(f2);
	printf("Foram lidos %d pacientes e informação sobre %d dados clinicos \n", countPatients, clinicalDataCount);
}
