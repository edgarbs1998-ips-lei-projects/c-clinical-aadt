#pragma once

#include "patient.h"

/* Definição do tipo de dados */
typedef Patient ListElem;

/* Definição de quaisquer outras operações que o tipo deve suportar, e.g., imprimir, comparar, etc. */
void listElemPrint(ListElem elem);
void listElemNormPrint(ListElem elem);
void listElemNeuralnetPrint(ListElem elem);
