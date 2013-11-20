#include "staticmap.h"

StaticMap::StaticMap(SimData *s_data) : Policy(s_data){}

void StaticMap::run(int phases)
{
	run_for_phases = phases;
}

void StaticMap::getMapping(int phase_number, vector<int>* mapping)
{
	for(int i=0; i<num_phases; i++)
		(*mapping)[i] = i;
}

void StaticMap::getMigrationList(int phase_number, vector<int>* mapping)
{
	for(int i=0; i<num_phases; i++)
		(*mapping)[i] = -1;
}
