#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

typedef enum{ARRIVAL=0, DEPARTURE} EventType; 

class Event
{
	EventType etype;
	double stime;
	int vm_index;
  public:
	Event(EventType, double, int);
	bool operator<(const Event) const;
	double getTime();
	EventType getEventType();
	void printDetails();
};

#endif
