#include "event.h"

Event :: Event(EventType e, double t, int vmi)
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

double Event :: getTime()
{
	return stime;
}

void Event :: printDetails()
{
	switch(etype)
	{
		case ARRIVAL:
			cout<<"ARRIVAL: "<<stime<<endl;
			break;
		case DEPARTURE:
			cout<<"DEPARTURE: "<<stime<<endl;
			break;
	}
}
