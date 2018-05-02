#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "MakeEvent.h"
#include "Objects.h"

std::queue<Event*>* buildEventQueue(Train* t, Line* l, int time) {
    std::vector<Station> stations = l->getStations();

    auto* q = new std::queue<Event*>();
    for (const auto &station : stations) {
        q->push(MakeEvent(&Train::arriveAtStation, t, station, time));
        time = (time + station.timeToNext) % (24 * 60);
    }

    return q;
}


void runSimulation(std::string lineName, int time) {
    Line* line = new Line(std::move(lineName));
    auto* simTrain = new Train();
    std::queue<Event*>* eventQueue = buildEventQueue(simTrain, line, time);

    while (!eventQueue->empty()) {
        eventQueue->front()->Invoke();
        eventQueue->pop();
    }
}