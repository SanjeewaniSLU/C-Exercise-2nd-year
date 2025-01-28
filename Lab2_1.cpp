#include <iostream>
#include <string>
#include <sstream>


int main(){
    std::string line;

    while (true){

        std::cout << "Enter a line with numbers or \"stop\": ";
        std::getline(std::cin,line);

        if (line.substr(0,4) == "stop")
        {
            break;
        }

        std::istringstream inputStream(line);

        int number, sum = 0,count = 0;

        while (inputStream >> number)
        {
            sum += number;
            count++;
        }
        std::cout << "Total of " << count << " numbers is "<< sum << std::endl;
        }

    return 0;
}