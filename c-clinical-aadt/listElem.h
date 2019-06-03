#pragma once

#include "patient.h"

/* Defini��o do tipo de dados */
typedef Patient ListElem;

/* Defini��o de quaisquer outras opera��es que o tipo deve suportar, e.g., imprimir, comparar, etc. */
void listElemPrint(ListElem elem);
void listElemNormPrint(ListElem elem);
void listElemNeuralnetPrint(ListElem elem);
