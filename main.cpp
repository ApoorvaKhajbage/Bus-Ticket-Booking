#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generateTicket(string busNumber, string name, string boardingPoint,
                    string destination) {
  // Open the tickets file
  ofstream ticketFile("tickets.csv", ios::app);

  // Check if the file was opened successfully
  if (!ticketFile) {
    cerr << "Error: Unable to open the ticket file" << endl;
    return;
  }

  // Check the ticket count for the selected bus
  ifstream ticketData("tickets.csv");
  if (!ticketData) {
    cerr << "Error: Unable to open the ticket data file" << endl;
    return;
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

    if (ticket[1] == busNumber) {
      ticketCount++;
    }
  }
  ticketData.close();

  // Check if the maximum limit of tickets has been reached
  if (ticketCount >= 30) {
    cout << "Maximum limit of tickets reached for bus " << busNumber
         << " and hence no " << endl;
    return;
  }

  // Generate a ticket number using the current system time
  time_t ticketTime = time(0);
  int ticketNumber = (int)ticketTime;

  // Write the ticket data to the file
  ticketFile << ticketNumber << "," << busNumber << "," << name << ","
             << boardingPoint << "," << destination << endl;

  // Close the file
  ticketFile.close();
}

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

  // Read the bus data from the file and store it in a vector
  vector<vector<string>> busRoutes;
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

    busRoutes.push_back(stops);
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
  for (unsigned int i = 0; i < busRoutes.size(); i++) {
    vector<string> stops = busRoutes[i];

    // Check if the boarding and destination points are in the bus route
    if (find(stops.begin(), stops.end(), boardingPoint) != stops.end() &&
        find(stops.begin(), stops.end(), destination) != stops.end()) {
      // The boarding and destination points are in the route, add the bus
      // number to the matching buses
      matchingBuses.push_back(stops[0]);
    }
  }

  // Print the matching buses to the console
  cout << "Buses that go through " << boardingPoint << " and " << destination
       << ":" << endl;
  for (unsigned int i = 0; i < matchingBuses.size(); i++) {
    cout << i + 1 << ". " << matchingBuses[i] << endl;
  }
  // Ask the user to select a bus
  int selection = 0;
  cout << "Please select a bus you want to board: ";
  cin >> selection;

  // Prompt the user to enter their name
  cout << "Enter your name: ";
  cin >> name;

  // Generate a ticket for the selected bus
  if (selection > 0 && selection <= matchingBuses.size()) {
    generateTicket(matchingBuses[selection - 1], name, boardingPoint,
                   destination);
    cout << "Ticket generated for bus " << matchingBuses[selection - 1]
         << " for " << name << endl;
  } else {
    cout << "Invalid selection" << endl;
  }

  return 0;
}
