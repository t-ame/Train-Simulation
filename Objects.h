//
// Created by Noah Roberts on 4/14/18.
//

#ifndef MARTA_SIM_OBJECTS_H
#define MARTA_SIM_OBJECTS_H

#include <string>
#include <vector>

class Station;

class Train {
public:
    Train();
    void arriveAtStation(Station station, int time);
    void checkForDelay();

private:
    int numPassengers;
    int efficiencyGrade;
    int delay;
};


class Station {
public:
    Station(std::string n, int time, int dist, bool end, bool event);

private:
    std::string name;
    int timeToNext;
    int distFromCenter;
    bool endStation;
    bool eventStation;
};


class Line {
public:
    Line(std::string n);
    void genStations();

private:
    std::string name;
    std::vector<Station> stations;
};


#endif //MARTA_SIM_OBJECTS_H
