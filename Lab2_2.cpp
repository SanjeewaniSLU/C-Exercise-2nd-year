#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

int main(){

    std::vector<std::string> dirNames;
    std::string input;


    std::cout << " Enter directory names or enter a blank line to stop entry: "<<std::endl;;
    while (true){
        std::getline(std::cin,input);
        if(input.empty()){
            break;
        }
        dirNames.push_back(input);
    }

    std::string relativePath;
    for (const auto& dir : dirNames) {
        if (!relativePath.empty()) {
            relativePath += "/";
        }
        relativePath += dir;
    }

    std::filesystem::create_directories(relativePath);

    std::string lastFilePath = relativePath + "/result.txt";
    std::ofstream resultFile(lastFilePath);

    std::filesystem::path absolutePath = std::filesystem::absolute(lastFilePath);

    std::cout << "Absolute path to the file: " << absolutePath << std::endl;
    resultFile << "Absolute path to the file: " << absolutePath << std::endl;

    resultFile << "Content of the string vector:" << std::endl;
    for (const auto& dir : dirNames) {
        resultFile << dir << std::endl;
    }

    std::cout << "Relative path to the file: " << relativePath << std::endl;
    resultFile << "Relative path to the file: " << relativePath << std::endl;

    return 0;
}
