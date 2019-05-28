#pragma once

#include <stdlib.h>

#include "date.h"

typedef struct minMax {
	Date minBirthDate;
	Date maxBirthDate;

	float maxAge;
	float minAge;

	float minBmi;
	float maxBmi;

	float minGlucose;
	float maxGlucose;

	float minInsuline;
	float maxInsuline;

	float minMcp1;
	float maxMcp1;
} MinMax;
