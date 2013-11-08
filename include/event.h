#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

typedef enum{ARRIVAL=0, DEPARTURE} EventType;

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
