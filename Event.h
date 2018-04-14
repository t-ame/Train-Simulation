#pragma once

class Event {
public:
    void Invoke() {
        Notify();
    }

protected:
    virtual void Notify() = 0;
};