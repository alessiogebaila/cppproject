 #include <iostream>;
 #include <string>;
 using namespace std;



class Events
{
private:
	const int events_id;
	static int events_nr;
	string events_name;





	int tickets_available;
	double tickets_prices;

	//getters
	std::string* getEvents()
	{
		std::string* copy = new std::string[this->events_nr];
		for (int i = 0; i < this->events_nr; i++)
		{
			copy[i] = this->events_nr[i];
		}
		return copy;
		return events_nr;
	}
	int get()
	{
		return this->events_nr;
	}

	tickets_available getTicketsAvailable()
	{
		return this->tickets_prices;
	}
public:
	Events()

    {
		this->events_name = new char[strlen("match name") + 1];
		strcpy_s(this->events_name, strlen("match name") + 1, "match name");

		this->events_id = other;
	}

	Events(const char* _name, string _date, string _time) {
		if (events_name != nullptr && strlen(events_name) > 1)
		{
			this->events_name = new char[strlen(events_name) + 1];
			strcpy_s(this->events_name, strlen(name) + 1, name);
		}
		else
		{
			cout << "Enter a valid event name:";

		}
		
	}
};


class Tickets
{
private:
	const int ticket_id;
	Events* p_EventsList;
	string events_name;
	string events_location;
public:
	Tickets();
	Tickets(string my_name_event, string my_location_event);
	Tickets(const Tickets& my_tickets);
	~Tickets();
	Tickets& operator=(const Tickets& my_tickets);
	void Init(Events* p_my_events, int array_size);
	void Run();
	void DisplayMenu();
	void ViewEvents();
	Events* SearchEvents();
	Events* FindEvents(string cauta_eveniment);
	void PurchaseTicket();

	
	friend ostream& operator<<(ostream& out, Tickets& my_tickets);
	friend istream& operator>>(istream& in, Tickets& my_tickets);


	Events& operator[](int index);


	Tickets& operator>=(double my_ticket_price);

};