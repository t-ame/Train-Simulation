//
// Created by Noah Roberts on 4/14/18.
//

#include "Objects.h"
#include <utility>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>

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

using namespace std;

int MAX_DISTFROMCENTER = 13;
int BASE_BOARDING = 33;
float UNLOAD_SCALING = 0.30;
float EVENT_SCALING = 0.15;
float DIST_SCALING = 0.25;
typedef pair<int, int> rpair;
rpair morning = rpair(420, 540);
rpair evening = rpair(960, 1140);
float RUSH_ON_SCALING = 0.6;
float RUSH_OFF_SCALING = 0.05;

eventLog::eventLog(std::string stationName, int time, int numBoard, int numDeboard, int numPassengers) :
        stationName(stationName), time(time), numBoard(numBoard), numDeboard(numDeboard), numPassengers(numPassengers) {}

Train::Train() {
    numPassengers = 0;
    efficiencyGrade = 1.0;
    delay = 0;
}

void Train::arriveAtStation(Station& station, int time) {
    // init numOn
    int numOn =  BASE_BOARDING - BASE_BOARDING * station.distFromCenter / (MAX_DISTFROMCENTER + 1);
    int numOff = numPassengers * UNLOAD_SCALING + numPassengers * DIST_SCALING * (1 - station.distFromCenter / (MAX_DISTFROMCENTER + 1));

    // check for event
    if (station.eventStation) {
        int eventStart = station.eventTime.first;
        int eventEnd = station.eventTime.second;
        int arriveRange = 60;
        int leaveRange = 20;
        if (eventStart - arriveRange <= time && time <= eventStart) {
            numOff += EVENT_SCALING * numOff;
        } else if (eventEnd <= time && time <= eventEnd + leaveRange) {
            numOn += EVENT_SCALING * numOn;
        }
    }

    // check time of day
    if (morning.first <= time && time <= morning.second) {
        numOn += numOn * RUSH_ON_SCALING;
        numOn -= numOn * abs(station.distFromCenter - MAX_DISTFROMCENTER / 2) / ((MAX_DISTFROMCENTER + 1) / 2) * 0.8;
        numOff += RUSH_OFF_SCALING * numOff * 1.0 / (station.distFromCenter + 1);
    } else if (evening.first <= time && time <= evening.second) {
        numOn += RUSH_ON_SCALING * numOn * 1.0 / (station.distFromCenter + 1);
        numOff += RUSH_OFF_SCALING * numOff;
        numOff -= numOff * abs(station.distFromCenter - MAX_DISTFROMCENTER / 2) / ((MAX_DISTFROMCENTER + 1) / 2) * 0.5;
    }

    // added some randomness
    numOff *= float(rand() % 40 + 80) / 100;
    numOn *= float(rand() % 40 + 80) / 100;

    if (numOff > numPassengers) {
        numOff = numPassengers;
    }

    // check if end station
    if (station.endStation && numPassengers != 0) {
        numOn = 0;
        numOff = numPassengers;
    }

    // log this particular event
    eventHist.push_back(new eventLog(station.name, time, numOn, numOff, numPassengers));

    numPassengers = numPassengers - numOff + numOn;
//    cout << "Time: " << time << " numOn: " << numOn << " numOff: " << numOff << " numPassengers: " << numPassengers << " Name: " << station.name << endl;
}

void Train::checkForDelay() {

}

std::vector<eventLog*> Train::getEventHist() {
    return eventHist;
}


Station::Station(string n, int time, int dist, bool end, bool event, int start, int stop) : name(n), timeToNext(time), distFromCenter(dist),
    endStation(end), eventStation(event), eventTime(pair<int, int>(start, stop)) {}


Line::Line(string n, string ev, int start, int stop) {
    name = n;
    eventStation = ev;
    eventStart = start;
    eventStop = stop;
    //initializeStations();
    genStations();
}


void Line::genStations() {

    typedef pair<string, int> spair; //<station name, time to next station>
    typedef vector<spair> spairvec;
    map<string, spairvec> lineInfo;


    //to insert into map,
    //spairvec v = ….///line info
    //lineInfo[this->name] = v;

    // Hard code
    static spairvec red;
    red.push_back(spair("Airport", 2));
    red.push_back(spair("College Park", 3));
    red.push_back(spair("East Point", 3));
    red.push_back(spair("Lakewood", 2));
    red.push_back(spair("Oakland City", 2));
    red.push_back(spair("West End", 2));
    red.push_back(spair("Garnett", 3));
    red.push_back(spair("Five Points", 1));
    red.push_back(spair("Peachtree Center", 1));
    red.push_back(spair("Civic Center", 2));
    red.push_back(spair("North Ave", 1));
    red.push_back(spair("Midtown", 2));
    red.push_back(spair("Arts Center", 4));
    red.push_back(spair("Lindbergh", 4));
    red.push_back(spair("Buckhead", 5));
    red.push_back(spair("Medical Center", 2));
    red.push_back(spair("Dunwoody", 2));
    red.push_back(spair("Sandy Springs", 2));
    red.push_back(spair("North Springs", 0));

    static spairvec gold;
    gold.push_back(spair("Airport", 2));
    gold.push_back(spair("College Park", 3));
    gold.push_back(spair("East Point", 3));
    gold.push_back(spair("Lakewood", 2));
    gold.push_back(spair("Oakland City", 2));
    gold.push_back(spair("West End", 2));
    gold.push_back(spair("Garnett", 3));
    gold.push_back(spair("Five Points", 1));
    gold.push_back(spair("Peachtree Center", 1));
    gold.push_back(spair("Civic Center", 2));
    gold.push_back(spair("North Ave", 1));
    gold.push_back(spair("Midtown", 2));
    gold.push_back(spair("Arts Center", 4));
    gold.push_back(spair("Lindbergh", 3));
    gold.push_back(spair("Lenox", 3));
    gold.push_back(spair("Brookhaven",4 ));
    gold.push_back(spair("Chamblee", 3));
    gold.push_back(spair("Doraville", 0));

    static spairvec blue;
    blue.push_back(spair("Hamilton E. Holmes", 3));
    blue.push_back(spair("West Lake", 3));
    blue.push_back(spair("Ashby", 1));
    blue.push_back(spair("Vine City", 1));
    blue.push_back(spair("Omni", 1));
    blue.push_back(spair("Five Points", 1));
    blue.push_back(spair("Georgia State", 2));
    blue.push_back(spair("King Memorial", 3));
    blue.push_back(spair("Inman Park", 2));
    blue.push_back(spair("Edgewood-Candler Park", 3));
    blue.push_back(spair("East Lake", 3));
    blue.push_back(spair("Decatur", 4));
    blue.push_back(spair("Avondale", 3));
    blue.push_back(spair("Kensington", 2));
    blue.push_back(spair("Indian Creek", 0));

    static spairvec green;
    green.push_back(spair("Bankhead", 4));
    green.push_back(spair("Ashby", 1));
    green.push_back(spair("Vine City", 1));
    green.push_back(spair("Omni", 1));
    green.push_back(spair("Five Points", 1));
    green.push_back(spair("Georgia State", 2));
    green.push_back(spair("King Memorial", 3));
    green.push_back(spair("Inman Park", 2));
    green.push_back(spair("Edgewood-Candler Park", 0));

    lineInfo["Red"] = red;
    lineInfo["Gold"] = gold;
    lineInfo["Blue"] = blue;
    lineInfo["Green"] = green;

    if (name == "Red")
        MAX_DISTFROMCENTER = 11;
    else if (name == "Gold")
        MAX_DISTFROMCENTER = 10;
    else if (name == "Blue")
        MAX_DISTFROMCENTER = 9;
    else if (name == "Green")
        MAX_DISTFROMCENTER = 4;

    // given a line string, generate array/vec of stations
    auto mit = lineInfo.find(name);
    int centerInd = 0;
    for (int i = 0; i < mit->second.size(); i++) {
        if (mit->second[i].first == "Five Points")
            centerInd = i;
    }

    for (int i = 0; i < mit->second.size(); i++) {
        string n = mit->second[i].first;
        int t = mit->second[i].second;
        int d = abs(i - centerInd);
        bool end = false;
        if (i == 0 || i == mit->second.size() - 1)
            end = true;
        bool ev = false;
        if (name == eventStation)
            ev = true;

        stations.push_back(Station(n, t, d, end, ev, eventStart, eventStop));
    }
}

vector<Station>* Line::getStations() {
    return &stations;
}
