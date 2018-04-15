//
// Created by Noah Roberts on 4/14/18.
//

#include "Objects.h"
#include <utility>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;


Train::Train() {

}

void Train::arriveAtStation(Station station, int time) {

}

void Train::checkForDelay() {

}


Station::Station(string n, int time, int dist, bool end, bool event) : name(n), timeToNext(time), distFromCenter(dist),
    endStation(end), eventStation(event) {}


Line::Line(string n, string ev) {
    name = n;
    eventStation = ev;
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
    spairvec red;
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

    spairvec gold;
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

    spairvec blue;
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

    spairvec green;
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

        stations.push_back(Station(n, t, d, end, ev));
    }
}

std::vector<Station> Line::getStations() {
    return stations;
}
