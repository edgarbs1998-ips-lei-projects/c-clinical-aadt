#include <stdlib.h>
#include <string.h>

#include "utils.h"

char** split(char* string, int nFields, const char* delim) {
	char** tokens = malloc(sizeof(char*) * nFields);

	int index = 0;

	char* next_token = NULL;

	char* token = (char*)strtok_s(string, delim, &next_token);

	while (token) {
		tokens[index++] = token;
		token = strtok_s(NULL, delim, &next_token);

	}

	return tokens;
}

Date dateCreate(int day, int month, int year) {
	Date date;
	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}


int date_cmp(Date d1, Date d2)

{

	if (d1.day == d2.day && d1.month == d2.month && d1.year == d2.year)

		return 0;

	else if (d1.year > d2.year || d1.year == d2.year && d1.month > d2.month || d1.year == d2.year && d1.month == d2.month && d1.day > d2.day)

		return 1;

	else return -1;

}

