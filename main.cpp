#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include "MakeEvent.h"
#include "Objects.h"

using namespace std;

void sayHello() {
    std::cout << "sayHello\n";
}

void sayGoodbye(int a) {
    std::cout << "sayHello " << a << "\n";
}

void sayHello2(const std::string& a, const std::string& b) {
    std::cout << "Hello " << a << " and " << b << "\n";
}

void sumIt(int a, int b, int c, int d) {
    std::cout << "The sum is " << a + b + c + d << "!\n";
}

class Dog {
public:
    Dog(std::string n) : name(n) {}

    void woof() { std::cout << "Woof\n"; }

    void barkNTimes(int a) {
        for(int i = 0; i < a; i++) {
            std::cout << "Bark! ";
        }
        std::cout << std::endl;
    }

    void addThem(double a, double b) {
        std::cout << "The dog says, 'The sum is " << a + b << "!'\n";
    }

private:
    std::string name;

};


int main() {
//    Event* a = MakeEvent(&sayHello);
//    Event* b = MakeEvent(&sayGoodbye, 2);
//    Event* c = MakeEvent(&sayHello2, "Bobby", "Alice");
//    Event* d = MakeEvent(&sumIt, 5, 3, 1, 4);
//
//    Dog* myDog = new Dog("Barney");
//
//    Event* e = MakeEvent(&Dog::woof, myDog);
//    Event* f = MakeEvent(&Dog::barkNTimes, myDog, 5);
//    Event* g = MakeEvent(&Dog::addThem, myDog, 2.2, 7.0);
//
//    std::cout << "Start the invokes\n";
//
//    a->Invoke();
//    b->Invoke();
//    c->Invoke();
//    d->Invoke();
//    e->Invoke();
//    f->Invoke();
//    g->Invoke();

    Line line("Gold");
    vector<Station> s = line.getStations();
    Train t1;
    int time = 1020; // 6:50
    for (int i = 0; i < s.size(); i++) {
        t1.arriveAtStation(s[i], time);
        time += s[i].timeToNext;
    }

    return 0;
}
