#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Utilities.h"
namespace sdds {
    Vehicle* createInstance(std::istream& in){
        Vehicle* res{};
        if (in.peek()=='c'||in.peek()=='C'){
            in.ignore(2);
            res = new Car(in);
        }
        return res;
    }
    std::string& guansTrimmerV3(std::string& src) {
        if (src.c_str()) {
            src.erase(0, src.find_first_not_of(' '));
            src.erase(src.find_last_not_of(' ') + 1);
        }
        return src;
    }
}
