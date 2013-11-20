#include "simulation.h"

Simulation::Simulation(SimSData *ssdata)
{
	this->ssdata = ssdata;
	for(int i=0; i<ssdata->getNumVM(); i++)
		vmlist.push_back(new VM(ssdata, i));
	policy = new StaticMap(ssdata->getSimData());
}

void Simulation::start()
{
	sim_time = 0;
	phase_num = -1;
	migration_phase = false;
	event_list.push(Event(PHASE_BEGIN, 0, 0));
	event_list.push(Event(MIG_BEGIN, PHASE_LENGTH*(1-MIGRATIONDURATION), 0));
	for(unsigned int i=0; i<vmlist.size(); i++)
		event_list.push(Event(ARRIVAL, vmlist[i]->getNextInterArrivalTime(0), vmlist[i]->getIndex()));
	cout<<"Yay!! Simulation started..."<<endl;
}

void Simulation::run(double stop_time)
{
	policy->run((int)ceil(stop_time/PHASE_LENGTH));

	while(!event_list.empty())
	{
		// for(unsigned int i=0; i<vmlist.size(); i++)
		// cout<<vmlist[i]->num_phases<<" ";

		Event e = event_list.top();
		sim_time = e.getTime();
		float serv_time = -1;

		if(sim_time > stop_time)
			break;

		//e.printDetails();
		switch(e.getEventType())
		{
			case ARRIVAL:
				event_list.push(Event(ARRIVAL, sim_time+vmlist[e.getVMIndex()]->getNextInterArrivalTime(phase_num), e.getVMIndex()));
				if(vmlist[e.getVMIndex()]->isIdle())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(ssdata, policy, phase_num, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->updateOnArrival(sim_time, serv_time, phase_num);
				break;

			case DEPARTURE:
				if(!vmlist[e.getVMIndex()]->isEmptyQueue())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(ssdata, policy, phase_num, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->updateOnDeparture(sim_time, serv_time, phase_num);
				break;

			case PHASE_BEGIN:
				if(phase_num >= 0)
					for(int i=0; i<ssdata->getNumVM(); i++)
						vmlist[i]->updateOnPhaseChange(sim_time, phase_num);
				event_list.push(Event(PHASE_BEGIN, sim_time+PHASE_LENGTH, e.getVMIndex()+1));
				migration_phase = false;
				phase_num = (phase_num+1) % ssdata->getNumPhases();
				break;

			case MIG_BEGIN:
				event_list.push(Event(MIG_BEGIN, sim_time+PHASE_LENGTH, e.getVMIndex()+1));
				migration_phase = true;
				break;
		}
		event_list.pop();
	}

	cout<<"Simulation completed..."<<endl;
}

void Simulation::stop()
{
	for(unsigned int i=0; i<vmlist.size(); i++)
	{
		cout << "** VM " << i << " stats **" << endl;
		cout << "overall average response time: " << vmlist[i]->getOverallResponseTime() << endl;
		cout << "overall average waiting time: " << vmlist[i]->getOverallWaitingTime() << endl;
		cout << "overall average queue length: " << vmlist[i]->getOverallQueueLength(sim_time) << endl;
		cout << "overall profit: " << vmlist[i]->getOverallProfit(sim_time) << endl;
		cout << endl;
	}

	for(unsigned int i=0; i<vmlist.size(); i++)
		vmlist[i]->stop();
	cout<<sim_time<<endl;
	FILE * stat;
	stat = fopen("results/response_time_phase_log.txt", "w");
	for(int i=0; i<ssdata->getNumPhases(); i++)
	{
		for(int j=0; j<ssdata->getNumVM(); j++)
			fprintf(stat, "%f\t", vmlist[j]->getAvgResponseTime(i));
		fprintf(stat, "\n");
	}
	fclose(stat);
    stat = fopen("results/waiting_time_phase_log.txt", "w");
	for(int i=0; i<ssdata->getNumPhases(); i++)
	{
		for(int j=0; j<ssdata->getNumVM(); j++)
			fprintf(stat, "%f\t", vmlist[j]->getAvgWaitingTime(i));
		fprintf(stat, "\n");
	}
	fclose(stat);
	/* stat = fopen("results/queuelength_phase_log.txt", "w");
	for(int i=0; i<ssdata->getNumPhases(); i++)
	{
		for(int j=0; j<ssdata->getNumVM(); j++)
			fprintf(stat, "%f\t", vmlist[j]->getAvgQLength(i,sim_time));
		fprintf(stat, "\n");
	}
	fclose(stat);*/
	stat = fopen("results/profit_phase_log.txt", "w");
	for(int i=0; i<ssdata->getNumPhases(); i++)
	{
		for(int j=0; j<ssdata->getNumVM(); j++)
			fprintf(stat, "%f\t", vmlist[j]->getAvgProfit(i, sim_time));
		fprintf(stat, "\n");
	}
	fclose(stat);
}

Simulation::~Simulation()
{
	// for(unsigned int i=0; i<vmlist.size(); i++)
	// 	delete vmlist[i];
	delete policy;
}
