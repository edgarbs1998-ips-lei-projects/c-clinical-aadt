#pragma once

#include "string.h"
#include "listTad.h"
#include "mapTad.h"
#include "calculateAvg.h"

void calculateDistrictAvg(PtMap mapDistrictAvg, CalculateAvg* calculateAvg, String currentDistrict);
int getDistrictsCount(PtList patients, int listSize);
void prepareDistrictAvg(PtList patients, int listSize, PtMap mapDistrictAvg);
PtMap averageClinicalData(PtList patients);
void printAverageClinicalData(PtList patients);
