#include <iostream>
#include <fstream>
using namespace std;

class PassengerNode
{
private:
    string name;
    string ID;
    string flightCode;
    string contactNumber;
    PassengerNode *nextNode;
    PassengerNode *prevNode;

public:
    PassengerNode()
    {
        name = "";
        ID = "";
        flightCode = "";
        contactNumber = "";
        nextNode = nullptr;
        prevNode = nullptr;
    }

    PassengerNode(string n = "", string id = "", string fC = "", string cont = "")
    {
        name = n;
        ID = id;
        flightCode = fC;
        contactNumber = cont;
        nextNode = nullptr;
        prevNode = nullptr;
    }
    string getname() { return name; }
    string getID() { return ID; }
    string getflightCode() { return flightCode; }
    string getcontactNumber() { return contactNumber; }
    void setNextNode(PassengerNode *nextNode) { this->nextNode = nextNode; }
    void setPrevNode(PassengerNode *prevNode) { this->prevNode = prevNode; }
    PassengerNode *getNextNode() { return nextNode; }
    PassengerNode *getPrevNode() { return prevNode; }
};

class FlightNode
{
private:
    string origin;
    string destination;
    string departure;
    string arrival;
    string flighCode;
    string price;
    string totalSeats;
    FlightNode *nextNode;
    FlightNode *prevNode;

public:
    FlightNode()
    {
        origin = "";
        destination = "";
        departure = "";
        arrival = "";
        flighCode = "";
        price = "";
        totalSeats = "";
        nextNode = nullptr;
        prevNode = nullptr;
    }

    FlightNode(string o = "", string dest = "", string dep = "", string a = "", string f = "", string ts = "", string p = "")
    {
        origin = o;
        destination = dest;
        departure = dep;
        arrival = a;
        flighCode = f;
        price = p;
        totalSeats = ts;
        nextNode = nullptr;
        prevNode = nullptr;
    }

    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDeparture() { return departure; }
    string getArrival() { return arrival; }
    string getFlighCode() { return flighCode; }
    string getPrice() { return price; }
    string getTotalSeats() { return totalSeats; }
    void setNextNode(FlightNode *nextNode) { this->nextNode = nextNode; }
    void setPrevNode(FlightNode *prevNode) { this->prevNode = prevNode; }
    FlightNode *getNextNode() { return nextNode; }
    FlightNode *getPrevNode() { return prevNode; }
};

class EmployeeNode
{
private:
    string name;
    string ID;
    string designation;
    EmployeeNode *nextNode;
    EmployeeNode *prevNode;

public:
    EmployeeNode() { name = "", ID = "", designation = "", nextNode = nullptr, prevNode = nullptr; }
    EmployeeNode(string n = "", string id = "", string d = "") { name = n, ID = id, designation = d, nextNode = nullptr, prevNode = nullptr; }
    string getName() { return name; }
    string getID() { return ID; }
    string getDesignation() { return designation; }
    void setNextNode(EmployeeNode *nextNode) { this->nextNode = nextNode; }
    void setPrevNode(EmployeeNode *prevNode) { this->prevNode = prevNode; }
    EmployeeNode *getNextNode() { return nextNode; }
    EmployeeNode *getPrevNode() { return prevNode; }
};

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Backend class start) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// class Memory
// {
// public:
//     PassengerNode PassengerHeadNode;

//     void importData();
// };
// void Memory::importData()
// {
//     // ifstream file;
//     // file.open()
// }
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Backend class end) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class AirportManagementSystem
{
private:
    PassengerNode *PassengerHeadNode;
    PassengerNode *PassengerCurrentNode;
    int passengerSize;

    FlightNode *FlightHeadNode;
    FlightNode *FlightCurrentNode;
    int flightSize;

    EmployeeNode *EmployeeHeadNode;
    EmployeeNode *EmployeeCurrentNode;
    int employeeSize;

public:
    AirportManagementSystem()
    {
        passengerSize = 0, PassengerHeadNode = nullptr, PassengerCurrentNode = nullptr;
        flightSize = 0, FlightHeadNode = nullptr, FlightCurrentNode = nullptr;
        employeeSize = 0, EmployeeHeadNode = nullptr, EmployeeCurrentNode = nullptr;
    }
    // functions for system memory
    void ImportData();
    void ArrayToDoubly(string *array);

    // functions for employee
    void pushEmployee(string n, string id, string d);
    void popEmployee(string id);
    void showEmployeeByID(string id);
    void showALLEmployees();

    // functions for flight
    void pushFlight(string Origin, string Destination, string Departure, string Arrival, string FlightCode, string TotalSeats, string Price);
    void popFlight(string flightCode);
    void showFlightByFlightCode(string flightCode);
    void showAllFlight();
    void showFlightByOrigin(string Origin);
    void showFlightByDestination(string destinition);

    // functions for passenger
    void printUniqueOrigins();
    bool checkOriginAvailiblity(string o);
    void printUniqueDestinations();
    bool checkDestinationAvailiblity(string d);
    void getFlight(string o, string d);
    bool checkFlightCode(string o, string d, string fC);
    void bookFlight_pushPassenger(string name, string id, string flightCode, string contact);
    void cancelBooking_popPassenger(string id);
    void showAllPassengers();
    void showPassengerByID(string id);
    void showAllPassengerOfFlight(string flightCode);
};

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( System Memory functions start) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void AirportManagementSystem::ImportData()
{
    ifstream Storage;
    Storage.open("Storage.txt", ios::app); // opening in append mode just for personal satisfaction
    while (Storage.eof() == 0)
    {
        string ToupleFieldsArray[8] = {""}; // initializing array with empty string at every index

        string StorageTouple = "";
        getline(Storage, StorageTouple);
        if (StorageTouple == "") // if it is empty row you will skip to next row
        {
            continue;
        }
        int cols = 0;
        string StorageField = "";
        for (int j = 0; j < StorageTouple.length(); j++) // breaking row that we input into different values
        {
            if (StorageTouple[j] != ',') // if , does not occur keep adding character in temp_row
            {
                StorageField += StorageTouple[j];
            }
            else // if , occur save temp_row into 2D array
            {
                ToupleFieldsArray[cols] = StorageField;
                cols++;
                StorageField = "";

                if (cols == 8)
                {
                    ArrayToDoubly(ToupleFieldsArray);
                }
            }
        }
    }
    Storage.close();
}

void AirportManagementSystem::ArrayToDoubly(string *array)
{
    if (array[0] == "employee")
    {
        pushEmployee(array[1], array[2], array[3]);
    }
    else if (array[0] == "passenger")
    {
        bookFlight_pushPassenger(array[1], array[2], array[3], array[4]);
    }
    else if (array[0] == "flight")
    {
        pushFlight(array[1], array[2], array[3], array[4], array[5], array[6], array[7]);
    }
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( System Memory functions end) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Employee functions start) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void AirportManagementSystem::pushEmployee(string n, string id, string d)
{
    EmployeeNode *newNode = new EmployeeNode(n, id, d);
    if (EmployeeHeadNode == nullptr)
    {
        EmployeeHeadNode = newNode;
    }
    else
    {
        EmployeeCurrentNode = EmployeeHeadNode;
        while (EmployeeCurrentNode->getNextNode() != nullptr)
        {
            EmployeeCurrentNode = EmployeeCurrentNode->getNextNode();
        }
        EmployeeCurrentNode->setNextNode(newNode);
        newNode->setPrevNode(EmployeeCurrentNode);
    }
    employeeSize++;
    cout << "Employee Successfully Registered" << endl;
}

// void AirportManagementSystem::popEmployee(string id)
// {
// }

// void AirportManagementSystem::showEmployeeByID(string id)
// {
// }

void AirportManagementSystem::showALLEmployees()
{
    cout << "Total Employee: " << employeeSize << endl;
    if (EmployeeHeadNode == nullptr)
    {
        cout << "No Employee record availible" << endl;
    }
    else
    {
        EmployeeCurrentNode = EmployeeHeadNode;
        while (EmployeeCurrentNode != nullptr)
        {
            cout << "Employee Name: " << EmployeeCurrentNode->getName() << endl;
            cout << "Employee ID: " << EmployeeCurrentNode->getID() << endl;
            cout << "Employee Designatione: " << EmployeeCurrentNode->getDesignation() << endl
                 << endl;
            EmployeeCurrentNode = EmployeeCurrentNode->getNextNode();
        }
    }
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Employee functions end) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// +++++++++++++++++++++++++++++++++++++ ( Flight functions start) +++++++++++++++++++++++++++++++++++++
void AirportManagementSystem::pushFlight(string Origin, string Destination, string Departure, string Arrival, string FlightCode, string TotalSeats, string Price)
{
    FlightNode *newNode = new FlightNode(Origin, Destination, Departure, Arrival, FlightCode, TotalSeats, Price);
    if (FlightHeadNode == nullptr)
    {
        FlightHeadNode = newNode;
    }
    else
    {
        FlightCurrentNode = FlightHeadNode;
        while (FlightCurrentNode->getNextNode() != nullptr)
        {
            FlightCurrentNode = FlightCurrentNode->getNextNode();
        }
        FlightCurrentNode->setNextNode(newNode);
        newNode->setPrevNode(FlightCurrentNode);
    }
    flightSize++;
    cout << "Flight Successfully Added" << endl;
}

// void AirportManagementSystem::popFlight(string flightCode)
// {
// }

void AirportManagementSystem::showFlightByFlightCode(string flightCode)
{
}

void AirportManagementSystem::showAllFlight()
{
    cout << "Total Flights: " << flightSize << endl;
    if (FlightHeadNode == nullptr)
    {
        cout << "No Flight record availible" << endl;
    }
    else
    {
        FlightCurrentNode = FlightHeadNode;
        while (FlightCurrentNode != nullptr)
        {
            cout << "Flight origin: " << FlightCurrentNode->getOrigin() << endl;
            cout << "Flight destination: " << FlightCurrentNode->getDestination() << endl;
            cout << "Flight departure: " << FlightCurrentNode->getDeparture() << endl;
            cout << "Flight arrival: " << FlightCurrentNode->getArrival() << endl;
            cout << "Flight flighCode: " << FlightCurrentNode->getFlighCode() << endl;
            cout << "Flight price: " << FlightCurrentNode->getPrice() << endl;
            cout << "Flight totalSeats: " << FlightCurrentNode->getTotalSeats() << endl
                 << endl;
            FlightCurrentNode = FlightCurrentNode->getNextNode();
        }
    }
}

// void AirportManagementSystem::showFlightByOrigin(string Origin)
// {
// }

// void AirportManagementSystem::showFlightByDestination(string destinition)
// {
// }

// void AirportManagementSystem::printUniqueOrigins()
// {
// }

// bool AirportManagementSystem::checkOriginAvailiblity(string o)
// {
// }
// +++++++++++++++++++++++++++++++++++++ ( Flight functions end) +++++++++++++++++++++++++++++++++++++

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Passenger functions start) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// void AirportManagementSystem::printUniqueDestinations()
// {
// }

// bool AirportManagementSystem::checkDestinationAvailiblity(string d)
// {
// }

// void AirportManagementSystem::getFlight(string o, string d)
// {
// }

// bool AirportManagementSystem::checkFlightCode(string o, string d, string fC)
// {
// }

void AirportManagementSystem::bookFlight_pushPassenger(string name, string id, string flightCode, string contact)
{
    PassengerNode *newNode = new PassengerNode(name, id, flightCode, contact);
    if (PassengerHeadNode == nullptr)
    {
        PassengerHeadNode = newNode;
    }
    else
    {
        PassengerCurrentNode = PassengerHeadNode;
        while (PassengerCurrentNode->getNextNode() != nullptr)
        {
            PassengerCurrentNode = PassengerCurrentNode->getNextNode();
        }
        PassengerCurrentNode->setNextNode(newNode);
        newNode->setPrevNode(PassengerCurrentNode);
    }
    passengerSize++;
    cout << "Flight Successfully Added" << endl;
}

// void AirportManagementSystem::cancelBooking_popPassenger(string id)
// {
// }
void AirportManagementSystem::showAllPassengers()
{
    cout << "Total Passengers: " << passengerSize << endl;
    if (PassengerHeadNode == nullptr)
    {
        cout << "No Passenger record availible" << endl;
    }
    else
    {
        PassengerCurrentNode = PassengerHeadNode;
        while (PassengerCurrentNode != nullptr)
        {
            cout << "Passenger Name: " << PassengerCurrentNode->getname() << endl;
            cout << "Passenger ID: " << PassengerCurrentNode->getID() << endl;
            cout << "Passenger Flight Code: " << PassengerCurrentNode->getflightCode() << endl;
            cout << "Passenger Contact Number: " << PassengerCurrentNode->getcontactNumber() << endl
                 << endl;
            PassengerCurrentNode = PassengerCurrentNode->getNextNode();
        }
    }
}

// void AirportManagementSystem::showPassengerByID(string id)
// {
// }

// void AirportManagementSystem::showAllPassengerOfFlight(string flightCode)
// {
// }
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Passenger functions end) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main()
{
    AirportManagementSystem System;
    System.ImportData();

    cout << "\n%%%%%%%%%%%%%%%%%%% (Printing Passengers) %%%%%%%%%%%%%%%%%%%\n"
         << endl;
    System.showAllPassengers();
    cout << "\n%%%%%%%%%%%%%%%%%%% (Printing Employees) %%%%%%%%%%%%%%%%%%%\n"
         << endl;
    System.showALLEmployees();
    cout << "\n%%%%%%%%%%%%%%%%%%% (Printing Flight) %%%%%%%%%%%%%%%%%%%\n"
         << endl;
    System.showAllFlight();
    return 0;
}
