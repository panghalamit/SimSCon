/*
This class handles the input data. It reads from standard
input stream and provides API to access the data
*/

#ifndef SIMDSATA_H
#define SIMDSATA_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include "simdata.h"
using namespace std;

class SimSData
{
    int num_vms;
    int num_phases;
    float *arrival_rates;
    float *service_rates;
    SimData *sdata;

  public:
    SimSData(int, int);
    ~SimSData();
    void readInput();
    int getNumVM();
    int getNumPhases();
    float getArrivalRate(int);
    float getFixedServiceRate(int);
    SimData* getSimData();
};

#endif
