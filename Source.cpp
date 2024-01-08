#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Printable {
public:
    virtual void print() const = 0;
};


 class Event:public Printable {
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

         int d = stoi(value.substr(0, 2));
         int m = stoi(value.substr(3, 2));
         int y = stoi(value.substr(6, 4));

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

     string getEventName() const{
         return this->eventName;
     }

     void setEventName(string eventName) {
         this->eventName = eventName;
     }

     string getEventDate() const{
         return this->eventDate;
     }

     void setEventDate(const string& newDate) {
         if (isValidDateFormat(newDate)) {
             this->eventDate = newDate;
         }
         else
             throw exception("The string has an invalid date format.");
     }

     string getEventLocation() const{
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

     void printEventDetails() const {
         cout << "The event is named:" << getEventName() << endl;
         cout << "The event is on the:" << getEventDate() << endl;
         cout << "The event is at:" << getEventLocation() << endl;
     }

     void print() const override {
         printEventDetails();
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


 class Location: public Printable {
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

     int getNumRows() const{
         return this->numRows;
     }

     void setNumRows(int rows) {
         this->numRows = numRows;
     }

     int getNumZones() const {
         return this->numZones;
     }

     void setNumZones(int zones) {
         this->numZones = numZones;
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
     static int getTotalEventLocations()  {
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
         cout << "The location has:" << getNumZones() << " zones" << endl;
         cout << "The location has:" << getNumRows() << "rows" << endl;
         cout << "The location has:" << getSeats() << "seats" << endl;
         cout << "Every row has:" << getSeatsPerRow() << "seats" << endl;
     }

     void print() const override {
         printLocationDetails();
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


class Ticket:public Printable {
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

    void print() {
        printTicketDetails();
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
  };

  
  class PrintOperation : public PrintableOperation {
  public:
      void execute(const Printable& printable) const override {
          printable.print();
      }
  };

  

int main(int argc, char* argv[]) {
    vector<Ticket> tickets;

    if (argc == 2) {
      tickets = loadTicketsFromFile(argv[1]);
    }

    cout << "Hello, World!" << endl;

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
            Ticket newTicket;
            tickets.push_back(newTicket);
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
            saveTicketsToFile(tickets, filename);
            break;
        }
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
}