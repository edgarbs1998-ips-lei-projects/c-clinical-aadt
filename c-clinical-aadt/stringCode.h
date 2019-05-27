#pragma once

#include "utils.h"

typedef struct stringCode {
	String code; //a alocação TEM DE SER ESTÁTICA
} StringCode;

StringCode stringCodeCreate(char* str);