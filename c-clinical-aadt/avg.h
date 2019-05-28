#include "string.h"
#include "listTad.h"
#include "mapTad.h"
#include "calculateAvg.h"

void averageClinicalData(PtList patients);
PtMap averageClinicalDataMap(PtList list, int listSize);
int getDistrictsCount(PtList patients, int listSize);
void prepareDistrictAvg(PtList patients, int listSize, PtMap mapDistrictAvg);
void calculateDistrictAvg(PtMap mapDistrictAvg, CalculateAvg* calculateAvg, String currentDistrict);
