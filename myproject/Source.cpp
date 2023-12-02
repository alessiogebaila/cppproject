 #include <iostream>;
 #include <string>;
 using namespace std;




    class Events {
    private:
        int maxSeats;
        int numRows;
        int numZones;
        int seatsPerRow;

        static int totalEventLocations;

    public:
        char* charVector;
        int* numericVector;

        Events();
        Events(int maxSeats, int numRows, int numZones, int seatsPerRow);
        Events(const Events& other);
        ~Events();

     
        int getMaxSeats() {
            return this->maxSeats;
        }
        void setMaxSeats(int seats);
        int getNumRows() {
            return this->numRows;
        }
        void setNumRows(int rows);
        int getNumZones() {
            return this->numZones;
        }
        void setNumZones(int zones);
        int getSeatsPerRow() {
            return this->seatsPerRow;
        }


        void setSeatsPerRow(int seats);

 

        Events& operator=(const Events& other);
        friend ostream& operator<<(ostream& os, const Events& eventLocation);
        friend istream& operator>>(istream& is, Events& eventLocation);
    };
    int totalEvents = 0;

    Events() {
        maxSeats = 0;
        numRows = 0;
        numZones = 0;
        seatsPerRow = 0;
        charVector = new vector char();
        numericVector = new vector int();
        totalEvents++;
    }

    Events(int maxSeats, int numRows, int numZones, int seatsPerRow) {
        this->maxSeats = maxSeats;
        this->numRows = numRows;
        this->numZones = numZones;
        this->seatsPerRow = seatsPerRow;
        charVector = new vector char();
        numericVector = new vector int();
        totalEventLocations++;
    }

    Events(const Events& other) {
        maxSeats = this->maxSeats;
        numRows = this->numRows;
        numZones = this->numZones;
        seatsPerRow = this->seatsPerRow;
        charVector = new vector char(*other.charVector);
        numericVector = new vector int(*other.numericVector);
        totalEventLocations++;
    }

    ~Events() {
        delete charVector;
        delete numericVector;
        totalEvents--;
    }

    int Events::getMaxSeats() const {
        return maxSeats;
    }

    void Events::setMaxSeats(int seats) {
        if (seats > 0) {
            maxSeats = seats;
        }
        else {
            std::cerr << "Invalid input for maxSeats.\n";
        }
    }


    // Generic methods
    void Events::processEvents() {
        // Implement your processing logic here
    }

    void Events::displayEventsDetails() const {
        std::cout << "Location Details:\n";
        std::cout << "Max Seats: " << maxSeats << "\n";
        // Display other details
    }

    ostream& operator<<(ostream& os, const Events& eventLocation) {
        os << "Max Seats: " << eventLocation.maxSeats << "\n";
        // Output other details
        return os;
    }

    istream& operator>>(istream& is, Events& eventLocation) {
        // Input logic for EventLocation
        return is;
    }


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