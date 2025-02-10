#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>


class House{
public:
    House(const std::string& addr, double sz, double pr)
        :address(addr),size(sz),price(pr){}

    friend std::ostream& operator << (std::ostream& os, const House& house);

    bool operator<(const House& other) const{
        return (price / size) < (other.price / other.size);
    }

    void setAddress(const std::string& addr){
        address = addr;
    }

    std::string getAddress() const{
        return address;
    }

    void setArea (double sz){
        size =sz;
    }

    void setPrice(double pr){
        price = pr;
    }

private:
    std::string address;
    double size;
    double price;
};

std::ostream& operator << (std::ostream& os, const House& house){
    os << "Address : " << house.address << "Size : " << house.size <<" m^2 ,Price : " << house.price <<" euros.";
    return os;
}

class Apartment{

public:
    Apartment(std::shared_ptr<House> h,int aprtNum,double s,double r)
    :house(h),apartmentNumber(aprtNum),size(s),monthlyRent(r){}

    bool operator <(const Apartment& other) const{
        return monthlyRent < other.monthlyRent;
    }

    void printDetails()const{
        std::cout << " Address : " << house->getAddress() << ", Apartment Number : " << apartmentNumber
        << ", Size of the apartment: " << size << "m^2, The monthly rent : " << monthlyRent << " euros" << std::endl;
    }

private:
    std::shared_ptr<House> house;
    int apartmentNumber;
    double size;
    double monthlyRent;

};


int main(){
    auto house1 = std::make_shared<House>("Kilonportti 1 A 020", 300.0, 200000.0);
    auto house2 = std::make_shared<House>("Kilonrinne 10 B 036",230.0,150000.0);

    std::vector<Apartment> apartments = {
        Apartment(house1, 1, 50, 1000),
        Apartment(house1, 2, 60, 1200),
        Apartment(house1, 3, 45, 900),
        Apartment(house2, 1, 55, 1100),
        Apartment(house2, 2, 65, 1300),
        Apartment(house2, 3, 50, 1050),
        Apartment(house2, 4, 70, 1400)
    };
    std::sort(apartments.begin(), apartments.end());

    for (const auto& apt : apartments) {
        apt.printDetails();
    }
}