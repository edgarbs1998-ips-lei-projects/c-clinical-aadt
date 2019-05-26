#include "utils.h"
#include "patient.h"
#include "list.h"

char** split(char* string, int nFields, const char* delim) {
	char** tokens = malloc(sizeof(char*) * nFields);

	int index = 0;

	char* next_token = NULL;

	char* token = (char*)strtok_s(string, delim, &next_token);

	while (token) {
		tokens[index++] = token;
		token = strtok_s(NULL, delim, &next_token);

	}

	return tokens;
}


void importPatientsFromFile(char* fileNamePatients, char* fileNameClinicalData, PtList patients) {
	FILE* f;
	int error = fopen_s(&f, fileNamePatients, "r"); //opens the file in read mode

	if (error) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatients);
		return;
	}

	int patientID;
	char nextLine[1024];
	int countPatients = 0; //Patients count
	int clinicalDataCount = 0; //ClinicalData count

	while (fgets(nextLine, sizeof(nextLine), f)) {
		if (strlen(nextLine) < 1)
			continue;

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
	int error2 = fopen_s(&f2, fileNameClinicalData, "r"); //opens the file in read mode

	if (error2) {
		printf("An error occured... It was not possible to open the file %s ...\n", fileNamePatients);
		return;
	}

	char nextLine2[1024];

	while (fgets(nextLine2, sizeof(nextLine2), f2)) {
		if (strlen(nextLine2) < 1)
			continue;

		char** tokens = split(nextLine2, 6, ";");
		//tokens[0] - id
		//tokens[1] - date
		//tokens[2] - bmi
		//tokens[3] - glucose
		//tokens[4] - insulin
		//tokens[5] - mcp1

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

		patient1.clinicalData.age = registDate - birthDate;
		patient1.clinicalData.bmi = incrementalAverage(patient1.clinicalData.bmi, patient1.clinicalData.clinicalDataCount, (float)atof(tokens[2]));

		int patientAge = atoi(tokens[2]);
		float bmi = (float)atof(tokens[3]);
		float glucose = (float)atof(tokens[4]);
		float insulin = (float)atof(tokens[5]);
		float mcp1 = (float)atof(tokens[6]);


		clinicalDataCount++;


		Patient oldElem;
		listSet(patients, pos, patient1, &oldElem);

		printf("Foram lidos %d pacientes e informação sobre %d dados clinicos \n", countPatients, clinicalDataCount);
		fclose(f);
	}
}

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

Date dateCreate(int day, int month, int year) {
	Date date;
	date.day = day;
	date.month = month;
	date.year = year;

	return date;
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


float incrementalAverage(float avg_n, int n, float v_n1) {
	if (n == 0) {
		return v_n1;
	}
	else {


	}
}
