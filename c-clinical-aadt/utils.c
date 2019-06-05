#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "listTad.h"
#include "minMax.h"

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

int equalsStringIgnoreCase(char str1[], char str2[]) {
	char* lstr1, * lstr2;
	_strlwr_s(lstr1 = _strdup(str1), strlen(str1) + 1);
	_strlwr_s(lstr2 = _strdup(str2), strlen(str2) + 1);
	return (strcmp(lstr1, lstr2) == 0);
}

PtList copyList(PtList list) {
	int size;
	listSize(list, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	return auxList;
}

Date dateCreate(int day, int month, int year) {
	Date date;
	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}

int dateCmp(Date d1, Date d2) {
	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)
		return 0;
	else if (d1.year > d2.year || d1.year == d2.year && d1.month > d2.month || d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)
		return 1;
	else return -1;

}

int calculateAge(Date date) {
	int age = -1;

	time_t t = time(NULL);
	struct tm now;
	localtime_s(&now, &t);
	
	Date nowDate = dateCreate(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);

	if (date.year <= nowDate.year) {
		age = nowDate.year - date.year;

		if (date.month > nowDate.month) {
			--age;
		}
		else if (date.month == nowDate.month) {
			if (date.day > nowDate.day) {
				--age;
			}
		}
	}

	return age;
}

void getMinMax(PtList list, int listSize, MinMax *minMax) {
	ListElem elem;
	listGet(list, 0, &elem);

	minMax->minBirthDate = elem.birthdate;
	minMax->maxBirthDate = elem.birthdate;
	minMax->minAge = elem.clinicalData.age;
	minMax->maxAge = elem.clinicalData.age;
	minMax->minBmi = elem.clinicalData.bmi;
	minMax->maxBmi = elem.clinicalData.bmi;
	minMax->minGlucose = elem.clinicalData.glucose;
	minMax->maxGlucose = elem.clinicalData.glucose;
	minMax->minInsuline = elem.clinicalData.insulin;
	minMax->maxInsuline = elem.clinicalData.insulin;
	minMax->minMcp1 = elem.clinicalData.mcp1;
	minMax->maxMcp1 = elem.clinicalData.mcp1;

	for (int i = 1; i < listSize; ++i) {
		listGet(list, i, &elem);

		if (dateCmp(elem.birthdate, minMax->minBirthDate) < 0) {
			minMax->minBirthDate = elem.birthdate;
		}
		else if (dateCmp(elem.birthdate, minMax->maxBirthDate) > 0) {
			minMax->maxBirthDate = elem.birthdate;
		}

		if (elem.clinicalData.age < minMax->minAge) {
			minMax->minAge = elem.clinicalData.age;
		}
		else if (elem.clinicalData.age > minMax->maxAge) {
			minMax->maxAge = elem.clinicalData.age;
		}

		if (elem.clinicalData.bmi < minMax->minBmi) {
			minMax->minBmi = elem.clinicalData.bmi;
		}
		else if (elem.clinicalData.bmi > minMax->maxBmi) {
			minMax->maxBmi = elem.clinicalData.bmi;
		}

		if (elem.clinicalData.glucose < minMax->minGlucose) {
			minMax->minGlucose = elem.clinicalData.glucose;
		}
		else if (elem.clinicalData.glucose > minMax->maxGlucose) {
			minMax->maxGlucose = elem.clinicalData.glucose;
		}

		if (elem.clinicalData.insulin < minMax->minInsuline) {
			minMax->minInsuline = elem.clinicalData.insulin;
		}
		else if (elem.clinicalData.insulin > minMax->maxInsuline) {
			minMax->maxInsuline = elem.clinicalData.insulin;
		}

		if (elem.clinicalData.mcp1 < minMax->minMcp1) {
			minMax->minMcp1 = elem.clinicalData.mcp1;
		}
		else if (elem.clinicalData.mcp1 > minMax->maxMcp1) {
			minMax->maxMcp1 = elem.clinicalData.mcp1;
		}
	}
}

void showNoDataWarning() {
	printf("\n\nSEM DADOS CARREGADOS\n\n");
	system("pause");
}

void showNoTrainDataWarning() {
	printf("\nSEM DADOS DE TREINO CARREGADOS\n\n");
	system("pause");
}

void printPatientHeader() {
	printf("\n%15s %s %s %s %37s %12s %s %9s %s %s\n",
		"Indice", "BirthDate", "Sex", "Hospital", "District", "Age", "Bmi", "Glicose", "Insulin", "Mpc1");
}
