#pragma once

#include "Event.h"

template<typename MEM, typename OBJ>
Event* MakeEvent(MEM member, OBJ obj);

template<typename MEM, typename OBJ, typename T1>
Event* MakeEvent(MEM member, OBJ obj, T1 a1);

template<typename MEM, typename OBJ, typename T1, typename T2>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2);

template<typename MEM, typename OBJ, typename T1, typename T2, typename T3>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2, T3 a3);

template<typename MEM, typename OBJ, typename T1, typename T2, typename T3, typename T4>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2, T3 a3, T4 a4);

Event* MakeEvent(void(*f)(void));

template<typename U1, typename T1>
Event* MakeEvent(void(*f)(U1), T1 a1);

template<typename U1, typename U2, typename T1, typename T2>
Event* MakeEvent(void(*f)(U1, U2), T1 a1, T2 a2);

template<typename U1, typename U2, typename U3, typename T1, typename T2, typename T3>
Event* MakeEvent(void(*f)(U1, U2, U3), T1 a1, T2 a2, T3 a3);

template<typename U1, typename U2, typename U3, typename U4, typename T1, typename T2, typename T3, typename T4>
Event* MakeEvent(void(*f)(U1, U2, U3, U4), T1 a1, T2 a2, T3 a3, T4 a4);

/******************************************************************************************/

template<typename MEM, typename OBJ>
Event* MakeEvent(MEM member, OBJ obj) {
    class EventObj0 : public Event {
    public:
        EventObj0(OBJ o, MEM m) :
                m_obj(o),
                m_function(m) {
            std::cout << "EventMem0\n";
        }
    protected:
        void Notify() override {
            (m_obj->*m_function)();
        }
    private:
        OBJ m_obj;
        MEM m_function;
    };
    return new EventObj0(obj, member);
};

template<typename MEM, typename OBJ, typename T1>
Event* MakeEvent(MEM member, OBJ obj, T1 a1) {
    class EventObj1 : public Event {
    public:
        EventObj1(OBJ o, MEM m, T1 a) :
                m_obj(o),
                m_function(m),
                m_a(a) {
            std::cout << "EventMem1\n";
        }

    protected:
        void Notify() override {
            (m_obj->*m_function)(m_a);
        }
    private:
        OBJ m_obj;
        MEM m_function;
        T1 m_a;
    };
    return new EventObj1(obj, member, a1);
};

template<typename MEM, typename OBJ, typename T1, typename T2>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2) {
    class EventObj2 : public Event {
    public:
        EventObj2(OBJ o, MEM m, T1 a, T2 b) :
                m_obj(o),
                m_function(m),
                m_a(a),
                m_b(b) {
            std::cout << "EventMem2\n";
        }
    protected:
        void Notify() override {
            (m_obj->*m_function)(m_a, m_b);
        }
    private:
        OBJ m_obj;
        MEM m_function;
        T1 m_a;
        T2 m_b;
    };
    return new EventObj2(obj, member, a1, a2);
};

template<typename MEM, typename OBJ, typename T1, typename T2, typename T3>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2, T3 a3) {
    class EventObj3 : public Event {
    public:
        EventObj3(OBJ o, MEM m, T1 a, T2 b, T3 c) :
                m_obj(o),
                m_function(m),
                m_a(a),
                m_b(b),
                m_c(c) {
            std::cout << "EventMem3\n";
        }
    protected:
        void Notify() override {
            (m_obj->*m_function)(m_a, m_b, m_c);
        }
    private:
        OBJ m_obj;
        MEM m_function;
        T1 m_a;
        T2 m_b;
        T3 m_c;
    };
    return new EventObj3(obj, member, a1, a2, a3);
};

template<typename MEM, typename OBJ, typename T1, typename T2, typename T3, typename T4>
Event* MakeEvent(MEM member, OBJ obj, T1 a1, T2 a2, T3 a3, T4 a4) {
    class EventObj4 : public Event {
    public:
        EventObj4(OBJ o, MEM m, T1 a, T2 b, T3 c, T4 d) :
                m_obj(o),
                m_function(m),
                m_a(a),
                m_b(b),
                m_c(c),
                m_d(d)
        {
            std::cout << "EventMem4\n";
        }
    protected:
        void Notify() override {
            (m_obj->*m_function)(m_a, m_b, m_c, m_d);
        }
    private:
        OBJ m_obj;
        MEM m_function;
        T1 m_a;
        T2 m_b;
        T3 m_c;
        T4 m_d;
    };
    return new EventObj4(obj, member, a1, a2, a3, a4);
};


/****************************************************************************************************/

Event* MakeEvent(void(*f)()) {
    class EventFunc0 : public Event {
    public:
        typedef void(*F)();

        EventFunc0(F function) :
            m_function(function)
        {
            std::cout << "EventFunc0\n";
        }
    protected:
        void Notify() override {
            (*m_function)();
        }
    private:
        F m_function;
    };
    return new EventFunc0(f);
}

template<typename U1, typename T1>
Event* MakeEvent(void(*f)(U1), T1 a1) {
    class EventFunc1 : public Event {
    public:
        typedef void(*F)(U1);

        EventFunc1(F function, T1 a):
            m_function(function),
            m_a(a) {

            std::cout << "EventFunc1\n";
        }
    protected:
        void Notify() override {
            (*m_function)(m_a);
        }
    private:
        F m_function;
        T1 m_a;
    };
    return new EventFunc1(f, a1);
}

template<typename U1, typename U2, typename T1, typename T2>
Event* MakeEvent(void(*f)(U1, U2), T1 a1, T2 a2) {
    class EventFunc2 : public Event {
    public:
        typedef void(*F)(U1, U2);

        EventFunc2(F function, T1 a, T2 b):
                m_function(function),
                m_a(a),
                m_b(b)
        {
            std::cout << "EventFunc2\n";
        }
    protected:
        void Notify() override {
            (*m_function)(m_a, m_b);
        }
    private:
        F m_function;
        T1 m_a;
        T2 m_b;
    };
    return new EventFunc2(f, a1, a2);
}

template<typename U1, typename U2, typename U3, typename T1, typename T2, typename T3>
Event* MakeEvent(void(*f)(U1, U2, U3), T1 a1, T2 a2, T3 a3) {
    class EventFunc3 : public Event {
    public:
        typedef void(*F)(U1, U2, U3);

        EventFunc3(F function, T1 a, T2 b, T3 c):
                m_function(function),
                m_a(a),
                m_b(b),
                m_c(c)
        {
            std::cout << "EventFunc3\n";
        }
    protected:
        void Notify() override {
            (*m_function)(m_a, m_b, m_c);
        }
    private:
        F m_function;
        T1 m_a;
        T2 m_b;
        T3 m_c;
    };
    return new EventFunc3(f, a1, a2, a3);
}

template<typename U1, typename U2, typename U3, typename U4, typename T1, typename T2, typename T3, typename T4>
Event* MakeEvent(void(*f)(U1, U2, U3, U4), T1 a1, T2 a2, T3 a3, T4 a4) {
    class EventFunc4 : public Event {
    public:
        typedef void(*F)(U1, U2, U3, U4);

        EventFunc4(F function, T1 a, T2 b, T3 c, T4 d):
                m_function(function),
                m_a(a),
                m_b(b),
                m_c(c),
                m_d(d)
        {
            std::cout << "EventFunc4\n";
        }
    protected:
        void Notify() override {
            (*m_function)(m_a, m_b, m_c, m_d);
        }
    private:
        F m_function;
        T1 m_a;
        T2 m_b;
        T3 m_c;
        T4 m_d;
    };
    return new EventFunc4(f, a1, a2, a3, a4);
}