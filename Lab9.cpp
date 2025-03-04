#include <string>
#include <iostream>
#include <vector>

class Observer {
public:
    virtual void Update() = 0;
};
class Subject {
public:
    virtual void Attach(Observer *o) = 0;
    virtual void Notify() = 0;
};


class Person {
public:
    Person(const char* name = "nobody") : name(name) {}
    virtual ~Person() = default;
    virtual void identity() const {
        std::cout << "My name is: " << name << std::endl;
    }
    virtual void interrogate(){}

private:
    std::string name;
};


class Spy : public Person,public Subject{
public:
    Spy(const char* real_name, const char* alias, int resistance)
        : Person(real_name), alias(alias), resistance(resistance) {}

    void set_identity(const char* alias) {
        this->alias = alias;
    }

    void identity() const override {
        if (resistance > 0) {
            std::cout << "My name is: " << alias << std::endl;
        } else {
            Person::identity();
            std::cout << "My alias is: " << alias << std::endl;
        }
    }
    void interrogate() override {
        if(resistance > 0){
            resistance--;
            if (resistance == 0) {
                Notify();
            }
        }
    }

    void Attach(Observer* o) override {
        observers.push_back(o);
    }

    void Notify() override {
        for (Observer* observer : observers) {
            observer->Update();
        }
    }
private:
    std::string alias;
    int resistance;
    std::vector<Observer*> observers;
};

class Judge : public Person,public  Observer{
public:
    Judge(const char* name) : Person(name) {}

    void Update() override {
        identity();
        std::cout << "I'm sending a spy to prison!" << std::endl;
    }
};

int main(int argc, char** argv){
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);
    Judge judge("Judge Barnhill");
    spy.Attach(&judge);
    spy2.Attach(&judge);

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();

    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();

    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }

    return 0;
}

