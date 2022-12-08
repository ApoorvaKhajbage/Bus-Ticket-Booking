#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class Ticket {
public:
  Ticket(string busNumber, string name, string boardingPoint,
         string destination, int fare) {
    // Generate a ticket number using the current system time
    time_t ticketTime = time(0);
    int ticketNumber = (int)ticketTime;

    // Set the ticket data using pointer to a current object
    this->ticketNumber = ticketNumber;
    this->busNumber = busNumber;
    this->name = name;
    this->boardingPoint = boardingPoint;
    this->destination = destination;
    this->fare = fare;
  }

  // Write the ticket data to a file
  void writeToFile() {
    // Open the tickets file
    ofstream ticketFile("tickets.csv", ios::app);

    // Check if the file was opened successfully
    if (!ticketFile) {
      cerr << "Error: Unable to open the ticket file" << endl;
      return;
    }

    // Write the ticket data to the file
    ticketFile << ticketNumber << "," << busNumber << "," << name << ","
               << boardingPoint << "," << destination << "," << fare << endl;

    // Close the file
    ticketFile.close();
  }

  // Print the ticket
  void printTicket() {
    cout << "--------------------------------------" << endl;
    cout << "          JAN PARIVAHAN         " << endl;
    cout << "Ticket Number: " << ticketNumber << endl;
      time_t ticketTime = time(0);
      tm* loc_time = localtime(&ticketTime);
      loc_time->tm_hour += 5;
      loc_time->tm_min += 30;

  // Convert the modified time back into a timestamp
  ticketTime = mktime(loc_time);

    cout << "Booking Time : " << asctime(loc_time);
      loc_time->tm_hour += 1;
    cout << "Valid Till : " << asctime(loc_time);
    cout << "Bus Number: " << busNumber << endl;
    cout << "Passenger Name: " << name << endl;
    cout << "Boarding Point: " << boardingPoint << endl;
    cout << "Destination: " << destination << endl;
    cout << "Fare: ₹" << fare << endl;
    cout << "--------------------------------------" << endl;
  }
private:
  int ticketNumber;
  string busNumber; //Remember busNumber is a data member of Ticket class not bus class and bus->number is different
  string name;
  string boardingPoint;
  string destination;
  int fare;
};

class Bus {
public:
  Bus() {
    // Set default values without this, variables would be undefined
    this->number = "";
    this->stops = {};
  }

  Bus(string number, vector<string> stops) {
    this->number = number;
    this->stops = stops;
  }
  // Get the bus number
  string getNumber() { return number; }

  // Get the bus stops
  vector<string> getStops() { return stops; }

  // Check if the maximum limit of tickets has been reached for this bus
  bool isFull() {
    ifstream ticketData("tickets.csv");//can't open in write mode otherwise getline function wont work
    if (!ticketData) {
      cout << "Error: Unable to open the ticket data file" << endl;
      return true;
    }

    int ticketCount = 0;
    string line;
    getline(ticketData, line); // skip the headers
    while (getline(ticketData, line)) {
      // Split the line by commas to extract the individual fields
      size_t pos = 0;
      string token;
      vector<string> ticket;
      while ((pos = line.find(",")) != string::npos) {
        token = line.substr(0, pos);
        ticket.push_back(token);
        line.erase(0, pos + 1);
      }
      ticket.push_back(line);

      if (ticket[1] == number) {
        ticketCount++;
      }
    }
    ticketData.close();

    return ticketCount >= 30;
  }

  // Generate a ticket for this bus
  void generateTicket(string name, string boardingPoint, string destination) {

    if (!isFull()) {
      // Calculate the fare between the boarding point and the destination
      int fare = abs(10 * (find(stops.begin(), stops.end(), destination) -
                       find(stops.begin(), stops.end(), boardingPoint)));

      Ticket ticket(number, name, boardingPoint, destination, fare);
      ticket.writeToFile();

      // Print the ticket
      ticket.printTicket();
    } else {
      cout << "Unable to book ticket because Maximum limit of tickets reached "
              "for bus "
           << number << endl;
    }
  }

private:
  string number;
  vector<string> stops;
};

int main() {
  // Open the CSV file
  ifstream busData("bus_data.csv");
  // Check if the file was opened successfully
  if (!busData) {
    cerr << "Error: Unable to open the bus data file" << endl;
    return 1;
  }

  // Read the headers from the file
  string line;
  getline(busData, line);

  // Read the bus data from the file and create Bus objects
  vector<Bus> buses;
  while (getline(busData, line)) {
    // Split the line by commas to extract the individual bus stops
    vector<string> stops;
    size_t pos = 0;
    string token;
    while ((pos = line.find(",")) != string::npos) {
      token = line.substr(0, pos);
      stops.push_back(token);
      line.erase(0, pos + 1);
    }
    stops.push_back(line);
    buses.push_back(Bus(stops[0], stops));
  }

  // Close the file
  busData.close();
  // Prompt the user to enter the boarding and destination points
  string boardingPoint, destination, name;
  cout << "Enter the boarding point: ";
  cin >> boardingPoint;
  cout << "Enter the destination: ";
  cin >> destination;

  // Find the bus numbers of the buses that go through the specified stops
  vector<string> matchingBuses;
  for (int i = 0; i < buses.size(); i++) {
    vector<string> stops = buses[i].getStops();
    // Check if the boarding and destination points are in the bus route
    if (find(stops.begin(), stops.end(), boardingPoint) != stops.end() &&
        find(stops.begin(), stops.end(), destination) != stops.end()) {
      // The boarding and destination points are in the route, add the bus
      // number to the matchingBuses vector
      matchingBuses.push_back(buses[i].getNumber());
    }
  }

  // Check if there are any matching buses
  if (matchingBuses.empty()) {
    cout << "There are no buses available between the specified stops" << endl;
    return 0;
  }

  // Print the matching buses
  cout << "Matching buses: " << endl;
  for (int i = 0; i < matchingBuses.size(); i++) {
    cout << matchingBuses[i] << endl;
  }

  // Prompt the user to select a bus
  string busNumber;
  cout << "Enter the bus number: ";
  cin >> busNumber;
    if(find(matchingBuses.begin(), matchingBuses.end(),busNumber) == matchingBuses.end()){
      cout << "No matching bus. Try again." << endl;
      return 0;
    }

  // Find the selected bus
  Bus selectedBus;
  for (int i = 0; i < buses.size(); i++) {
    if (buses[i].getNumber() == busNumber) {
      selectedBus = buses[i];
      break;
    }
  }
  // Prompt the user for their name
  cout << "Enter your name: ";
  cin >> name;

  // Generate a ticket for the selected bus
  selectedBus.generateTicket(name, boardingPoint, destination);

  return 0;
}
