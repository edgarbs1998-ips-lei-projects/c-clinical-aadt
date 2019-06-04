#pragma once

typedef struct districtAvg {
	float age; /* media das idades no distrito */
	float bmi; /* media dos valores de IMC no distrito */
	float glucose; /* media dos valores de glicose no distrito */
	float insulin; /* media dos valores de insulina no distrito */
	float mcp1; /* media dos valores da proteina MCP1 no distrito */
} DistrictAvg;

DistrictAvg createDistrictAvg(float age, float bmi, float glucose, float insulin, float mcp1);
void printDistrictAvg(DistrictAvg* ptDistrictAvg);
