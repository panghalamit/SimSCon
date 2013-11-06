
typedef enum{ARRIVAL=0, DEPARTURE} event_type; 

class Event
{
	private:
		event_type type;
		double stime;
		int vm_index;
	public:
		Event(event_type e, double t, int vmi);
		bool operator<(const Event * e);
		double getTime();
		event_type getEventType();
		int getVMIndex();
		~Event();
};

