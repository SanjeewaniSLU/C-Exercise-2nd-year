#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class Item{
public:
    Item( ) : name("" ),weight(0),price(0.0),count(0){}
    Item(const std::string& n, int w, double p, int c): name(n),weight(w),price(p),count(c){}

    friend std::ostream& operator<<(std::ostream& os,const Item& item);
    friend std::istream& operator>>(std::istream& is, Item& item);

    bool operator < (const Item& other) const{
        double price_kg = price / (weight /1000.0);
        double otherPrice_kg = other.price /(other.weight / 1000.0);
        return price_kg < otherPrice_kg;
    }

    int getCount() const{
        return count;
    }
    void setCount(int c) {
        count = c;
    }
    double getPrice() const{
        return price;
    }
    void setPrice(double p){
        price = p;
    }

private:
    std::string name;
    int weight;
    double price;
    int count;
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "{ \"Name\":\"" << item.name
       << "\",\"Weight\":" << item.weight
       << ",\"Price\":" << item.price
       << ",\"Count\":" << item.count
       << "}";
    return os;
}

std::istream& operator>>(std::istream& is, Item& item){
    std::string my_str;

    try
    {
        std::getline(is,my_str,'{');

        std::getline(is,my_str,':');
        if (my_str.find("\"Name\"") == std::string::npos){
            std::cerr << "Error: Invalid or Missing \"Name\" field." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        char next_char;
        is >> next_char;
        if (next_char != '"') {
            std::cerr << "Error: Name value must start with a quote." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is,item.name,'"');

        if (item.name.empty()) {
            std::cerr << "Error: \"Name\" field cannot be empty." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        if (std::all_of(item.name.begin(), item.name.end(), [](char c) { return std::isspace(c); })) {
            std::cerr << "Error: \"Name\" field cannot contain only whitespace." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        is >> next_char;
        if (next_char != ',') {
            std::cerr << "Error: Expected comma after Name value." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is,my_str,':');
        if(!(is >> item.weight)){
            std::cerr << "Error: Invalid or missing \"Weight\" field." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is,my_str,':');
        if (!(is >> item.price)){
            std::cerr << "Error: Invalid or missing \"Price\" field." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is,my_str,':');
        if(!(is >> item.count)){
            std::cerr << "Error: Invalid or missing \"Count\" field." << std::endl;
            is.setstate(std::ios::failbit);
            return is;
        }

        std::getline(is,my_str,'}');
    } catch (...){
        std::cerr << "Error: Exception occurred while parsing JSON input." << std::endl;
        is.setstate(std::ios::failbit);
    }

    return is;
}

int main()
{
    std::vector<Item> items;
    std::string input;
    bool end = false;

    while(!end){
        std::cout << "Enter item name or 'stop' to end, 'json' for JSON format:";
        std::getline(std::cin, input);

        if (input == "stop"){
            end = true;
        }else if (input == "json"){
            bool validJson = false;
            while (!validJson) {
                std::cout << "Enter item details in JSON format: ";
                Item item;
                std::cin >> item;
                std::cin.ignore();
                if (!std::cin.fail()) {
                    items.push_back(item);
                    validJson = true;
                } else {
                    std::cin.clear();
                    std::cerr << "Invalid JSON format. Please try again." << std::endl;
                }
            }
        }else{
            int weight,count ;
            double price;

            std::cout << "Enter weight (g): ";
            std::cin >> weight;
            std::cout << "Enter price (€): ";
            std::cin >> price;
            std::cout << "Enter count: ";
            std::cin >> count;
            std::cin.ignore();
            items.push_back(Item(input, weight, price, count));
        }
    }
    std::sort(items.begin(), items.end());

    std::cout << "\nSorted Items:\n";
    double netWorth = 0.0;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i << ": " << items[i] << std::endl;
        netWorth += items[i].getPrice() * items[i].getCount();
    }
    std::cout << "Net worth of stock: " << netWorth << " euros\n";


    bool update = true;
    while (update)
    {
        std::cout << "\nEnter the index of the item to update (or 'exit' to quit):";
        std::getline(std::cin,input);

        if (input == "exit"){
            update = false;
        }else{
            try{
                int index = std::stoi(input);
                if (index >= 0 && index < items.size()) {
                    double newPrice;
                    std::cout << "Enter new price: ";
                    std::cin >> newPrice;
                    items[index].setPrice(newPrice);
                    std::cin.ignore();

                    std::sort(items.begin(), items.end());
                    std::cout << "\nUpdated Sorted Items:\n";
                    netWorth = 0.0;
                    for (size_t i = 0; i < items.size(); ++i) {
                        std::cout << i << ": " << items[i] << std::endl;
                        netWorth += items[i].getPrice() * items[i].getCount();
                    }
                    std::cout << "Net worth of stock: " << netWorth << " euros\n";
                } else {
                    std::cerr << "Invalid index. Please try again." << std::endl;
                }
            }catch (std::invalid_argument&)
            {
                std::cerr << "Invalid input. Please enter a valid index or 'exit'." << std::endl;
            }

        }

    }
    return 0;
}