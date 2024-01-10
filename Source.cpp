#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Printable {
public:
    virtual void print() const = 0;
    virtual string serialize() const = 0;
    virtual ~Printable() = default;
};

class Location{
private:
    string locationName;
    int seats;
    int numRows;
    int numZones;
    int* seatsPerRow;

    static int totalEventLocations;

public:

    Location() {
        this->locationName = "";
        this->seats = 0;
        this->numRows = 0;
        this->numZones = 0;
        this->seatsPerRow = nullptr;
        totalEventLocations++;
    }

    Location(string locationName, int seats, int numRows, int numZones, int* seatsPerRow) {
        this->locationName = locationName;
        this->seats = seats;
        this->numRows = numRows;
        this->numZones = numZones;
        this->seatsPerRow = seatsPerRow;
        totalEventLocations++;
    }

    int getSeats() const {
        return this->seats;
    }

    void setSeats(int seats) {
        if (seats > 0) {
            this->seats = seats;
        }
        else {
            cout << "Invalid input for seats \n";
        }
    }

    int getNumRows() const {
        return this->numRows;
    }

    void setNumRows(int rows) {
        this->numRows = rows;
    }

    int getNumZones() const {
        return this->numZones;
    }

    void setNumZones(int zones) {
        this->numZones = zones;
    }

    int* getSeatsPerRow() const {
        int* copy = new int[this->numRows];
        for (int i = 0; i < this->numRows; i++) {
            copy[i] = this->seatsPerRow[i];
        }
        return copy;
    }

    void setSeatsPerRow(int* newSeatsPerRow, int newNumRows) {
        delete[] this->seatsPerRow;
        this->seatsPerRow = new int[newNumRows];
        memcpy(this->seatsPerRow, newSeatsPerRow, sizeof(int) * newNumRows);

        this->numRows = newNumRows;
    }
    static int getTotalEventLocations() {
        return totalEventLocations;
    }

    static void setTotalEventLocations(int TotalEventLocations) {
        totalEventLocations = TotalEventLocations;
    }

    string getLocationName() const {
        return this->locationName;
    }

    void setLocationName(const string location) {
        if (location.length() < 3 || location.length() > 20) {
            throw exception("You entered an invalid string");
        };
        this->locationName = location;
    }

    void printLocationDetails() const {
        cout << "The location name is: " << getLocationName() << endl;
        cout << "The location has: " << getNumZones() << " zones" << endl;
        cout << "The location has: " << getNumRows() << " rows" << endl;
        cout << "The location has: " << getSeats() << " seats" << endl;

        cout << "Seats per row:";
        for (int i = 0; i < this->numRows; i++) {
            cout << " " << this->seatsPerRow[i];
        }
        cout << endl;
    }

    

    friend bool operator!(const Location& l) {
        if (l.locationName != " ") {
            return true;
        }
        else {
            return false;
        }
    }
   

    Location& operator=(const Location& other) {
        if (this != &other) {
            locationName = other.locationName;
            seats = other.seats;
            numRows = other.numRows;
            numZones = other.numZones;

            delete[] seatsPerRow;

            if (other.seatsPerRow != nullptr) {
                seatsPerRow = new int[numRows];
                memcpy(seatsPerRow, other.seatsPerRow, sizeof(int) * numRows);
            }
            else {
                seatsPerRow = nullptr;
            }
        }
        return *this;
    }

    ~Location() {
        delete[] this->seatsPerRow;
    }

};

class Event {
private:
    Location location;

    string eventName;
    string eventDate;
    string eventTime;
 


public:

    bool isValidDateFormat(const std::string& value) {
        if (value.size() != 10 || value[2] != '-' || value[5] != '-') {
            return false;
        }

        for (int i : {0, 1, 3, 4, 6, 7, 8, 9}) {
            if (!std::isdigit(value[i])) {
                return false;
            }
        }

        int d = stoi(value.substr(0, 2));
        int m = stoi(value.substr(3, 2));
        int y = stoi(value.substr(6, 4));

        if (m < 1 || m > 12 || d < 1 || d > 31) {
            return false;
        }

        return true;
    }

    static bool isValidTimeFormat(const string& timeStr) {
        if (timeStr.size() != 5 || timeStr[2] != '-') {
            return false;
        }

        for (int i : {0, 1, 3, 4}) {
            if (!isdigit(timeStr[i])) {
                return false;
            }
        }

        int hour = stoi(timeStr.substr(0, 2));
        int minute = stoi(timeStr.substr(3, 2));

        if (minute < 0 || minute > 59 || hour < 0 || hour > 23) {
            return false;
        }

        return true;
    }



    Event() {
        this->eventName = " ";
        this->eventDate = " ";
        this->eventTime = " ";
    }
    Event(const string& eventName, const string& eventDate, const string& eventLocation) {
        this->eventName = eventName;
        this->eventDate = eventDate;
        this->eventTime = eventLocation;
    }

    string getEventName() const {
        return this->eventName;
    }

    void setEventName(string eventName) {
        this->eventName = eventName;
    }

    string getEventDate() const {
        return this->eventDate;
    }

    void setEventDate(const string& newDate) {
        if (isValidDateFormat(newDate)) {
            this->eventDate = newDate;
        }
        else
            throw exception("The string has an invalid date format.");
    }

    string getEventTime() const {
        return this->eventTime;
    }

    void setEventTime(const string& newTime) {
        if (isValidTimeFormat(newTime)) {
            this->eventTime = newTime;
        }
        else
            throw exception("The string that you wanted to initialize eventTime with has an invalid time format, enter a hh:mm one.");
    }


    void printEventDetails() const {
        cout << "The event is named:" << getEventName() << endl;
        cout << "The event is on the:" << getEventDate() << endl;
        cout << "The event is at:" << getEventTime() << endl;
    }

    

    Event& operator=(const Event& other);
    friend ostream& operator<<(ostream& os, const Event& eventLocation);
    friend istream& operator>>(istream& is, Event& eventLocation);
    int totalEvents = 0;

    ~Event() {
        this->eventName = " ";
    }

};


class Seat {
private:
    int number;
    bool reserved = false;

public:
   
    int getNumber() const {
        return this->number;
    }

    void setNumber(int nr) {
        if (nr < 1) {
            throw exception("Invalid seat number");
        }
        this->number = nr;
    }

    bool isReserved() {
        return reserved;
    }

    void reserve() {
        this->reserved = true;
    }

   
    Seat() : number(1) {}

    Seat(int nr) {
        this->setNumber(nr);
    }

    Seat(const Seat& other) {
        this->setNumber(other.number);
        this->reserved = other.reserved;
    }

    ~Seat() {}

    
    Seat& operator=(const Seat& other) {
        if (this != &other) {
            this->setNumber(other.number);
            this->reserved = other.reserved;
        }
        return *this;
    }

    Seat& operator!() {
         
        this->reserved = false;
        return *this;
    }

    friend std::ostream& operator<<(ostream& os, const Seat& seat) {
        os << std::endl << "Seat Number: " << seat.number << ", Reserved: " << (seat.reserved ? "Yes" : "No");
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Seat& seat) {
        ;
        is >> seat.number;

        int reservedInput;
        
        is >> reservedInput;
        seat.reserved = (reservedInput == 1);

        return is;
    }

    
    void displayDetails() const {
        cout << endl << *this;
    }
};

class Row {
private:
    int nr;
    Seat* seats = nullptr;
    int nrSeats = 0;

public:
    
    int getNumber() const {
        return this->nr;
    }

    void setNumber(int num) {
        if (num < 1) {
            throw exception("Invalid row number");
        }
        this->nr = num;
    }

    int getNumSeats() const {
        return this->nrSeats;
    }

    void setNumSeats(int num) {
        if (num < 5) {
            throw exception("Row must have at least five seats");
        }
        this->nrSeats = num;
    }

    
    Row() : nr(1), nrSeats(1) {
        seats = new Seat[nrSeats];
    }

    Row(int num, int nrSeats) {
        this->setNumber(num);
        this->setNumSeats(nrSeats);
        this->seats = new Seat[this->nrSeats];

        for (int i = 0; i < this->nrSeats; ++i) {
            this->seats[i] = Seat(i + 1);
        }
    }

    Row(const Row& other) : nr(other.nr), nrSeats(other.nrSeats) {
        this->seats = new Seat[this->nrSeats];

        for (int i = 0; i < this->nrSeats; ++i) {
            this->seats[i] = other.seats[i];
        }
    }

    ~Row() {
        delete[] this->seats;
    }

    
    Row& operator=(const Row& other) {
        if (this != &other) {
            delete[] this->seats;
            this->nr = other.nr;
            this->nrSeats = other.nrSeats;
            this->seats = new Seat[this->nrSeats];

            for (int i = 0; i < this->nrSeats; ++i) {
                this->seats[i] = other.seats[i];
            }
        }
        return *this;
    }

    Seat& operator[](int index) {
        if (index < 0 || index >= this->nrSeats) {
            throw out_of_range("Invalid seat ");
        }
        return this->seats[index];
    }

    friend ostream& operator<<(ostream& os, const Row& row) {
        os << endl << " Row " << row.nr ;
        
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Row& row) {
        
        is >> row.nr;

        is >> row.nr;

        row.seats = new Seat[row.nr];

        for (int i = 0; i < row.nr; ++i) {
             is >> row.seats[i];
        }

        return is;
    }

    
    void displayDetails() const {
        cout << endl << " Row: " << this->nr <<endl;
        for (int i = 0; i < this->nr; ++i) {
            cout << this->seats[i];
        }
        
    }

    void reserveRow() {
        
        for (int i = 0; i < this->nr; ++i) {
            this->seats[i].reserve();
        }
    }

    Seat getSeat(int seatNr) const {
        for (int i = 0; i < nrSeats; ++i) {
            if (seats[i].getNumber() == seatNr) {
                return seats[i];
            }
        }

        throw runtime_error("Seat not found");
    }
};


class Ticket:public Printable {
private:
    Event event;
    const int eventId;
    char* ticketType = nullptr;
    int price;
    Seat seatNr;
    Row rowNr;
    static int totalTickets;

    

public:


    Ticket() :eventId(1) {
        this->ticketType = new char[1] {'\0'};
        this->price = 0;
    }

    Ticket(int eventId, char* ticketType, int rowNr, int seatNr, int price) : eventId(eventId)
    {
        this->ticketType = ticketType;
        this->price = 0;

        totalTickets++;

    }


string getTicketType() const {
        return string(this->ticketType);
    }
    void setTicketType(string ticketType) {
        this->ticketType = new char[ticketType.size() + 1];
        strcpy_s(this->ticketType, ticketType.size() + 1, ticketType.c_str());
    }

    int getPrice() const {
        return this->price;
    }

    void setPrice(int price) {
        if (price < 15 || price>500) {
            throw exception("This price is invalid");
        }
        this->price = price;
    }



    static int getTotalTickets();
    void processTicket();
    void validateInput(const string& input);


    friend ostream& operator<<(ostream& os, const Ticket& ticket);
    friend istream& operator>>(istream& is, Ticket& ticket);
    bool operator==(const Ticket& other) const;
    Ticket operator++();
    Ticket operator--(int);

    friend bool operator!(const Ticket& t) {
        if (t.ticketType != nullptr) {
            return true;
        }
        else {
            return false;
        }
    }



    Ticket& operator=(const Ticket& other) {
        if (this != &other) {

            delete[] this->ticketType;

            this->price = other.price;
          

            if (other.ticketType != nullptr) {
                this->ticketType = new char[strlen(other.ticketType) + 1];
                strcpy_s(this->ticketType, strlen(other.ticketType) + 1, other.ticketType);
            }
            else {
                this->ticketType = nullptr;
            }
        }
        return *this;
    }
    void print() const override {
        cout << "Ticket details:\n";
        cout << "The ticket type is:" << getTicketType() << endl;
        cout << "The ticket price is:" << getPrice() << endl;
        cout << "Row: " << rowNr << ", Seat: " << seatNr << endl;
    }

    string serialize() const override {
 
        stringstream ss;
        ss << "Ticket|" << getTicketType() << "|" << getPrice() << "|Row:" << rowNr.getNumber() << "|Seat:" << seatNr.getNumber();
        return ss.str();
    }

    

    Ticket(const Ticket& other) : eventId(other.eventId) {
        this->ticketType = new char[strlen(other.ticketType) + 1];
        strcpy_s(this->ticketType, strlen(other.ticketType) + 1, other.ticketType);
        this->rowNr = other.rowNr;
        this->seatNr = other.seatNr;
        this->price = other.price;
    }

    ~Ticket() {
        if (this->ticketType != nullptr) {
            delete[] this->ticketType;
            this->ticketType = nullptr;
        }
    }
};


class PrintableOperation {
public:
    virtual void execute(const Printable& printable) const = 0;
    virtual ~PrintableOperation() = default;
};

class PrintOperation : public PrintableOperation {
public:
    void execute(const Printable& printable) const override {
        printable.print();
    }
};

class TicketRepository {
public:
    static vector<Ticket> loadTicketsFromBinaryFile(const string& filename);
    static void saveTicketsToBinaryFile(const vector<Ticket>& tickets, const string& filename);
};

void TicketRepository::saveTicketsToBinaryFile(const vector<Ticket>& tickets, const string& filename) {
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening binary file for writing." << endl;
        return;
    }


    ofstream textFile("tickets.txt");
    if (!textFile.is_open()) {
        cerr << "Error opening text file for writing." << endl;
        file.close();
        return;
    }

    for (const auto& ticket : tickets) {
        string serializedTicket = ticket.serialize();
        file.write(serializedTicket.c_str(), serializedTicket.size());
        file.put('\n');


        textFile << serializedTicket << '\n';
    }

    file.close();
    textFile.close();

    cout << "Tickets saved to binary file and text file successfully." << endl;
}


vector<Ticket> TicketRepository::loadTicketsFromBinaryFile(const string& filename) {
    vector<Ticket> tickets;
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening binary file for reading." << endl;
        return tickets;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, '|')) {
            tokens.push_back(token);
        }


        if (tokens.size() == 100) {
            Ticket ticket;
            tickets.push_back(ticket);
        }
    }

    file.close();

    cout << "Tickets loaded from binary file successfully." << endl;

    return tickets;
}


int Ticket::totalTickets = 0;
int Location::totalEventLocations = 0;

int main(int argc, char* argv[]) {


    vector<Ticket> tickets;

    if (argc > 1) {
        tickets = TicketRepository::loadTicketsFromBinaryFile(argv[1]);
    }
    else {

        vector<Ticket> loadedTickets = TicketRepository::loadTicketsFromBinaryFile("tickets.bin");

        tickets.insert(tickets.end(), loadedTickets.begin(), loadedTickets.end());



        int choice;

        do {
            cout << "1. Add Ticket\n";
            cout << "2. Display Tickets\n";
            cout << "3. Save Tickets to File\n";
            cout << "4. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {

                cout << "Adding a new ticket..." << endl;
                string ticketType;
                int price, rowNo, seatNo;

                cout << "Enther the ticket type:";
                cin >> ticketType;

                cout << "Enter the ticket price:";
                cin >> price;

                cout << "Enter the row number:";
                cin >> rowNo;

                cout << "Enter the seat number:";
                cin >> seatNo;

                try {
                    Ticket newTicket(1, const_cast<char*>(ticketType.c_str()), rowNo, seatNo, price);
                    tickets.push_back(newTicket);
                    cout << "New ticket added successfully!" << endl;
                }
                catch (const exception& e) {
                    cerr << "Exception caught: " << e.what() << endl;
                }

                break;
            }

            case 2: {
                PrintOperation printOperation;
                for (const auto& ticket : tickets) {
                    printOperation.execute(ticket);
                }
                break;
            }
            case 3: {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                TicketRepository::saveTicketsToBinaryFile(tickets, filename);
                break;
            }
            case 4: {
                cout << "Exiting program.\n";
                break;
            }

            default:
                cout << "Invalid choice. Try again.\n";

                return 0;
            }
        } while (choice != 4);

    }

}