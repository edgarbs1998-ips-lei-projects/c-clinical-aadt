#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "string.h"
#include "utils.h"

// Bubble sort birthdate
void bubbleSortBirthDate(PtList list, int listSize) {
	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			int cmp = dateCmp(elem1.birthdate, elem2.birthdate);

			if (cmp > 0) {
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}
		}
	}
}

// Sort by birthdate
void sortByBirthDate(PtList list) {
	PtList auxList = copyList(list);
	int size;
	listSize(auxList, &size);

	bubbleSortBirthDate(auxList, size);

	printPatientHeader();
	listPrint(auxList);

	printf("\n");
	system("pause");

	listDestroy(&auxList);
}

// Bubble sort hospital
void bubbleSortHospital(PtList list, int listSize) {
	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			if (strcmp(elem1.hospital, elem2.hospital) > 0)
			{
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}

			if (strcmp(elem1.hospital, elem2.hospital) == 0) {
				int cmp = dateCmp(elem1.birthdate, elem2.birthdate);

				if (cmp > 0) {
					listSet(list, j + 1, elem1, &elem2);
					listSet(list, j, elem2, &elem1);
				}
			}
		}
	}
}

// Sort by hospital
void sortByHospital(PtList list) {
	PtList auxList = copyList(list);
	int size;
	listSize(auxList, &size);

	bubbleSortHospital(auxList, size);

	printPatientHeader();
	listPrint(auxList);

	printf("\n");
	system("pause");

	listDestroy(&auxList);
}

// Buble sort district
void bubbleSortDistrict(PtList list, int listSize) {
	ListElem elem1;
	ListElem elem2;

	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			if (strcmp(elem1.district, elem2.district) > 0)
			{
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}

			if (strcmp(elem1.district, elem2.district) == 0) {
				if (strcmp(elem1.hospital, elem2.hospital) > 0)
				{
					listSet(list, j + 1, elem1, &elem2);
					listSet(list, j, elem2, &elem1);
				}
			}
		}
	}
}

// Sort by district
void sortByDistrict(PtList list) {
	PtList auxList = copyList(list);
	int size;
	listSize(auxList, &size);

	bubbleSortDistrict(auxList, size);

	printPatientHeader();
	listPrint(auxList);

	printf("\n");
	system("pause");

	listDestroy(&auxList);
}

// Sort menu
void showSortMenu(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	/* interpretador de comandos */
	char option;
	int exit = 0;

	do {
		system("cls");

		printf("\n===================================================================================");
		printf("\n                                        SORT                                       ");
		printf("\n===================================================================================");
		printf("\n1 - Ordenar por data de nascimento");
		printf("\n2 - Ordenar por hospital (desempate pela data de nascimento)");
		printf("\n3 - Ordenar por distrito (desempate pelo hospital)");
		printf("\n0 - Volta ao menu anterior");
		printf("\n\n");

		// Aguarda que o utilizador pressione um carater, ignora a tecla ENTER que causava comportamentos indesejados
		do {
			option = _getch();
		} while (option == 13 /* RETURN */);

		switch (option) {
		case '1':
			sortByBirthDate(patients);
			break;
		case '2':
			sortByHospital(patients);
			break;
		case '3':
			sortByDistrict(patients);
			break;
		case '0':
			exit = 1;
			break;
		}
	} while (exit == 0);
}
