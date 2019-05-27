#pragma once

typedef struct date {
	int day;
	int month;
	int year;
} Date;

typedef char String[255];

char** split(char* string, int nFields, const char* delim);
Date dateCreate(int day, int month, int year);
int date_cmp(Date d1, Date d2);
