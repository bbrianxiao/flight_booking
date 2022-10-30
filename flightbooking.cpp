#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class FlightBooking
{
public:
    FlightBooking(int id, int capacity, int reserved);
    FlightBooking();
    void printStatus();
    bool reserveSeats(int numberOfSeats);
    bool cancelReservations(int numberOfSeats);
    int getId();

private:
    int id;
    int capacity;
    int reserved;
};

void FlightBooking::printStatus()
{
    printf("Flight %d : %d/%d (%d%%) seats reserved \n", id, reserved, capacity, (reserved * 100 / capacity));
}

FlightBooking::FlightBooking()
{
    this->id = 0;
    this->capacity = 0;
    this->reserved = 0;
}

FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
    // if the reserved number is negative, set the number to 0
    if (reserved < 0)
        reserved = 0;
    // if the reserved number is more than 105% of the capacity, set the number to 105% of the capacity
    if ((reserved * 1.0 / capacity) > 1.05)
        reserved = (int)capacity * 1.05;
    this->id = id;
    this->capacity = capacity;
    this->reserved = reserved;
}

// try to add reservations and return 'true' on success
bool FlightBooking::reserveSeats(int numberOfSeats)
{
    // if the number is negative, set the number to 0
    if (numberOfSeats < 0)
        numberOfSeats = 0;

    // it will not allow more than 105% reservation of the total capacity
    if (((numberOfSeats + this->reserved) * 1.0 / this->capacity) <= 1.05)
    {
        this->reserved += numberOfSeats;
        return true;
    }
    return false;
}

// try to cancel reservations and return 'true' on success
bool FlightBooking::cancelReservations(int numberOfSeats)
{
    // if the number is negative, set the number to 0
    if (numberOfSeats < 0)
        numberOfSeats = 0;
    // the number of seats of cancellation must NOT greater than the total reserved seats
    if (numberOfSeats <= this->reserved)
    {
        this->reserved -= numberOfSeats;
        return true;
    }
    return false;
}

int FlightBooking::getId()
{
    return this->id;
}

string leftTrim(string str);
string spaceTrim(string str);
string toLowerCase(string str);
bool stringToNumber(string numberString, int *number);
bool parsingCommand(string inputLine, string *command, int *id, int *number);
int createFlight(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int capacity);
int deleteFlight(FlightBooking flights[], int *numberOfFlightBookings, int flightId);
int reserveSeats(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int numberOfSeats);
int cancelSeats(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int numberOfSeats);

const int MAX_NUMBER_OF_FLIGHT_BOOKINGS = 10;

int main()
{
    FlightBooking bookings[MAX_NUMBER_OF_FLIGHT_BOOKINGS];
    int numberOfFlightBookings = 0; // to save the number of flight bookings already created
    string command = "";
    string cmd = "";
    int flightId;
    int number;
    while (command != "quit")
    {
        if (numberOfFlightBookings == 0)
            cout << "No flights in the system" << endl;
        else
        {
            for (int i = 0; i < numberOfFlightBookings; i++)
                bookings[i].printStatus();
        }

        cout << endl
             << "What would you like to do?: ";
        getline(cin, command);
        if (!parsingCommand(command, &cmd, &flightId, &number))
        {
            cout << "Invalid Command! The valid command format is create [id][n], add [id][n], cancel[id][n], delete [id], or quit" << endl;
        }
        else
        {
            if (cmd == "quit")
                break;
            if (cmd == "create")
            {
                int result = createFlight(bookings, &numberOfFlightBookings, flightId, number);
                if (result == -1)
                {
                    cout << "Cannot perform this operation: maxium number of flights has been reached." << endl;
                }
                else if (result == -2)
                {
                    cout << "Cannot perform this operation: the flight " << flightId << " already exists." << endl;
                }
                else if (result == -3)
                {
                    cout << "Cannot perform this operation: the flight capacity can NOT be zero or negative." << endl;
                }
            }
            if (cmd == "delete")
            {
                int result = deleteFlight(bookings, &numberOfFlightBookings, flightId);
                if (result == -1)
                {
                    cout << "Cannot perform this operation: flight " << flightId << " not found." << endl;
                }
            }
            if (cmd == "add")
            {
                int result = reserveSeats(bookings, &numberOfFlightBookings, flightId, number);
                if (result == -1)
                {
                    cout << "Cannot perform this operation: flight " << flightId << " not found." << endl;
                }
                else if (result == -2)
                {
                    cout << "Cannot perform this operation: capacity reached." << endl;
                }
            }
            if (cmd == "cancel")
            {
                int result = cancelSeats(bookings, &numberOfFlightBookings, flightId, number);
                if (result == -1)
                {
                    cout << "Cannot perform this operation: flight " << flightId << " not found." << endl;
                }
                else if (result == -2)
                {
                    cout << "Cannot perform this operation: the number of cancellation is greater than the number of seats reserved." << endl;
                }
            }
        }
    }

    return 0;
}

// remove all leading spaces from the string
// for example, string "   create 101 200" will be converted to "create 101 200"
string leftTrim(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            result = result + str.substr(i);
            break;
        }
    }
    return result;
}

// convert multipul spaces to a single space in a string
// for example, string "aa   bb    cc" will be converted to "aa bb cc"
string spaceTrim(string str)
{
    string result = "";
    bool isMultipleSpace = false;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            result = result + str[i];
            isMultipleSpace = false;
        }
        else
        {
            if (!isMultipleSpace)
            {
                result = result + " ";
                isMultipleSpace = true;
            }
        }
    }

    return result;
}

// convert all characters to lower case in a string
string toLowerCase(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        result.push_back(tolower(str[i]));
    }
    return result;
}

// convert a string to a number
// if a string is a valid number, convert it to an integer, return true.
// otherwise return false
// for example, string "123" will be converted to number 123 and return true
// string "123B" or "A123" will not be converted and return false
bool stringToNumber(string numberString, int *number)
{
    bool result = true;
    if (numberString.size() > 0 && isdigit(numberString[0]) == 0 && (numberString[0] != '-')) // first letter is not a digit nor a minus sign
    {
        result = false;
        return result;
    }
    for (int i = 1; i < numberString.size(); i++)
    {

        if ((isdigit(numberString[i]) == 0)) // not a digit
        {
            result = false;
            return result;
        }
    }
    try
    {
        *number = (stoi(numberString));
    }
    catch (const std::invalid_argument &ex)
    {
        result = false;
    }
    catch (const std::out_of_range &ex)
    {
        result = false;
    }

    return result;
}

// parsing user input to get command, flight Id, and parameter(number)
// if the valid command, valid flight Id, valid parameter(number) are received, return true
// if the command is invalid, or the flight Id is not a valid number, or the parameter(number) is not a valid number, return false
bool parsingCommand(string inputLine, string *command, int *flightId, int *number)
{
    bool flag = false;
    string result = "";
    string cmd, id, num;

    stringstream X(toLowerCase(spaceTrim(leftTrim(inputLine))));

    while (getline(X, cmd, ' '))
    {
        if (cmd == "create")
        {
            flag = true;
            *command = cmd;
            getline(X, id, ' ');
            flag = stringToNumber(id, flightId);
            if (!flag)
                break;
            getline(X, num, ' ');
            flag = stringToNumber(num, number);
            break;
        }
        if (cmd == "delete")
        {
            flag = true;
            *command = cmd;
            getline(X, id, ' ');
            flag = stringToNumber(id, flightId);
            break;
        }
        else if (cmd == "add")
        {
            flag = true;
            *command = cmd;
            getline(X, id, ' ');
            flag = stringToNumber(id, flightId);
            if (!flag)
                break;
            getline(X, num, ' ');
            flag = stringToNumber(num, number);
            break;
        }
        else if (cmd == "cancel")
        {
            flag = true;
            *command = cmd;
            getline(X, id, ' ');
            flag = stringToNumber(id, flightId);
            if (!flag)
                break;
            getline(X, num, ' ');
            flag = stringToNumber(num, number);
            break;
        }
        else if (cmd == "quit")
        {
            *command = cmd;
            flag = true;
            break;
        }
    }

    return flag;
}

// create a flight if possible
// if the maxium number of flights(10) has already been reached, new flight will not be created, return -1;
// if the flightId already exists, new flight will not be created, return -2;
// if the capacity is negative or zero, new flight will not be created, return -3;
// if the above two conditions does not occur, flight will be created, return 1.
int createFlight(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int capacity)
{
    if (*numberOfFlightBookings == MAX_NUMBER_OF_FLIGHT_BOOKINGS)
        return -1; // the maxium number of flights has been reached
    if (capacity <= 0)
        return -3; // capacity can not be 0 or less

    for (int i = 0; i < *numberOfFlightBookings; i++)
    {
        if (flights[i].getId() == flightId)
            return -2; // flight already exist
    }

    FlightBooking flight = FlightBooking(flightId, capacity, 0);
    flights[*numberOfFlightBookings] = flight;
    (*numberOfFlightBookings)++;

    return 1;
}

// delete a flight if possible
// if the flightId was not found, return -1;
// if the flight ID was found, delete the flight, return 1.
int deleteFlight(FlightBooking flights[], int *numberOfFlightBookings, int flightId)
{
    bool found = false;
    int index = 0;
    if (*numberOfFlightBookings == 0)
        return -1; // flight not found
    for (int i = 0; i < *numberOfFlightBookings; i++)
    {
        if (flights[i].getId() == flightId)
        {
            index = i;
            found = true;
            break;
        }
    }

    if (!found)
        return -1; // flight not found

    for (int i = index; i < *numberOfFlightBookings; i++)
        flights[i] = flights[i + 1];
    (*numberOfFlightBookings)--;
    return 1; // delete flight successfully
}

// reserve seats for a flight if possible
// if the flight ID does not find, return -1;
// if the capacity of the flight reached, return -2;
// seats reserved successfully, return 1.
int reserveSeats(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int numberOfSeats)
{
    bool found = false;
    int index = 0;
    if (*numberOfFlightBookings == 0)
        return -1; // flight not found
    for (int i = 0; i < *numberOfFlightBookings; i++)
    {
        if (flights[i].getId() == flightId)
        {
            index = i;
            found = true;
            break;
        }
    }

    if (!found)
        return -1; // flight not found

    if (flights[index].reserveSeats(numberOfSeats))
        return 1; // reserved successfully
    else
        return -2; // capacity reached
}

// cancel seats from a flight if possible
// if the flight ID does not find, return -1;
// if the number of cancellation is greater than the number of seats reserved, return -2;
// seats cancelled successfully, return 1.
int cancelSeats(FlightBooking flights[], int *numberOfFlightBookings, int flightId, int numberOfSeats)
{
    bool found = false;
    int index = 0;
    if (*numberOfFlightBookings == 0)
        return -1; // flight not found
    for (int i = 0; i < *numberOfFlightBookings; i++)
    {
        if (flights[i].getId() == flightId)
        {
            index = i;
            found = true;
            break;
        }
    }

    if (!found)
        return -1; // flight not found

    if (flights[index].cancelReservations(numberOfSeats))
        return 1; // reserved successfully
    else
        return -2; // the number of cancellation is greater than the number of seats reserved
}
