//
// Created by Noah Roberts on 4/14/18.
//

#ifndef MARTA_SIM_OBJECTS_H
#define MARTA_SIM_OBJECTS_H

#include <string>

class Train {
public:
private:
    int numPassengers;
    int efficiencyGrade;
};


class Station {
public:
private:
    int timeToNext;
    int distFromCenter;
    bool endStation;
    bool eventStation;
};


class Line {
public:
private:
    std::string name;
    Station stations[];
};


#endif //MARTA_SIM_OBJECTS_H
