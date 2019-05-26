#pragma once

#include "clinicalData.h"

typedef struct date {
	int day;
	int month;
	int year;
} Date;

typedef char String[255];

typedef struct patient {
	int id; /*N�mero que identifica um paciente */
	Date birthdate; /*Data de nascimento*/
	char gender; /*G�nero (M ou F)*/
	String hospital; /*Nome do hospital de referencia do paciente*/
	String district; /*Distrito onde pertence o hospital*/
	ClinicalData clinicalData; /*Dados cl�nicos do doente (m�dias)*/
} Patient;

typedef struct Patient* PtPatient;
