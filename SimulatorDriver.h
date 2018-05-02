#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "MakeEvent.h"
#include "Objects.h"

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

std::queue<Event*>* buildEventQueue(Train* t, Line* l, int time) {
    std::vector<Station>* stations = l->getStations();
    auto* q = new std::queue<Event*>();

    int stopTime = time + 24 * 60;
    int timeNoMod = time;
    do {
        std::vector<Station>::iterator iterF;
        for (iterF = stations->begin(); iterF != stations->end(); iterF++) {
            q->push(MakeEvent(&Train::arriveAtStation, t, *iterF, time));
            time = (time + iterF->timeToNext) % (24 * 60);
            timeNoMod += iterF->timeToNext;
        }
        std::vector<Station>::reverse_iterator iterR;
        for (iterR = stations->rbegin(); iterR != stations->rend(); iterR++) {
            q->push(MakeEvent(&Train::arriveAtStation, t, *iterR, time));
            time = (time + iterR->timeToNext) % (24 * 60);
            timeNoMod += iterR->timeToNext;
        }
    } while(timeNoMod < stopTime);

    return q;
}


std::vector<eventLog*> runSimulation(std::string lineName, int time) {
    Line* line = new Line(std::move(lineName));
    Train simTrain;
    std::queue<Event*>* eventQueue = buildEventQueue(&simTrain, line, time);

    while (!eventQueue->empty()) {
        eventQueue->front()->Invoke();
        eventQueue->pop();
    }

    return simTrain.getEventHist();
}