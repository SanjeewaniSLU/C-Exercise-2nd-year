#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>

using namespace std;

class RandGen_2 {
public:
    RandGen_2(int min, int max) : min_val(min), max_val(max) {
        srand(time(NULL));
    }
    int operator()() {
        int total = max_val - min_val + 1;
        if (numbers.size() >= total) {
            throw runtime_error("Unable to produce unique random number");
        }
        int number;
        do {
            number = rand() % (max_val - min_val + 1) + min_val;
        } while (find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        return number;
    }
private:
    int min_val;
    int max_val;
    vector<int> numbers;
};

void test_generator(RandGen_2 ur, int count) {
    cout << "Generating numbers:" << endl;
    vector<int> generated;
    try {
        for (int i = 0; i < count; ++i) {
            generated.push_back(ur());
        }
    } catch (const runtime_error& e) {
        cout << "Exception: " << e.what() << ". Tried to generate " << count
             << " random numbers. Got only " << generated.size() << endl;
    }
    for (int num : generated) {
        cout << num << endl;
    }
    cout << "End of generator" << endl;
}

int main() {
    RandGen_2 randGen(5, 13);
    test_generator(randGen, 6);
    test_generator(randGen, 9);
    test_generator(randGen, 13);

    RandGen_2 randGen2(1, 35);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 70);

    return 0;
}