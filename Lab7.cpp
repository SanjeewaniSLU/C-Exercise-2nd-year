#include <string>
#include <iostream>

class Person {
public:
    Person(const char* name = "nobody") : name(name) {}
    virtual ~Person() = default;
    virtual void identity() const {
        std::cout << "My name is: " << name << std::endl;
    }
    virtual void interrogate() {
        std::cout << getName() << " is being interrogated." << std::endl;
    }
    std::string getName() const { return name; }
private:
    std::string name;
};

class Spy : public Person {
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
            std::cout << "My name is: " << getName() << std::endl;
            std::cout << "My alias is: " << alias << std::endl;
        }
    }

    void interrogate() override {
        if (resistance > 0) {
            resistance--;
        }
    }

private:
    std::string alias;
    int resistance;
};

int main(int argc, char** argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);

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