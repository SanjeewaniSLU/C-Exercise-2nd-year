#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){
    map < string, int> mp;
    string input;
    int integer = 0;
    bool end = false;

    while(!end){
        cout << " Enter name or \"stop\" or \"print\" : " ;
        cin >> input;

        if(input == "stop"){
            end = true;
        }
        else if(input == "print"){
            for (auto it = mp.begin();it != mp.end();++it){
                cout << it->first << ":" << it->second <<endl;
            }
        }
        else{
            cout << "Enter an integer :";
            cin >> integer;
            mp[input] = integer;
        }
    }
    return 0;
}

