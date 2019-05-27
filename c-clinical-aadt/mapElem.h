#pragma once

#include "stringCode.h"
#include "districtAvg.h"

/* definicao do tipo da chave */
typedef StringCode MapKey;
/* definicao do tipo do valor*/
typedef DistrictAvg MapValue;

void mapKeyPrint(MapKey key);
void mapValuePrint(MapValue value);

/* funcao de comparacao de chaves */
int mapKeyEquals(MapKey key1, MapKey key2);