
typedef enum{ARRIVAL=0, DEPARTURE} event_type; 

class Event
{
	private:
		event_type type;
		double stime;
	public:
		Event(event_type e, double t);
		bool operator<(const Event * e);
		double getTime();
		event_type getEventType();
		~Event();
};

