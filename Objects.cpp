//
// Created by Noah Roberts on 4/14/18.
//

#include "Objects.h"
#include <utility>
#include <map>


Train::Train() {

}

void Train::arriveAtStation(Station station, int time) {

}

void Train::checkForDelay() {

}


Station::Station(std::string n, int time, int dist, bool end, bool event) {

}


Line::Line(std::string n) {

}

void Line::genStations() {
    std::pair<std::string, int> SPAIR;

    typedef std::pair<string, int> spair;
    typedef std::vector<spair> spairvec;
    std::map<string, spairvec> lineInfo;

    //to insert into map,
    //spairvec v = ….///line info
    //lineInfo[this->name] = v;

    // Hard code
    SPAIR red[] =

}
