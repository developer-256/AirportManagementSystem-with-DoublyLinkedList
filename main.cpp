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
    void displayPassenger()
    {
        cout << "Passenger Name: " << name << endl;
        cout << "Passenger ID: " << ID << endl;
        cout << "Passenger Flight Code: " << flightCode << endl;
        cout << "Passenger Contact Number: " << contactNumber << endl
             << endl;
    }
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
    void displayFlight()
    {
        cout << "Flight origin: " << origin << endl;
        cout << "Flight destination: " << destination << endl;
        cout << "Flight departure: " << departure << endl;
        cout << "Flight arrival: " << arrival << endl;
        cout << "Flight flighCode: " << flighCode << endl;
        cout << "Flight price: " << price << endl;
        cout << "Flight totalSeats: " << totalSeats << endl
             << endl;
    }
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
    void displayEmployee()
    {
        cout << "Employee Name: " << name << endl;
        cout << "Employee ID: " << ID << endl;
        cout << "Employee Designatione: " << designation << endl
             << endl;
    }
};

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
    void exportEntireData();

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
            else
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

void AirportManagementSystem::exportEntireData()
{
    ofstream Storage;
    Storage.open("Storage.txt", ios::trunc); // opening file in truncate mode so that original content in replaced
    // exporting employee data
    if (EmployeeHeadNode != nullptr)
    {
        EmployeeCurrentNode = EmployeeHeadNode;
        while (EmployeeCurrentNode != nullptr)
        {
            Storage << "employee," << EmployeeCurrentNode->getName() << "," << EmployeeCurrentNode->getID() << "," << EmployeeCurrentNode->getDesignation() << endl;
            EmployeeCurrentNode = EmployeeCurrentNode->getNextNode();
        }
    }
    // exporting passenger data
    if (PassengerHeadNode != nullptr)
    {
        PassengerCurrentNode = PassengerHeadNode;
        while (PassengerCurrentNode != nullptr)
        {
            Storage << "passenger," << PassengerCurrentNode->getname() << "," << PassengerCurrentNode->getID() << "," << PassengerCurrentNode->getflightCode() << "," << PassengerCurrentNode->getcontactNumber() << endl;
            PassengerCurrentNode = PassengerCurrentNode->getNextNode();
        }
    }
    // exporting flight data
    if (FlightHeadNode != nullptr)
    {
        FlightCurrentNode = FlightHeadNode;
        while (FlightCurrentNode != nullptr)
        {
            Storage << "flight," << FlightCurrentNode->getOrigin() << "," << FlightCurrentNode->getDestination() << "," << FlightCurrentNode->getDeparture() << "," << FlightCurrentNode->getArrival() << "," << FlightCurrentNode->getFlighCode() << "," << FlightCurrentNode->getTotalSeats() << "," << FlightCurrentNode->getPrice() << endl;
            FlightCurrentNode = FlightCurrentNode->getNextNode();
        }
    }
    Storage.close();
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
}

void AirportManagementSystem::popEmployee(string id)
{
    EmployeeCurrentNode = EmployeeHeadNode;
    while (EmployeeCurrentNode != nullptr)
    {
        if (EmployeeCurrentNode->getID() == id)
        {
            // If the node to be deleted is the head node
            if (EmployeeCurrentNode == EmployeeHeadNode)
            {
                EmployeeHeadNode = EmployeeCurrentNode->getNextNode();
            }

            if (EmployeeCurrentNode->getPrevNode() != nullptr)
            {
                EmployeeCurrentNode->getPrevNode()->setNextNode(EmployeeCurrentNode->getNextNode());
            }

            if (EmployeeCurrentNode->getNextNode() != nullptr)
            {
                EmployeeCurrentNode->getNextNode()->setPrevNode(EmployeeCurrentNode->getPrevNode());
            }

            delete EmployeeCurrentNode;
            employeeSize--;
            cout << "Employee successfully removed" << endl;
            return;
        }
        EmployeeCurrentNode = EmployeeCurrentNode->getNextNode();
    }
}

void AirportManagementSystem::showEmployeeByID(string id)
{
    EmployeeCurrentNode = EmployeeHeadNode;
    while (EmployeeCurrentNode != nullptr)
    {
        if (EmployeeCurrentNode->getID() == id)
        {
            EmployeeCurrentNode->displayEmployee();
        }
        EmployeeCurrentNode = EmployeeCurrentNode->getNextNode();
    }
}

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
            EmployeeCurrentNode->displayEmployee();
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
}

void AirportManagementSystem::popFlight(string flightCode)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getFlighCode() == flightCode)
        {
            // If the node to be deleted is the head node
            if (FlightCurrentNode == FlightHeadNode)
            {
                FlightHeadNode = FlightCurrentNode->getNextNode();
            }

            if (FlightCurrentNode->getPrevNode() != nullptr)
            {
                FlightCurrentNode->getPrevNode()->setNextNode(FlightCurrentNode->getNextNode());
            }

            if (FlightCurrentNode->getNextNode() != nullptr)
            {
                FlightCurrentNode->getNextNode()->setPrevNode(FlightCurrentNode->getPrevNode());
            }

            delete FlightCurrentNode;
            flightSize--;
            cout << "Flight successfully removed" << endl;
            return;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
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
            FlightCurrentNode->displayFlight();
            FlightCurrentNode = FlightCurrentNode->getNextNode();
        }
    }
}

void AirportManagementSystem::showFlightByFlightCode(string flightCode)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getFlighCode() == flightCode)
        {
            FlightCurrentNode->displayFlight();
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
}

void AirportManagementSystem::showFlightByOrigin(string Origin)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getOrigin() == Origin)
        {
            FlightCurrentNode->displayFlight();
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
}

void AirportManagementSystem::showFlightByDestination(string destinition)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getDestination() == destinition)
        {
            FlightCurrentNode->displayFlight();
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
}

void AirportManagementSystem::printUniqueOrigins()
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        bool isUnique = true;
        FlightNode *temp = FlightHeadNode;
        while (temp != FlightCurrentNode)
        {
            if (temp->getOrigin() == FlightCurrentNode->getOrigin())
            {
                isUnique = false;
                break;
            }
            temp = temp->getNextNode();
        }
        if (isUnique)
        {
            cout << FlightCurrentNode->getOrigin() << endl;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
    cout << endl;
}

bool AirportManagementSystem::checkOriginAvailiblity(string o)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getOrigin() == o)
        {
            return true;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
    return false;
}

void AirportManagementSystem::printUniqueDestinations()
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        bool isUnique = true;
        FlightNode *temp = FlightHeadNode;
        while (temp != FlightCurrentNode)
        {
            if (temp->getDestination() == FlightCurrentNode->getDestination())
            {
                isUnique = false;
                break;
            }
            temp = temp->getNextNode();
        }
        if (isUnique)
        {
            cout << FlightCurrentNode->getDestination() << endl;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
    cout << endl;
}

bool AirportManagementSystem::checkDestinationAvailiblity(string d)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getDestination() == d)
        {
            return true;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
    return false;
}

void AirportManagementSystem::getFlight(string o, string d)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getOrigin() == o && FlightCurrentNode->getDestination() == d)
        {
            FlightCurrentNode->displayFlight();
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
}

bool AirportManagementSystem::checkFlightCode(string o, string d, string fC)
{
    FlightCurrentNode = FlightHeadNode;
    while (FlightCurrentNode != nullptr)
    {
        if (FlightCurrentNode->getOrigin() == o && FlightCurrentNode->getDestination() == d && FlightCurrentNode->getFlighCode() == fC)
        {
            return true;
        }
        FlightCurrentNode = FlightCurrentNode->getNextNode();
    }
    return false;
}

// +++++++++++++++++++++++++++++++++++++ ( Flight functions end) +++++++++++++++++++++++++++++++++++++

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Passenger functions start) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
}

void AirportManagementSystem::cancelBooking_popPassenger(string id)
{
    PassengerCurrentNode = PassengerHeadNode;
    while (PassengerCurrentNode != nullptr)
    {
        if (PassengerCurrentNode->getID() == id)
        {
            if (PassengerCurrentNode == PassengerHeadNode)
            {
                PassengerHeadNode = PassengerCurrentNode->getNextNode();
            }

            if (PassengerCurrentNode->getPrevNode() != nullptr)
            {
                PassengerCurrentNode->getPrevNode()->setNextNode(PassengerCurrentNode->getNextNode());
            }

            if (PassengerCurrentNode->getNextNode() != nullptr)
            {
                PassengerCurrentNode->getNextNode()->setPrevNode(PassengerCurrentNode->getPrevNode());
            }

            delete PassengerCurrentNode;
            passengerSize--;
            cout << "Passenger successfully removed" << endl;
        }

        PassengerCurrentNode = PassengerCurrentNode->getNextNode();
    }
}

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
            PassengerCurrentNode->displayPassenger();
            PassengerCurrentNode = PassengerCurrentNode->getNextNode();
        }
    }
}

void AirportManagementSystem::showPassengerByID(string id)
{
    PassengerCurrentNode = PassengerHeadNode;
    while (PassengerCurrentNode != nullptr)
    {
        if (PassengerCurrentNode->getID() == id)
        {
            PassengerCurrentNode->displayPassenger();
        }

        PassengerCurrentNode = PassengerCurrentNode->getNextNode();
    }
}

void AirportManagementSystem::showAllPassengerOfFlight(string flightCode)
{
    PassengerCurrentNode = PassengerHeadNode;
    while (PassengerCurrentNode != nullptr)
    {
        if (PassengerCurrentNode->getflightCode() == flightCode)
        {
            PassengerCurrentNode->displayPassenger();
        }

        PassengerCurrentNode = PassengerCurrentNode->getNextNode();
    }
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ( Passenger functions end) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main()
{
    system("cls");
    AirportManagementSystem System;
    System.ImportData();
    // System.popEmployee("0001");
    // System.popEmployee("0003");
    // System.popFlight("DRP001");

    // cout << "\n%%%%%%%%%%% (Printing Passengers) %%%%%%%%%%%\n"
    //      << endl;
    // System.showAllPassengers();
    // cout << "\n%%%%%%%%%%% (Printing Employees) %%%%%%%%%%%\n"
    //      << endl;
    // System.showALLEmployees();
    // cout << "\n%%%%%%%%%%% (Printing Flight) %%%%%%%%%%%\n"
    //      << endl;
    // System.showAllFlight();
    // System.getFlight("Lahore", "Washington");
    // System.showFlightByOrigin("Lahore");
    // System.showFlightByDestination("Washington");
    // cout << System.checkFlightCode("Lahore", "Washington", "DRP001");
    return 0;
}
