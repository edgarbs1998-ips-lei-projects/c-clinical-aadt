#pragma once

#include "clinicalData.h"

typedef struct date {
	int day;
	int month;
	int year;
} Date;

typedef char String[255];

typedef struct patient {
	int id; /*Número que identifica um paciente */
	Date birthdate; /*Data de nascimento*/
	char gender; /*Género (M ou F)*/
	String hospital; /*Nome do hospital de referencia do paciente*/
	String district; /*Distrito onde pertence o hospital*/
	ClinicalData clinicalData; /*Dados clínicos do doente (médias)*/
} Patient;

typedef struct Patient* PtPatient;
