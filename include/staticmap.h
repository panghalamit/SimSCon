#ifndef STATICMAP_H
#define STATICMAP_H

#include <iostream>
#include "simdata.h"
#include "policy.h"
using namespace std;

class StaticMap : public Policy
{
  public:
  	StaticMap(SimData *s_data);
	void run(int phases);
	vector<int>* getMapping(int phase_number);
	vector<int>* getMigrationList(int phase_number);
};

#endif
