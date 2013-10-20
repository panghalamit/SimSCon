#include "event.h"

Event :: Event(event_type e, double t)
{
	this.type = e;
	this.time = t;
}

event_type Event :: getEventType()
{
	return type;
} 

double Event :: getTime()
{
	return time;
}

Event :: ~Event() {}
