#include <iostream>

using namespace std;

// Abstract class Counter
class Counter {
public:
    virtual void inc() = 0;
    virtual void dec() = 0;
    virtual operator int() = 0;
    virtual ~Counter() {};
};

// Derived class LimitedCounter
class LimitedCounter : public Counter {
public:
    LimitedCounter(int initial, int upper) : value(initial), upper_limit(upper) {}

    void inc() override {
        if (value < upper_limit) {
            ++value;
        }
    }

    void dec() override {
        if (value > 0) {
            --value;
        }
    }

    operator int() override {
        return value;
    }

private:
    int value;
    int upper_limit;
};

// Derived class OverflowCounter
class OverflowCounter : public Counter {
public:
    OverflowCounter(int initial, int upper) : value(initial), upper_limit(upper) {}

    void inc() override {
        if (value < upper_limit) {
            ++value;
        } else {
            value = 0;
        }
    }

    void dec() override {
        if (value > 0) {
            --value;
        } else {
            value = upper_limit;
        }
    }

    operator int() override {
        return value;
    }

private:
    int value;
    int upper_limit;
};

// Function to use the counter
void UseCounter(Counter& ctr, int num) {
    if (num > 0) {
        for (int i = 0; i < num; ++i) {
            ctr.inc();
        }
    } else {
        for (int i = 0; i < -num; ++i) {
            ctr.dec();
        }
    }
}

// Main function for testing
int main(int argc, char** argv) {
    LimitedCounter lc(0, 5);
    OverflowCounter oc(5, 9);

    cout << oc << endl;
    UseCounter(oc, 5);
    cout << oc << endl; // should display zero
    UseCounter(oc, -1);
    cout << oc << endl; // should display 9
    oc.dec();
    cout << oc << endl; // should display 8

    cout << lc << endl;
    lc.inc();
    cout << lc << endl;
    lc.dec();
    cout << lc << endl;
    for (int i = 0; i < 10; ++i) lc.inc();
    cout << lc << endl;
    UseCounter(lc, -9);
    cout << lc << endl;

    return 0;
}
