#include "event.h"

Event :: Event(event_type e, double t)
{
	type = e;
	stime = t;
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

Event :: ~Event() {}
