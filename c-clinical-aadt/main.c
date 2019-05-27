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

#include "info.h"

typedef char String[255];

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
			printf("Indice BirthDate Sex Hospital District Age Bmi Glicose Insulin Mpc1\n");
			showData(patientList);
		}
		else if (equalsStringIgnoreCase(command, "SORT")) {
			sortByDistrict(patientList);
		}
		else if (equalsStringIgnoreCase(command, "AVG")) {
			printf("Comando AVG nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "NORM")) {
			printf("Comando NORM nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "QUEUE")) {
			printf("Comando QUEUE nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "CHECKDISTRICT")) {
			printf("Comando CHECKDISTRICT nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "LOADT")) {
			printf("Comando MFOULG nao implementado.\n");
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

int equalsStringIgnoreCase(char str1[], char str2[]) {
	/* Apenas faz uma comparacao utilizando o strcmp.
	* Necessita de modificacao para obter uma comparacao
	* 'case insensitive' */
	return (strcmp(str1, str2) == 0);
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: Patients and Clinical Data                      ");
	printf("\n===================================================================================");
	printf("\nA. Info about players (LOAD, SHOW, CLEAR).");
	printf("\nB. Aggregated info about patients and clinical data (SORT, AVG, NORM, QUEUE, CHECKDISTRICT).");
	printf("\nC. Advanced indicator (LOADT, NORMT, NEURALNET)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
