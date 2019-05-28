#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "queue.h"
#include "queueTad.h"
#include "string.h"
#include "utils.h"
#include "listTad.h"
#include "queueAvg.h"
#include "minMax.h"

void queuePatients(PtList patients) {
	if (listIsEmpty(patients) == 1) {
		printf("List empty..."); // TODO Write error message
	}

	int size;
	listSize(patients, &size);

	QueueAvg queueAvg;
	getDataAvg(patients, size, &queueAvg);

	PtQueue ptQueue = queueCreate(size / 3);
	creteQueuePatients(ptQueue, patients, size, &queueAvg);

	showQueueMenu(ptQueue);
}

// Queue menu
void showQueueMenu(PtQueue ptQueue) {
	/* interpretador de comandos */
	String command;

	setlocale(LC_ALL, "PT");
	do {

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
			QueueElem elem;
			queueDequeue(ptQueue, &elem);

			queueElemPrint(elem);
		}
		else if (equalsStringIgnoreCase(command, "STOP")) {
			break;
		}
	} while (1);
}

void getDataAvg(PtList list, int listSize, QueueAvg *queueAvg) {
	MinMax minMax;
	getMinMax(list, listSize, &minMax);

	int minAge = calculateAge(minMax.maxBirthDate);
	int maxAge = calculateAge(minMax.minBirthDate);

	queueAvg->avgAge = (minMax.minAge + minMax.maxAge) / 2.0;
	queueAvg->avgBmi = (minMax.minBmi + minMax.maxBmi) / 2.0;
	queueAvg->avgGlucose = (minMax.minGlucose + minMax.maxGlucose) / 2.0;
	queueAvg->avgInsuline = (minMax.minInsuline + minMax.maxInsuline) / 2.0;
	queueAvg->avgMcp1 = (minMax.minMcp1 + minMax.maxMcp1) / 2.0;
}

void creteQueuePatients(PtQueue ptQueue, PtList patients, int listSize, QueueAvg *queueAvg) {
	ListElem elem;
	for (int i = 0; i < listSize; ++i) {
		listGet(patients, i, &elem);

		int age = calculateAge(elem.birthdate);
		if ((age < queueAvg->avgAge) || (age > queueAvg->avgAge &&
			elem.clinicalData.bmi < queueAvg->avgBmi && elem.clinicalData.glucose < queueAvg->avgGlucose &&
			elem.clinicalData.insulin < queueAvg->avgInsuline && elem.clinicalData.mcp1 < queueAvg->avgMcp1))
		{
			queueEnqueue(ptQueue, elem);
		}
	}
}
