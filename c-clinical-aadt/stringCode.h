#pragma once

#include "string.h"

typedef struct stringCode {
	String code; //a aloca��o TEM DE SER EST�TICA
} StringCode;

StringCode stringCodeCreate(char* str);