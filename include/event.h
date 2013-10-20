
typedef enum{ARRIVAL=0, DEPARTURE} event_type; 

class Event
{
	private:
		event_type type;
		double time;
	public:
		Event(event_type e, double t);
		double getTime();
		event_type getEventType();
		~Event();
};
