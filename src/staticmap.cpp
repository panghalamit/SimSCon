#include "staticmap.h"

StaticMap::StaticMap(SimData *s_data) : Policy(s_data){}

void StaticMap::run(int phases)
{
	run_for_phases = phases;
}

vector<int>* StaticMap::getMapping(int phase_number)
{
	vector<int>* v = new vector<int>();
	for(int i=0; i<num_phases; i++)
		v->push_back(i);
	return v;
}

vector<int>* StaticMap::getMigrationList(int phase_number)
{
	vector<int>* v = new vector<int>();
	for(int i=0; i<num_phases; i++)
		v->push_back(-1);
	return v;
}
