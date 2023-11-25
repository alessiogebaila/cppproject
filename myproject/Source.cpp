#include <iostream>;
#include <string>;
using namespace std;



class Event
{
private:
	const int event_id;
	static int event_nr;
	string event_name;
	int tickets_available;
	double ticket_prices;

public:
	Event();
	Event(string event_name, int my_tickets, double ticket_prices);
	Event(const Event& my_event);
	~Event();
	Event& operator=(const Event& my_event);

	char* get_event_name();
	int get_tickets_available();
	double get_ticket_prices();
	void set_event_name(string new_event_name);
	void set_tickets_available(int new_tickets_available);
	void set_ticket_prices(double new_ticket_prices);
	static int get_events_number();
	static void set_events_number(int new_events_number);

	double BuyTicket(int new_tickets_available);
};