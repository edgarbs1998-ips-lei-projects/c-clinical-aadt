/* PROJETO ATAD 2018-19
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
#include <windows.h>

#include "string.h"
#include "load.h"
#include "info.h"
#include "sort.h"
#include "avg.h"
#include "queue.h"
#include "checkDistrict.h"
#include "norm.h"
#include "loadT.h"
#include "normT.h"
#include "neuralnet.h"

/* definicao de prototipos de funcoes, definidas depois do main() */
void printCommandsMenu();

/*
* Descrição do Programa
*/
int main(int argc, char** argv) {

	/* declaracao de variaveis */
	PtList patientList = listCreate(10);
	PtList neuralNetList = listCreate(10);

	/* define o titulo da consola */
	SetConsoleTitle("C Clinical AADT");

	/* interpretador de comandos */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		system("cls");

		printCommandsMenu();

		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			/* vai provocar a saída do interpretador */
			quit = 1;
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			loadData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			clearData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			showData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "SORT")) {
			showSortMenu(patientList);
		}
		else if (equalsStringIgnoreCase(command, "AVG")) {
			printAverageClinicalData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "NORM")) {
			printNormalizeClinicalData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "QUEUE")) {
			initializeQueue(patientList);
		}
		else if (equalsStringIgnoreCase(command, "CHECKDISTRICT")) {
			initializeCheckDistrict(patientList);
		}
		else if (equalsStringIgnoreCase(command, "LOADT")) {
			loadTrainData(neuralNetList);
		}
		else if (equalsStringIgnoreCase(command, "NORMT")) {
			printNormalizeClinicalDataNeuralNet(neuralNetList);
		}
		else if (equalsStringIgnoreCase(command, "NEURALNET")) {
			initializeNeuralnet(patientList, neuralNetList);
		}
		else {
			printf("\n\nComando não encontrado.\n\n");
			system("pause");
		}
	}

	/* libertar memória e apresentar mensagem de saída. */
	listDestroy(&patientList);
	listDestroy(&neuralNetList);
	printf("\nGoodbye!\n");

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
