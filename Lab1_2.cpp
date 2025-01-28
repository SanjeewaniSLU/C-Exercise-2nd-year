#include <iostream>
#include <string>
#include <algorithm>

void replaceCharacter(std::string &str , char ch){
    std::replace(str.begin(),str.end(),ch,'_');
}


int main(){
    std::string inputStr;
    std::string replaceCh;
    while (true){

        std::cout << " Enter a string: ";
        std::getline(std::cin,inputStr);

        std::cout << "Enter a character to replace or \"stop\": ";
        std::getline(std::cin,replaceCh);

        if (replaceCh == "stop")
        {
            break;
        }

        if (!replaceCh.empty()){
            char x = replaceCh[0];
            replaceCharacter(inputStr,x);
            std::cout << "Result : " << inputStr << std::endl;
        }
    }
    return 0;
}