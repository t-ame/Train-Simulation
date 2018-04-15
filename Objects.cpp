//
// Created by Noah Roberts on 4/14/18.
//

#include "Objects.h"
#include <utility>
#include <map>
#include <vector>

using namespace std;


Train::Train() {

}

void Train::arriveAtStation(Station station, int time) {

}

void Train::checkForDelay() {

}


Station::Station(string n, int time, int dist, bool end, bool event) {

}


Line::Line(string n) {

}

void Line::genStations() {

    typedef pair<string, int> spair;
    typedef vector<spair> spairvec;
    map<string, spairvec> lineInfo;

    //to insert into map,
    //spairvec v = ….///line info
    //lineInfo[this->name] = v;

    // Hard code
    spairvec red;
    red.push_back(spair("test", 4));
    // TODO: hard-code all of this
    spairvec gold;
    spairvec blue;
    spairvec green;

    lineInfo["Red"] = red;
    lineInfo["Gold"] = gold;
    lineInfo["Blue"] = blue;
    lineInfo["Green"] = green;

    // given a line string, generate array/vec of stations
    
}
