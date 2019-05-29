/* PROJETO  ATAD 2018-19
* Identificacao dos Alunos:
*
*      Numero: 180221098 | Nome: André Pereira
*      Numero: 180221082 | Nome: Edgar Santos
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "string.h"
#include "info.h"
#include "sort.h"
#include "avg.h"
#include "queue.h"
#include "checkDistrict.h"
#include "norm.h"
#include "loadT.h"

/* definicao de prototipos de funcoes, definidas depois do main() */
int equalsStringIgnoreCase(char str1[], char str2[]);
void printCommandsMenu();
//...

/*
* Descrição do Programa
*/
int main(int argc, char** argv) {

	/* declaracao de variaveis */
	PtList patientList = listCreate(10);
	PtList neuralNetList = listCreate(10);

	/* interpretador de comandos */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			/* vai provocar a saída do interpretador */
			quit = 1;
			QuitProgram(patientList);
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			importPatientsFromFile("patients.csv", "clinicalData.csv", patientList);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			clearData(&patientList);
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			printf("%18s %s %s %s %37s %12s %s %9s %s %s\n",
				"Indice", "BirthDate", "Sex", "Hospital", "District", "Age", "Bmi", "Glicose", "Insulin", "Mpc1");
			showData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "SORT")) {
			showSortMenu(patientList);
		}
		else if (equalsStringIgnoreCase(command, "AVG")) {
			averageClinicalData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "NORM")) {
			listNormPrint(normalizeClinicalData(patientList));
		}
		else if (equalsStringIgnoreCase(command, "QUEUE")) {
			queuePatients(patientList);
		}
		else if (equalsStringIgnoreCase(command, "CHECKDISTRICT")) {
			showCheckDistrictMenu(patientList);
		}
		else if (equalsStringIgnoreCase(command, "LOADT")) {
			importPatientsFromFile("patients_train.csv", "clinicalData_train.csv", neuralNetList);
		}
		else if (equalsStringIgnoreCase(command, "NORMT")) {
			printf("Comando NORMT nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "NEURALNET")) {
			printf("Comando NEURALNET nao implementado.\n");
		}
		else {
			printf("Comando não encontrado.\n");
		}
	}

	/* libertar memória e apresentar mensagem de saída. */

	return (EXIT_SUCCESS);
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: Patients and Clinical Data                      ");
	printf("\n===================================================================================");
	printf("\nA. Info about Patients (LOAD, SHOW, CLEAR).");
	printf("\nB. Aggregated info about patients and clinical data (SORT, AVG, NORM, QUEUE, CHECKDISTRICT).");
	printf("\nC. Advanced indicator (LOADT, NORMT, NEURALNET)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
