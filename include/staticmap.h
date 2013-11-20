#ifndef STATICMAP_H
#define STATICMAP_H

#include <iostream>
#include "simdata.h"
#include "policy.h"
using namespace std;

class StaticMap : public Policy
{
  public:
  	StaticMap(SimData*);
	void run(int);
	void getMapping(int, vector<int>*);
	void getMigrationList(int, vector<int>*);
};

#endif
