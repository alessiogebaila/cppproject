#define _CRT_SECURE_NO_WARNINGS
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
    
     bool isValidDateFormat(const std::string& value) {
         if (value.size() != 10 || value[2] != '-' || value[5] != '-') {
             return false;
         }

         for (int i : {0, 1, 3, 4, 6, 7, 8, 9}) {
             if (!std::isdigit(value[i])) {
                 return false;
             }
         }

         int d = std::stoi(value.substr(0, 2));
         int m = std::stoi(value.substr(3, 2));
         int y = std::stoi(value.substr(6, 4));

         if (m < 1 || m > 12 || d < 1 || d > 31) {
             return false;
         }

         return true;
     }

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

     void setEventDate(const string& newDate) {
         if (isValidDateFormat(newDate)) {
             this->eventDate = newDate;
         }
         else
             throw exception("The string has an invalid date format.");
     }

     string getEventLocation() {
         return this->eventLocation;
     }

     void setEventLocation(string eventLocation) {
         this->eventLocation = eventLocation;
     }

     void setLocationName(const string location) {
         if (location.length() < 3 || location.length() > 20) {
             throw exception("You entered an invalid string");
         };
         this->eventLocation = location;
     }

     void printEventDetails() {
         cout << "The event is named:" << getEventName() << endl;
         cout << "The event is on the:" << getEventDate() << endl;
         cout << "The event is at:" << getEventLocation() << endl;
     }

     Event& operator=(const Event& other);
     friend ostream& operator<<(ostream& os, const Event& eventLocation);
     friend istream& operator>>(istream& is, Event& eventLocation);
     int totalEvents = 0;

     friend bool operator!(const Event& e) {
         if (e.eventLocation !=" ")
             return true;
         else
             return false;
     }


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
         totalEventLocations++;
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
         cout << "The location has:" << getNumZones() << " zones" << endl;
         cout << "The location has:" << getNumRows() << "rows" << endl;
         cout << "The location has:" << getSeats() << "seats" << endl;
         cout << "Every row has:" << getSeatsPerRow() << "seats" << endl;
     }

     friend bool operator!(const Location& l) {
         if (l.locationName != " ") {
             return true;
         }
         else {
             return false;
         }
     }
     void displayLocationDetails() {
         cout << "Location Details:\n";
         cout << "Max Seats: " << this->seats << "\n";

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
                 std::memcpy(seatsPerRow, other.seatsPerRow, sizeof(int) * numRows);
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

    int getRowNo() {
        return this->rowNo;
    }
    
    void setRowNo(int rowNo) {
        if (rowNo < 1 || rowNo>10) {
            throw exception("This row does not exist!");
        }
        this->rowNo = rowNo;
    }

    int getSeatNo() {
        return this->seatNo;
    }

    void setSeatNo(int seatNo) {
        if (seatNo < 1 || seatNo>15) {
            throw exception("This seat does not exist!");
        }
        this->seatNo = seatNo;
    }

    int getPrice() {
        return this->price;
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
            this->rowNo = other.rowNo;
            this->seatNo = other.seatNo;

           
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

    void printTicketDetails() {
        cout << "The ticket id is: " << getTicketId() << endl;
        cout << "The ticket type is:" << getTicketType() << endl;
        cout << "The ticket price is:" << getPrice() << endl;
        cout << "The row number is:" << getRowNo() << endl;
        cout << "The seat number is:" << getSeatNo() << endl;
    }

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