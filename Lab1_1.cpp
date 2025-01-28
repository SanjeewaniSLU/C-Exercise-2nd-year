#include <iostream>
#include <vector>

int main(){

    std::vector<int> nrs;
    int count;

    std::cout << " How many numbers do you want enter? ";
    std::cin >>count;

    for(int i=0; i < count; ++i){
        int nr;
        std::cout << "Enter nr ["<< i+1 <<"]: ";
        std::cin >> nr;
        nrs.push_back(nr);
    }
    std::cout << "You entered: ";
    for (int i = 0; i < nrs.size(); ++i) {
        std::cout << nrs[i];
        if (i < nrs.size() - 1) {
            std::cout << ", ";
        }
    }
}






