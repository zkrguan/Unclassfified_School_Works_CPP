#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Utilities.h"
namespace sdds {
    Vehicle* createInstance(std::istream& in){
        Vehicle* res{};
        //remove the white spaces before the tag//
        while (in.peek() == ' ') {
            in.ignore();
        }
        if (in.peek()=='c'||in.peek()=='C'){
            res = new Car(in);
        }
        return res;
    }
    // my old trimmer funciton with a slight adjustment//
    std::string& guansTrimmerV3(std::string& src) {
        if (src.c_str()) {
            src.erase(0, src.find_first_not_of(' '));
            src.erase(src.find_last_not_of(' ') + 1);
        }
        return src;
    }
}
