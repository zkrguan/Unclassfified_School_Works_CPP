/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Racecar
	File_Name:		Racecar.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#include <iostream>
#include <string>
#include "Car.h"
#include "Racecar.h"
namespace sdds {
	// Almost forgot how to call the base constructor to build the subobject//
	Racecar::Racecar(std::istream& in):Car(in){
		std::string tempBoost{};
		std::getline(in, tempBoost, '\n');
		m_booster = std::stod(tempBoost);
	}

	void Racecar::display(std::ostream& out) const{
		Car::display(out);
		out << "*";
	}

	double Racecar::topSpeed() const{
		return (1.0+m_booster)*Car::topSpeed();
	}


}
