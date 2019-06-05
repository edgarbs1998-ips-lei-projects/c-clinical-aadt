#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checkDistrict.h"
#include "listTad.h"
#include "mapTad.h"
#include "string.h"
#include "avg.h"
#include "districtAvg.h"
#include "utils.h"

void printCheckDistrict(PtMap districtsAvg, String district) {
	MapValue districtAvg;
	MapKey key = stringCodeCreate(district);

	if (mapContains(districtsAvg, key) == 1) {
		mapGet(districtsAvg, key, &districtAvg);

		printf("\n\nDistrict        Age  Bmi Glucose Insulin MCP1\n");
		mapKeyPrint(key);
		mapValuePrint(districtAvg);
	}
	else {
		printf("\n\nThe input district name does not exists...\n");
	}

	printf("\n");
	system("pause");
}

// Check district menu
void showCheckDistrictMenu(PtMap districtsAvg) {
	/* interpretador de comandos */
	String input;

	do {
		system("cls");

		printf("\n===================================================================================");
		printf("\n                                   CHECKDISTRICT                                   ");
		printf("\n===================================================================================");
		printf("\nPlease input the name of the district you want to check.");
		printf("\nTo go to the previous menu just press ENTER without any input.");
		printf("\n\nINPUT> ");

		fgets(input, sizeof(input), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		input[strlen(input) - 1] = '\0';

		if (input[0] == 0) {
			break;
		}

		printCheckDistrict(districtsAvg, input);
	}
	while (1);
}

// CheckDistrict initializer
void initializeCheckDistrict(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	PtList auxList = copyList(patients);
	PtMap districtsAvg = averageClinicalData(auxList);

	showCheckDistrictMenu(districtsAvg);

	// Libertar memória
	listDestroy(&auxList);
	mapDestroy(&districtsAvg);
}
