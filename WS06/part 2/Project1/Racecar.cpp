#include <iostream>
#include <string>
#include "Car.h"
#include "Racecar.h"
namespace sdds {
	// Almost forgot how to call the base constructor to build the subobject//
	Racecar::Racecar(std::istream& in):Car(in){
		// TD: need to consider the deliminator when it is a race car file//
		std::string tempBoost{};
		std::getline(in, tempBoost, '\n');
		m_booster = std::stod(tempBoost);
	}

	void Racecar::display(std::ostream& out) const{
		Car::display(out);
		out << "*\n";
	}

	double Racecar::topSpeed() const{
		return (1.0+m_booster)*topSpeed();
	}


}
