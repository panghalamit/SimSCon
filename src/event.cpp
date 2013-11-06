#include "event.h"

Event :: Event(event_type e, double t, int vmi)
{
	type = e;
	stime = t;
	vm_index = vmi;
}

bool Event :: operator<(const Event *e)
{
	return e->stime < stime;
}

event_type Event :: getEventType()
{
	return type;
} 

double Event :: getTime()
{
	return stime;
}

int Event :: getVMIndex()
{
	return vm_index;
}

Event :: ~Event() {}
