 #include <iostream>
 #include <string>
 #include <vector>
 using namespace std;


 class Event {
 private:
     string eventName;
     string eventDate;
     string eventLocation;
     

 public:
     Event() {
         this->eventName =" ";
         this->eventDate = " ";
         this->eventLocation = " ";
     }
     Event(const string& eventName, const string& eventDate, const string& eventLocation) {
         this->eventName = eventName;
         this->eventDate = eventDate;
         this->eventLocation = eventLocation;
     }

     string getEventName() {
         return this->eventName;
     }

     void setEventName(string eventName) {
         this->eventName = eventName;
     }

     string getEventDate() {
         return this->eventDate;
     }

     void setEventDate(string eventDate) {
         this->eventDate = eventDate;
     }

     string getEventLocation() {
         return this->eventLocation;
     }

     void setEventLocation(string eventLocation) {
         this->eventLocation = eventLocation;
     }

     Event& operator=(const Event& other);
     friend ostream& operator<<(ostream& os, const Event& eventLocation);
     friend istream& operator>>(istream& is, Event& eventLocation);
     int totalEvents = 0;


     ~Event() {
         this->eventName=" ";
     }

 };


 class Location {
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
         this->seatsPerRow = 0;
         totalEvents++;
     }

     Location(string locationName,int seats, int numRows, int numZones, int* seatsPerRow) {
         this->locationName = locationName;
         this->seats = seats;
         this->numRows = numRows;
         this->numZones = numZones;
         this->seatsPerRow = seatsPerRow;
         totalEventLocations++;
     }

     int getSeats() {
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

     int getNumRows() {
         return this->numRows;
     }

     void setNumRows(int rows) {
         this->numRows = numRows;
     }

     int getNumZones() {
         return this->numZones;
     }

     void setNumZones(int zones) {
         this->numZones = numZones;
     }

     int* getSeatsPerRow() {
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

     string getLocationName() {
         return this->locationName;
     }

     void setLocationName(const string location) {
         if (location.length() < 3 || location.length() > 20) {
             throw exception("You entered an invalid string");
         };
         this->locationName = location;
     }

     void printLocationDetails() {
         cout << "The location name is: " << getLocationName() << endl;
         cout << "The location has " << getNumZones() << " zones: ";
     }



     Location& operator=(const Location& other);
     friend ostream& operator<<(ostream& os, const Location& eventLocation);
     friend istream& operator>>(istream& is, Location& eventLocation);
     int totalEvents = 0;





     Location(const Location& other) {
         seats = this->seats;
         numRows = this->numRows;
         numZones = this->numZones;
         seatsPerRow = this->seatsPerRow;
         totalEventLocations++;
     }

     ~Location() {
        delete[] this->seatsPerRow;
     }

    // int Location::getSeats() const {
       //  return this->Seats;
    // }

    // void Location::setSeats(int seats) {
       //  if (seats > 0) {
         ///    this->Seats = seats;
       //  }
        // else {
           //  cout << "Invalid input for seats \n";
       //  }
    // }


     // Generic methods
     //void Location::processLocation() {
         // Implement your processing logic here
     //}

     //void Location::displayLocationDetails() const {
       //  std::cout << "Location Details:\n";
         //std::cout << "Max Seats: " << Seats << "\n";
         // Display other details
     //}

     //ostream& operator<<(ostream& os, const Location& eventLocation) {
       //  os << "Max Seats: " << eventLocation.maxSeats << "\n";
         // Output other details
         //return os;
     //}

     //istream& operator>>(istream& is, Location& eventLocation) {
         // Input logic for EventLocation
       //  return is;
     //}
 };
class Ticket {
private:
    const int eventId;
    char* ticketType=nullptr;
    int price;
    int seatNo;
    int rowNo;
    static int totalTickets;

public:

    Ticket() :eventId(1) {
        this->ticketType=nullptr;
        this->rowNo = 0;
        this->seatNo = 0;
        this->price = 0;

    }

    Ticket(int eventId, char* ticketType, int rowNo, int seatNo, int price) : eventId(eventId)
    {
        this->ticketType = ticketType;
        this->rowNo = rowNo;
        this->seatNo = seatNo;
        this->price = 0;

        totalTickets++;

    }

    Ticket(const string& eventId, const string& ticketType);
    

    string getTicketType() {
        return string(this->ticketType);
    }
    void setTicketType(string ticketType) {
        this->ticketType = new char[ticketType.size() + 1];
        strcpy_s(this->ticketType, ticketType.size() + 1, ticketType.c_str());
    }

    void setRowNo(int rowNo) {
        if (rowNo < 1 || rowNo>10) {
            throw exception("This row does not exist!");
        }
        this->rowNo = rowNo;
    }

    void setSeatNo(int seatNo) {
        if (seatNo < 1 || seatNo>15) {
            throw exception("This seat does not exist!");
        }
        this->seatNo = seatNo;
    }

    void setPrice(int price) {
        if (price < 15 || price>500) {
            throw exception("This price is invalid");
        }
        this->price = price;
    }


    const string& getTicketId() const;
    void generateTicketId();

    static int getTotalTickets();
    void processTicket();
    void validateInput(const string& input);


    friend ostream& operator<<(ostream& os, const Ticket& ticket);
    friend istream& operator>>(istream& is, Ticket& ticket);
    bool operator==(const Ticket& other) const;
    Ticket operator++();
    Ticket operator--(int);

    ~Ticket() {
        if (this->ticketType != nullptr) {
            delete[] this->ticketType;
            this->ticketType = nullptr;
        }
    }
  };

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}