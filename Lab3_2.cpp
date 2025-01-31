#include <iostream>
#include <deque>

class RunningAverage{
private:
    std::deque<int> values;
    int max_size;


public:
    RunningAverage(int size):max_size(size){}
    void add_value(int value);
    double get_average();
};

void RunningAverage::add_value(int value){
    if(values.size() == max_size){
        values.pop_front();
    }
    values.push_back(value);
}

double RunningAverage::get_average(){
    if(values.empty())
    {
        return 0.0;
    }
    double sum = 0;
    for (int val:values)
    {
        sum += val;
    }
    return sum / values.size();
};

int main() {
    RunningAverage avg(5);
    int input;
    bool end = false;

    while (!end){
        std::cout << "Enter a number (0 to stop): ";
        std::cin >> input;

        if (input == 0) {
            std::cout << "Current running average: " << avg.get_average() << std::endl;
            end = true;
        }else{

            avg.add_value(input);
            std::cout << "Current running average: " << avg.get_average() << std::endl;
        }
    }

    return 0;
}
