#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "checkDistrict.h"
#include "listTad.h"
#include "mapTad.h"
#include "string.h"
#include "avg.h"
#include "districtAvg.h"

// Check district menu
void showCheckDistrictMenu(PtList list) {
	// TODO Check if the list is empty to display an error message

	int size;
	listSize(list, &size);
	PtList auxList = listCreate(size);

	ListElem elem;
	for (int i = 0; i < size; ++i) {
		listGet(list, i, &elem);
		listAdd(auxList, i, elem);
	}

	PtMap districtsAvg = averageClinicalDataMap(auxList, size);

	/* interpretador de comandos */
	String district;

	setlocale(LC_ALL, "PT");
	do {

		printf("\n===================================================================================");
		printf("\n                                   CHECKDISTRICT                                   ");
		printf("\n===================================================================================");
		printf("\nPlease input the name of the district you want to check.");
		printf("\nTo go to the previous menu just press ENTER without any input.");
		printf("\n\nINPUT> ");

		fgets(district, sizeof(district), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		district[strlen(district) - 1] = '\0';

		if (district[0] == 0) {
			break;
		}

		MapValue districtAvg;
		MapKey key = stringCodeCreate(district);
		if (mapContains(districtsAvg, key) == 1) {
			mapGet(districtsAvg, key, &districtAvg);
			mapKeyPrint(key);
			mapValuePrint(districtAvg);
		}
		else {
			printf("The input district name does not exists...");
		}
	}
	while (1);
}
