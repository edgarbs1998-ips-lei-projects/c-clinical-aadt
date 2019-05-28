#pragma once

#include "date.h"
#include "string.h"
#include "minMax.h"
#include "listTad.h"

char** split(char* string, int nFields, const char* delim);
Date dateCreate(int day, int month, int year);
int dateCmp(Date d1, Date d2);
int equalsStringIgnoreCase(char str1[], char str2[]);
int calculateAge(Date date);
void getMinMax(PtList list, int listSize, MinMax* minMax);
