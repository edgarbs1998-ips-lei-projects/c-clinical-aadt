#include <string.h>

#include "stringCode.h"

StringCode stringCodeCreate(char* str) {
	StringCode sc;
	strcpy_s(sc.code, sizeof(sc.code), str);
	return sc;
}
