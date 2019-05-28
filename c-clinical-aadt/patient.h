#pragma once

#include "date.h"
#include "string.h"
#include "clinicalData.h"

typedef struct patient {
	int id; /*Número que identifica um paciente */
	Date birthdate; /*Data de nascimento*/
	char gender; /*Género (M ou F)*/
	String hospital; /*Nome do hospital de referencia do paciente*/
	String district; /*Distrito onde pertence o hospital*/
	ClinicalData clinicalData; /*Dados clínicos do doente (médias)*/
} Patient;

Patient createPatient(int id, Date birthDate, char gender, String hospital, String district);
void printPatient(Patient patient);
