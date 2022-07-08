/*
    Course_Name:	OOP 345
    Section:		A
    Title:			Workshop 6 Part 2
    Module:			Utilities
    File_Name:		Utilities.cpp
    Student_Name:	Zhaokai_Guan
    Student_ID:		130988215
*/
#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#include "Racecar.h"
#include "Utilities.h"
namespace sdds {
    Vehicle* createInstance(std::istream& in){
        Vehicle* res{};
        //remove the white spaces before the tag//
        while (in.peek() == ' ') {
            in.ignore();
        }
        char tag = in.peek();
        if (tag =='c'|| tag =='C'){
            res = new Car(in);
        }
        else if (tag == 'r' || tag == 'R'){
            res = new Racecar(in);
        }
        else{
            in.ignore(1000, '\n');
            throw tag;
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
