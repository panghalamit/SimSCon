#include "event.h"

Event :: Event(EventType e, float t, int vmi)
{
	etype = e;
	stime = t;
	vm_index = vmi;
}

bool Event :: operator<(const Event e) const
{
	return e.stime < stime;
}

EventType Event :: getEventType()
{
	return etype;
}

float Event :: getTime()
{
	return stime;
}

int Event :: getVMIndex()
{
	return vm_index;
}

void Event :: printDetails()
{
	switch(etype)
	{
		case ARRIVAL:
			cout<<"ARRIVAL on VM"<<vm_index<<": "<<stime<<endl;
			break;
		case DEPARTURE:
			cout<<"DEPARTURE on VM"<<vm_index<<": "<<stime<<endl;
			break;
		case PHASE_BEGIN:
			cout<<endl<<"** PHASE "<<vm_index<<" BEGINS **"<<endl;
			break;
		case MIG_BEGIN:
			cout<<"** MIGRATION for PHASE "<<vm_index<<" BEGINS**"<<endl;
			break;
	}
}
