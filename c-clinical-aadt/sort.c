#include "sort.h"

// SORT BY BIRTHDATE
void sortByBirthDate(PtList list) {
	int size = 0;
	ListElem elem;
	PtList auxList = listCreate(10);
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	int size2 = 0;
	listSize(auxList, &size2);
	bubbleSortDate(auxList, size2);

	listPrint(auxList);
}



void bubbleSortDate(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (unsigned int i = 0; i < listSize; i++) {
		for (unsigned int j = 0; j < listSize - i - 1; j++) {

			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			int cmp = date_cmp(elem1.birthdate, elem2.birthdate);

			if (cmp > 0) {

				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}
		}
	}
}

int date_cmp(Date d1, Date d2)

{

	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)

		return 0;

	else if (d1.year > d2.year || d1.year == d2.year && d1.month > d2.month || d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)

		return 1;

	else return -1;

}

// SORT BY HOSPITAL

void sortByHospital(PtList list) {
	int size = 0;
	ListElem elem;
	PtList auxList = listCreate(10);
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	int size2 = 0;
	listSize(auxList, &size2);
	bubbleSortHospital(auxList, size2);

	listPrint(auxList);
}

void bubbleSortHospital(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (unsigned int i = 0; i < listSize; i++) {
		for (unsigned int j = 0; j < listSize - i - 1; j++) {

			listGet(list, j, &elem1);
			listGet(list, j + 1, &elem2);

			if (strcmp(elem1.hospital, elem2.hospital) > 0)

			{
				listSet(list, j + 1, elem1, &elem2);
				listSet(list, j, elem2, &elem1);
			}

			if (strcmp(elem1.hospital, elem2.hospital) == 0) {

				int cmp = date_cmp(elem1.birthdate, elem2.birthdate);

				if (cmp > 0) {

					listSet(list, j + 1, elem1, &elem2);
					listSet(list, j, elem2, &elem1);
				}
			}
		}
	}
}

void sortByDistrict(PtList list) {
	int size = 0;
	ListElem elem;
	PtList auxList = listCreate(10);
	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	int size2 = 0;
	listSize(auxList, &size2);
	bubbleSortDistrict(auxList, size2);

	listPrint(auxList);
}

void bubbleSortDistrict(PtList list, int listSize) {

	ListElem elem1;
	ListElem elem2;

	for (unsigned int i = 0; i < listSize; i++) {
		for (unsigned int j = 0; j < listSize - i - 1; j++) {

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