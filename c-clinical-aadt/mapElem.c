#include "mapElem.h"
#include "districtAvg.h"

void mapKeyPrint(MapKey key) {
	printf("%s \n", key.code);
}

void mapValuePrint(MapValue value) {
	printDistrictAvg(&value);
}

/* funcao de comparacao de chaves */
int mapKeyEquals(MapKey key1, MapKey key2) {
	return strcmp(key1.code, key2.code) == 0;
}
