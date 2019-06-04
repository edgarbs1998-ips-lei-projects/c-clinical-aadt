#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info.h"
#include "listTad.h"

// Clear data
void clearData(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	int size;
	listSize(list, &size);
	listClear(list);

	printf("\nForam apagados %d registos de pacientes\n\n", size);
	system("pause");
}

// Show data
void showData(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	printf("\n");
	printf("%18s %s %s %s %37s %12s %s %9s %s %s\n",
		"Indice", "BirthDate", "Sex", "Hospital", "District", "Age", "Bmi", "Glicose", "Insulin", "Mpc1");
	listPrint(list);

	printf("\n");
	system("pause");
}
