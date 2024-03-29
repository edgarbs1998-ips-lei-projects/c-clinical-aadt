#pragma once

#include "date.h"
#include "string.h"
#include "clinicalData.h"

typedef struct patient {
	int id; /*N�mero que identifica um paciente */
	Date birthdate; /*Data de nascimento*/
	char gender; /*G�nero (M ou F)*/
	String hospital; /*Nome do hospital de referencia do paciente*/
	String district; /*Distrito onde pertence o hospital*/
	ClinicalData clinicalData; /*Dados cl�nicos do doente (m�dias)*/
} Patient;

Patient createPatient(int id, Date birthDate, char gender, String hospital, String district);
void printPatient(Patient patient);
void printNormPatient(Patient patient);
void printNeuralnetPatient(Patient patient);
