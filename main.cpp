#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <queue>
#include "SimulatorDriver.h"
#include "MakeEvent.h"
#include "Objects.h"

using namespace std;

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
            time = hour * 60 + min;
        }
    } while (time == -1);

    return time;
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
    runSimulation(lineName, time);

    return 0;
}



















