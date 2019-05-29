#include <stdio.h>

#include "listElem.h"
#include "patient.h"

void listElemPrint(ListElem elem) {
	printPatient(elem);
}

void listElemNormPrint(ListElem elem) {
	printNormPatient(elem);
}
