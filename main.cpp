#include <iostream>
#include <iomanip>
#include "SimulatorDriver.h"

using namespace std;

/*
 * * * * * * * * * * * * * *
 * MARTA Simulator         *
 * ECE4122                 *
 *                         *
 * Toya Amechi             *
 * Noah Roberts            *
 * Jackson Sheu            *
 * * * * * * * * * * * * * *
 */

//TODO: event support
//TODO: make numbers more believable
//TODO: show more data to the user
//TODO: make printing times prettier

string getLineNameInput() {
    // Take input and make sure it's valid.
    // Exception handling could be more elegant, but this works for now.
    string lineName;
    do {
        int input;
        cin >> input;

        switch (input) {
            case 1:
                lineName = "Red";
                break;
            case 2:
                lineName = "Gold";
                break;
            case 3:
                lineName = "Blue";
                break;
            case 4:
                lineName = "Green";
                break;

            default:
                cout << "Oops! Please enter a valid input (1, 2, 3, or 4)";
        }
    } while (lineName.empty());

    return lineName;
}

int getTimeInput(const string &lineName) {
    // Prompt user to enter time
    cout << "Great! We'll simulate the " << lineName << " line. What time should the train depart from the first station?" << endl;
    cout << "   Please enter a time in military time in this format: HH:MM" << endl;

    // Parse input, check for validity, and assign time
    int time = -1;
    do {
        int hour, min;
        cin >> hour;
        if (cin.get() != ':') {
            cout << "Invalid time! Please enter a military time in the format HH:MM" << endl;
        } else {
            cin >> min;
            if (0 <= hour && hour < 24 && 0 <= min && min < 60)
                time = hour * 60 + min;
            else
                cout << "Invalid time! Please enter a military time in the format HH:MM" << endl;
        }
    } while (time == -1);

    return time;
}

// Display user feedback
void giveFeedback(vector<eventLog*>* evH, string lineName) {
    vector<eventLog*> &eventHist = *evH;

    // For aggregating trips
    eventLog* lastEvent;
    int tripNum = 1;
    int tripStationCount = 0;
    int tripPassengerSum = 0;
    int tripBoardSum = 0;
    int tripDeboardSum = 0;
    int tripStartTime = eventHist.front()->time;
    string tripStart = eventHist.front()->stationName;

    int stationCount = 0;
    int passengerSum = 0;
    int boardSum = 0;
    int deboardSum = 0;

    for (auto event : eventHist) {
        if (lastEvent->stationName == event->stationName) {
            cout << "Trip " << setfill('0') << setw(2) << tripNum << ": " << tripStart << " ----> " << event->stationName;
            cout << " | " << setfill('0') << setw(2) << tripStartTime/60 << ":" << setfill('0') << setw(2) << tripStartTime%60;
            cout << " to " << setfill('0') << setw(2) << event->time/60 << ":" << setfill('0') << setw(2) << event->time%60;
            cout << " | Passengers/station: " << (tripPassengerSum / tripStationCount);
            cout << " | Boarding passengers/station: " << (tripBoardSum / tripStationCount);
            cout << " | Deboarding passengers/station: " << (tripDeboardSum / tripStationCount) << endl;

            tripNum++;
            tripStationCount = 0;
            tripPassengerSum = 0;
            tripBoardSum = 0;
            tripDeboardSum = 0;
            tripStartTime = event->time;
            tripStart = event->stationName;
        }

        tripStationCount++;
        tripBoardSum += event->numBoard;
        tripDeboardSum += event->numDeboard;
        tripPassengerSum += event->numPassengers;
        lastEvent = event;

        stationCount++;
        boardSum += event->numBoard;
        deboardSum += event->numDeboard;
        passengerSum += event->numPassengers;
    }

    cout << endl << "MARTA " << lineName << " Line 24 hour simulation results:" << endl;
    cout << "   Passengers/station: " << (passengerSum / stationCount) << endl;
    cout << "   Boarding passengers/station: " << (boardSum / stationCount) << endl;
    cout << "   Deboarding passengers/station: " << (deboardSum / stationCount) << endl << endl;

    cout << "Would you like to see the verbose output? (y/n)" << endl;
    char input;
    bool valid = true;
    bool verbose;
    do {
        cin >> input;
        if (input == 'y' || input == 'Y') {
            verbose = true;
            valid = true;
        } else if (input == 'n' || input == 'N') {
            verbose = false;
            valid = true;
        } else {
            valid = false;
            cout << "Uh oh! Please enter one of the following: y/n" << endl;
        }
    } while (!valid);

    if (verbose) {
        cout << "Verbose output:" << endl;
        for (auto event : eventHist) {
            cout << "Time: " << event->time << " numOn: " << event->numBoard << " numOff: " << event->numDeboard
                 << " numPassengers: ";
            cout << event->numPassengers << " Name: " << event->stationName << endl;
        }
    }
}


int main() {

    // Intro and user input
    cout << "Welcome to MARTA Sim!" << endl;
    cout << "   This program models the ridership of a single MARTA train." << endl << endl;
    cout << "Which line would you like to simulate?" << endl;
    cout << "   1 - Red" << endl << "   2 - Gold" << endl << "   3 - Blue" << endl << "   4 - Green" << endl;

    string lineName = getLineNameInput();
    int time = getTimeInput(lineName);

    cout << "Starting simulation..." << endl;
    // run simulation and get back list of every event that occurred.
    // this is a vector of struct pointers. See Objects.h for the data elements of the eventLog struct.
    vector<eventLog*> eventHist = runSimulation(lineName, time);
    giveFeedback(&eventHist, lineName);

    return 0;
}



















