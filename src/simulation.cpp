#include "simulation.h"

Simulation::Simulation(SimSData *ssdata)
{
	this->ssdata = ssdata;
	for(int i=0; i<ssdata->getNumVM(); i++)
		vmlist.push_back(new VM(ssdata, i));
	policy = new Mdp(ssdata->getSimData());
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
	cout<<(int)ceil(stop_time/PHASE_LENGTH)<<endl;
	policy->run((int)ceil(stop_time/PHASE_LENGTH));
	policy->printPolicy();

	while(!event_list.empty())
	{
		Event e = event_list.top();
		sim_time = e.getTime();
		float serv_time = -1;

		if(sim_time > stop_time)
			break;

		// e.printDetails();
		switch(e.getEventType())
		{
			case ARRIVAL:
				event_list.push(Event(ARRIVAL, sim_time+vmlist[e.getVMIndex()]->getNextInterArrivalTime(phase_num), e.getVMIndex()));
				if(vmlist[e.getVMIndex()]->isIdle())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(ssdata, policy, phase_num, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->updateOnArrival(sim_time, serv_time, phase_num, migration_phase);
				break;

			case DEPARTURE:
				if(!vmlist[e.getVMIndex()]->isEmptyQueue())
				{
					serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(ssdata, policy, phase_num, sim_time, migration_phase);
					event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));
				}
				vmlist[e.getVMIndex()]->updateOnDeparture(sim_time, serv_time, phase_num, migration_phase);
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
		cout << endl << "** VM " << i << " stats **" << endl;
		cout << "overall average response time: " << vmlist[i]->getOverallResponseTime() << endl;
		cout << "overall average waiting time: " << vmlist[i]->getOverallWaitingTime() << endl;
		cout << "overall average queue length: " << vmlist[i]->getOverallQueueLength(sim_time) << endl;
		cout << "overall profit: " << vmlist[i]->getOverallProfit() << endl;
	}

	for(unsigned int i=0; i<vmlist.size(); i++)
		vmlist[i]->stop();

	ofstream rt_file("results/response_time_phase.txt");
	ofstream wt_file("results/waiting_time_phase.txt");
	ofstream ql_file("results/queuelength_phase.txt");
	ofstream profit_file("results/profit_phase.txt");

	if(!(rt_file.is_open() && wt_file.is_open() && ql_file.is_open() && profit_file.is_open()))
	{
        cout<<"cannot open files, exiting!"<<endl;
        exit(1);
    }

	for(int i=0; i<ssdata->getNumPhases(); i++)
	{
		rt_file << i << "\t";
		for(int j=0; j<ssdata->getNumVM(); j++)
		{
			rt_file << vmlist[j]->getAvgResponseTime(i, 0) << "\t";
			wt_file << vmlist[j]->getAvgWaitingTime(i) << "\t";
			ql_file << vmlist[j]->getAvgQLength(i, sim_time) << "\t";
			profit_file << vmlist[j]->getAvgProfit(i, sim_time) << "\t";
		}
		rt_file << endl;
		rt_file << i+0.7 << "\t";
		for(int j=0; j<ssdata->getNumVM(); j++)
		{
			rt_file << vmlist[j]->getAvgResponseTime(i, 1) << "\t";
		}

		rt_file << endl;
		wt_file << endl;
		ql_file << endl;
		profit_file << endl;
	}

	rt_file.close();
	wt_file.close();
	ql_file.close();
	profit_file.close();

	cout<<endl<<"profit from DSCP algorithm: "<<policy->getOverallProfit()<<endl;
}

Simulation::~Simulation()
{
	for(unsigned int i=0; i<vmlist.size(); i++)
		delete vmlist[i];
	delete policy;
}
