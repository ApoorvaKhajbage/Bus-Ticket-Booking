# JAN PARIVAHAN - Bus Ticket Management System

## Overview

JAN PARIVAHAN is a simple bus ticket management system implemented in Python. It consists of two main classes: Ticket and Bus. The Ticket class handles ticket generation and storage, while the Bus class manages information about buses and their stops.

## Code Explanation

### Ticket Class
The Ticket class is responsible for generating and storing information about bus tickets. It includes the following functionalities:

- **Constructor**: Initializes ticket data such as ticket number, bus number, passenger name, boarding point, destination, and fare. The ticket number is generated using the current system time.
- **writeToFile()**: Writes ticket data to a CSV file named "tickets.csv" in a comma-separated format.
- **printTicket()**: Formats and prints ticket information to the console, including the booking time and ticket validity.

### Bus Class
The Bus class stores information about buses, including the bus number and stops. Key functionalities include:

- **Constructors**: Two constructors, one with default values and another that accepts bus number and stops as arguments.
- **getNumber()**: Returns the bus number.
- **getStops()**: Returns the stops that the bus makes.
- **isFull()**: Checks if the bus has reached its maximum ticket limit by counting the tickets associated with the bus in the "tickets.csv" file.
- **bookTicket()**: Books a ticket for the current bus, calculating the fare based on the distance between the boarding point and destination. If the bus is full, it displays an error message; otherwise, it creates a new Ticket object, writes ticket data to the CSV file, and prints the ticket information.

## Usage
To use the JAN PARIVAHAN system:
1. Instantiate Bus and Ticket objects as needed.
2. Book tickets using the `bookTicket()` method of the Bus class.
3. View booked tickets and their details using the `printTicket()` method of the Ticket class.

## Note
Ensure that the "tickets.csv" file exists and is writable by the program for ticket storage.

This system provides a basic framework for managing bus tickets efficiently and can be further expanded to include additional features such as ticket cancellation, seat allocation, and user authentication.
