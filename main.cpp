#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
//#include <pair>
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

string getTime(int time){
    int mins[4] = { 600, 60, 10, 1 };
    string news = "0000";
    int m = time% 1440;
    for (int d = 0; d < 4; d++) {
        news[d] = '0'+ m / mins[d]; m %= mins[d];
    }
    return news.substr(0, 2) + ':' + news.substr(2, 2);
}

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
    char check;
    string timestring = "04:40";
    cout << "Great! We'll simulate the " << lineName << " line."<<endl;
    cout<<"Would you like you enter a start time for the train simulation? (y/n): ";
    cin >> check;
    if (check != 'y' && check != 'n') {
        cout << "Please enter 'y' for yes and 'n' for no!: " << endl;
        cin >> check;
    }
    if (check == 'y') {
        cout << "What time should the train depart from the first station?" << endl;
        cout << "Enter time(earliest= 04:40am, latest= 23:59pm) in military format: HH:MM -> ";
        cin >> timestring;
    }

    int time = -1, hour = -1, min = -1;
    do {
        // Parse input, check for validity, and assign time
        if (timestring[2] != ':') {
            cout << "   Invalid time!\nEnter time(earliest= 04:40am, latest= 23:59pm) in military format: HH:MM -> ";
            cin >> timestring;
        }
        try {
            hour = stoi(timestring.substr(0, 2));
            min = stoi(timestring.substr(3, 2));
                if (hour < 4 || hour > 23 || min < 0 || min > 59 || (hour == 4 && min < 40)) {
                    cout
                            << "   Invalid time!\nEnter time(earliest= 04:40am, latest= 23:59pm) in military format: HH:MM -> ";
                    cin >> timestring;
                } else
                    time = hour * 60 + min;
        } catch (exception& e){
            cout<<"   Invalid time!\nEnter time(earliest= 04:40am, latest= 23:59pm) in military format: HH:MM -> ";
            cin >> timestring;
        }

    } while (time == -1);

    return time;
}

void setEndTime(){
    // Prompt user to enter time to end simulation
    char check;
    cout<<"Would you like you enter an end time for the train simulation? (y/n): ";
    cin >> check;
    if (check != 'y' && check != 'n') {
        cout << "Please enter 'y' for yes and 'n' for no!: " << endl;
        cin >> check;
    }
    if (check == 'y') {
        string timestring;
        cout << "What time should the simulation stop running?" << endl;
        cout << "Enter time(earliest= 05:00am, latest= 02:00am) in military format: HH:MM -> ";
        cin >> timestring;

        int time = -1, hour = -1, min = -1;
        do {
            // Parse input, check for validity, and assign time
            if (timestring[2] != ':') {
                cout
                        << "   Invalid time!\nEnter time(earliest= 05:00am, latest= 02:00am) in military format: HH:MM -> ";
                cin >> timestring;
            }
            try {
                hour = stoi(timestring.substr(0, 2));
                min = stoi(timestring.substr(3, 2));
                if (hour > 23 || min < 0 || min > 59 ) {
                    cout
                            << "   Invalid time!\nEnter time(earliest= 05:00am, latest= 02:00am) in military format: HH:MM -> ";
                    cin >> timestring;
                } else if ((hour < 5 && hour > 2) || (hour == 2 && min > 0)){
                    cout
                            << "   Invalid time!\nEnter time(earliest= 05:00am, latest= 02:00am) in military format: HH:MM -> ";
                    cin >> timestring;
                } else {
                    stopTime = time = hour * 60 + min;
                    if (hour <= 2)
                        stopTime = time = hour * 60 + min + 1440;
                }
            } catch (exception &e) {
                cout
                        << "   Invalid time!\nEnter time(earliest= 05:00am, latest= 02:00am) in military format: HH:MM -> ";
                cin >> timestring;
            }

        } while (time == -1);
    }
}

pair<string, pair<int, int> > getEvent(){
    // Prompt user to enter station for event
    string name = "";
    int start= -1, stop= -1;
    char check;
    cout<<"Would there be an event today? (y/n): ";
    cin >> check;
    if (check != 'y' && check != 'n') {
        cout << "Please enter 'y' for yes and 'n' for no: " << endl;
        cin >> check;
    }
    if (check == 'y') {
        //int temp;
        string timestring;
        cout << "Enter name of closest station in sentence-case format(eg. Edgewood-Candler Park): ";
        cin.ignore();
        std::getline(std::cin, name);
        cout << "Enter event start time(earliest= 05:00am, latest= 23:59pm) in military format: HH:MM -> ";
        cin >> timestring;

        int time = -1, hour = -1, min = -1;
        do {
            // Parse input, check for validity, and assign time
            if (timestring[2] != ':') {
                cout << "   Invalid time!\nEnter event start time(earliest= 05:00am, latest= 23:59pm) in military format: HH:MM -> ";
                cin >> timestring;
            }
            try {
                hour = stoi(timestring.substr(0, 2));
                min = stoi(timestring.substr(3, 2));
                if (hour < 5 || hour > 23 || min < 0 || min > 59) {
                    cout
                            << "   Invalid time!\nEnter event start time(earliest= 05:00am, latest= 23:59pm) in military format: HH:MM -> ";
                    cin >> timestring;
                } else
                    start = hour * 60 + min;
            } catch (exception& e){
                cout<<"   Invalid time!\nEnter event start time(earliest= 05:00am, latest= 23:59pm) in military format: HH:MM -> ";
                cin >> timestring;
            }
        } while (start == -1);

        cout << "Enter event End time(earliest= 06:00am, latest= 23:59pm) in military format: HH:MM -> ";
        cin >> timestring;

        do {
            // Parse input, check for validity, and assign time
            if (timestring[2] != ':') {
                cout << "   Invalid time!\nEnter event End time(earliest= 06:00am, latest= 23:59pm) in military format: HH:MM -> ";
                cin >> timestring;
            }
            try {
                hour = stoi(timestring.substr(0, 2));
                min = stoi(timestring.substr(3, 2));
                if (hour < 6 || hour > 23 || min < 0 || min > 59) {
                    cout
                            << "   Invalid time!\nEnter event End time(earliest= 06:00am, latest= 23:59pm) in military format: HH:MM -> ";
                    cin >> timestring;
                } else
                    stop = hour * 60 + min;
            } catch (exception& e){
                cout<<"   Invalid time!\nEnter event End time(earliest= 06:00am, latest= 23:59pm) in military format: HH:MM -> ";
                cin >> timestring;
            }
        } while (stop == -1);
    }
    return pair<string, pair<int, int> >(name, pair<int, int>(start,stop));
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

    cout<<endl;

    int count = 0;
    for (auto event : eventHist) {
        if (lastEvent->stationName == event->stationName) {
            cout << "Trip " << setfill('0') << setw(2) << tripNum << ": " << tripStart << " ----> " << event->stationName;
            cout << " | " << getTime(tripStartTime);
            cout << " to " << getTime(event->time);
            cout << " | Passengers/station: " << (tripPassengerSum / tripStationCount);
            cout << endl;

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

        //cout<<"Test "<<count++<<endl;
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
            cout << "Time: " << getTime(event->time) << " numOn: " << event->numBoard << " numOff: " << event->numDeboard
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
    setEndTime();
    pair<string, pair<int, int> > ev = getEvent();
    cout << "Starting simulation..." << endl;
    // run simulation and get back list of every event that occurred.
    // this is a vector of struct pointers. See Objects.h for the data elements of the eventLog struct.
    vector<eventLog*> eventHist = runSimulation(lineName, time, ev.first, ev.second.first, ev.second.second);
    //cout<< ev.first<<" "<< ev.second.first<<" "<< ev.second.second<<endl;

    giveFeedback(&eventHist, lineName);

    return 0;
}



















