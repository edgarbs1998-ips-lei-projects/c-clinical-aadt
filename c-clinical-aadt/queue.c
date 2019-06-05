#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "queueTad.h"
#include "string.h"
#include "utils.h"
#include "listTad.h"
#include "queueAvg.h"
#include "minMax.h"

void getDataAvg(PtList list, int listSize, QueueAvg *queueAvg) {
	MinMax minMax;
	getMinMax(list, listSize, &minMax);

	int minAge = calculateAge(minMax.maxBirthDate);
	int maxAge = calculateAge(minMax.minBirthDate);

	queueAvg->avgAge = (minAge + maxAge) / 2.0;
	queueAvg->avgBmi = (minMax.minBmi + minMax.maxBmi) / 2.0;
	queueAvg->avgGlucose = (minMax.minGlucose + minMax.maxGlucose) / 2.0;
	queueAvg->avgInsuline = (minMax.minInsuline + minMax.maxInsuline) / 2.0;
	queueAvg->avgMcp1 = (minMax.minMcp1 + minMax.maxMcp1) / 2.0;
}

void creteQueuePatients(PtQueue ptQueue, PtList patients, int listSize, QueueAvg *queueAvg) {
	int count = 0;
	ListElem elem;
	for (int i = 0; i < listSize; ++i) {
		listGet(patients, i, &elem);

		int age = calculateAge(elem.birthdate);
		if ((age < queueAvg->avgAge) || (age > queueAvg->avgAge &&
			elem.clinicalData.bmi < queueAvg->avgBmi && elem.clinicalData.glucose < queueAvg->avgGlucose &&
			elem.clinicalData.insulin < queueAvg->avgInsuline && elem.clinicalData.mcp1 < queueAvg->avgMcp1))
		{
			queueEnqueue(ptQueue, elem);
			++count;
		}
	}

	system("cls");
	printf("\n%d elements were copied to queue!\n\n", count);
	system("pause");
}

void nextQueueCommand(PtQueue ptQueue) {
	if (queueIsEmpty(ptQueue) == 1) {
		printf("\n\nNão existem mais elementos na fila...\n\n");
		system("pause");
		return;
	}

	QueueElem elem;
	queueDequeue(ptQueue, &elem);

	// Print
	printf("\n\nInd Birthdate Sex Hospital                             District          Age Bmi   Glicose Insulin Mcp1\n");
	queueElemPrint(elem);
	printf("\n");
	system("pause");
}

// Queue menu
void showQueueMenu(PtQueue patientsQueue) {
	/* interpretador de comandos */
	String command;

	do {
		system("cls");

		printf("\n===================================================================================");
		printf("\n                                       QUEUE                                       ");
		printf("\n===================================================================================");
		printf("\nnext - Retirar um elemento da fila e mostra a informação do paciente respetivo.");
		printf("\nstop - Termina este processo de repetição.");
		printf("\n\nCOMMAND> ");

		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "NEXT")) {
			nextQueueCommand(patientsQueue);
		}
		else if (equalsStringIgnoreCase(command, "STOP")) {
			break;
		}
		else {
			printf("\n\nComando não encontrado.\n\n");
			system("pause");
		}
	} while (1);
}

// Queue initializer
void initializeQueue(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		showNoDataWarning();
		return;
	}

	int size;
	listSize(patients, &size);

	QueueAvg queueAvg;
	getDataAvg(patients, size, &queueAvg);

	PtQueue patientsQueue = queueCreate(size / 3);
	creteQueuePatients(patientsQueue, patients, size, &queueAvg);

	showQueueMenu(patientsQueue);

	// Libertar memória
	queueDestroy(&patientsQueue);
}
