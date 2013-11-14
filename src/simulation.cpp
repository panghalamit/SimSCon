#include "simulation.h"

Simulation :: Simulation(SimData *sdata)
{
	s_data = sdata;
	for(int i=0; i<sdata->getNumVM(); i++)
		vmlist.push_back(new VM(sdata->getArrivalRate(i), sdata->getFixedServiceRate(i), i));
	policy = new Khanna(sdata);
}

void Simulation :: start()
{
	migration_phase = false;
	event_list.push(Event(PHASE_BEGIN, 0, 0));
	event_list.push(Event(MIG_BEGIN, PHASE_LENGTH*(1-MIGRATIONDURATION), 0));
	for(unsigned int i=0; i<vmlist.size(); i++)
		event_list.push(Event(ARRIVAL, vmlist[i]->getNextInterArrivalTime(), vmlist[i]->getIndex()));
	cout<<"Yay!! Simulation started..."<<endl;
}

void Simulation :: run(double stop_time)
{
	while(!event_list.empty())
	{
		Event e = event_list.top();
		sim_time = e.getTime();
		float serv_time = -1;

		if(sim_time > stop_time)
			break;

		e.printDetails();
		switch(e.getEventType())
		{
			case ARRIVAL:
				event_list.push(Event(ARRIVAL, sim_time+vmlist[e.getVMIndex()]->getNextInterArrivalTime(), e.getVMIndex()));
				if(vmlist[e.getVMIndex()]->isIdle())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(s_data, policy, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->update_on_arrival(sim_time, serv_time);
				break;

			case DEPARTURE:
				if(!vmlist[e.getVMIndex()]->isEmptyQueue())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(s_data, policy, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->update_on_departure(sim_time, serv_time);
				break;

			case PHASE_BEGIN:
				event_list.push(Event(PHASE_BEGIN, sim_time+PHASE_LENGTH, e.getVMIndex()+1));
				migration_phase = false;
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

void Simulation :: stop ()
{
	// dumping statistics
	ofstream stat_file("results/stats.txt");
	if(stat_file.is_open())
	{
		for(unsigned int i=0; i<vmlist.size(); i++)
		{
			stat_file << "** VM " << i << " stats **" << endl;
			stat_file << "average response time: " << vmlist[i]->getAvgResponseTime() << endl;
			stat_file << "average waiting time: " << vmlist[i]->getAvgWaitingTime() << endl;
			stat_file << "average queue length: " << vmlist[i]->getAvgQLength(sim_time) << endl;
			stat_file << endl;
		}
		stat_file.close();
	} else
	{
		cout<<"error occured! unable to open stats.txt!"<<endl;
		exit(1);
	}

	for(unsigned int i=0; i<vmlist.size(); i++)
	{
		vmlist[i]->stop();
		delete vmlist[i];
	}
	delete policy;
}
