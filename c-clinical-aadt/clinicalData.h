#pragma once

#define DOENCA1 1
#define DOENCA2 2
#define DOENCA3 3
#define SEM_DOENCA 4

typedef struct clinicalData {
	float age; /* M�dia da idade em anos quando os dados foram obtidos */
	float bmi; /* Valores m�dios do Imc- Indice Massa corporal m�dio (Kg/m2) */
	float glucose; /* Valores m�dios da Glicose (mg/dl) */
	float insulin; /* Valores m�dios da Insulina (�U/ml) */
	float mcp1; /* Valores m�dios da Proteina MCP-1 (pg/ml)*/
	int disease_type; /* Classificacao do Doente 1 � Doen�a1 2 � Doen�a2 3 � Doen�a3 4 � Sem Doen�a Usado apenas na opcao NEURALNET*/

	int clinicalDataCount; /* Numero de vezes que os dados foram obtidos */
} ClinicalData;
