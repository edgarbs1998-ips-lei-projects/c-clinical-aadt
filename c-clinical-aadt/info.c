#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info.h"
#include "listTad.h"
#include "utils.h"

// Clear data
void clearData(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	int size;
	listSize(list, &size);
	listClear(list);

	printf("\n\nForam apagados %d registos de pacientes\n\n", size);
	system("pause");
}

// Show data
void showData(PtList list) {
	if (listIsEmpty(list) == 1) {
		showNoDataWarning();
		return;
	}

	printf("\n");
	printPatientHeader();
	listPrint(list);

	printf("\n");
	system("pause");
}
