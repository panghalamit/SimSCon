#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

typedef enum{PHASE_BEGIN=0, MIG_BEGIN, ARRIVAL, DEPARTURE} EventType;

class Event
{
	EventType etype;
	float stime;
	int vm_index;

  public:
	Event(EventType, float, int);
	bool operator<(const Event) const;
	float getTime();
	int getVMIndex();
	EventType getEventType();
	void printDetails();
};

#endif
