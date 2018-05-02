//
// Created by Noah Roberts on 4/14/18.
//

#ifndef MARTA_SIM_OBJECTS_H
#define MARTA_SIM_OBJECTS_H

#include <string>
#include <vector>

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

struct eventLog {
    std::string stationName;
    int time;
    int numBoard;
    int numDeboard;
    int numPassengers; // on arrival

    eventLog(std::string stationName="", int time=0, int numBoard=0, int numDeboard=0, int numPassengers=0);
};

class Station;

class Train {
public:
    Train();
    void arriveAtStation(Station& station, int time);
    void checkForDelay();
    std::vector<eventLog*> getEventHist();

private:
    int numPassengers;
    double efficiencyGrade;
    int delay; // minutes
    std::vector<eventLog*> eventHist;
};


class Station {
public:
    Station(std::string n, int time, int dist, bool end, bool event, int start, int stop);

    std::string name;
    int timeToNext;
    int distFromCenter;
    bool endStation;
    bool eventStation;
    std::pair<int, int> eventTime;
};


class Line {
public:
    Line(std::string n, std::string ev = "", int start = -1, int stop = -1);
    void genStations();
    std::vector<Station>* getStations();

private:
    std::string name;
    std::vector<Station> stations;
    std::string eventStation;
    int eventStart;
    int eventStop;
};


#endif //MARTA_SIM_OBJECTS_H
