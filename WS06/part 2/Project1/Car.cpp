#include <iostream>
#include <iomanip>
#include <string>
#include "Car.h"
#include "Utilities.h"

namespace sdds {
	Car::Car(std::istream& istr){
		char tag = istr.peek();
		// ignore the comma and space
		while (istr.peek() == ',' || istr.peek() == ' ') {
			istr.ignore();
		}
		// taking in the maker
		std::getline(istr, m_Maker, ',');
		guansTrimmerV3(m_Maker);
		// remove all spaces before the actual condition//
		// using peek to check the next char is comma//
		if (istr.peek()==','){
			// if next char is comma, the condition will be set to ! to present the wrong state
			m_Condition = '!';
		}
		else if (istr.peek() == ' ') {
			//ignore the space//
			istr.ignore();
			// not equal to , means there isn't just a space in this field//
			if (istr.peek() != ','){
				istr.get(m_Condition);
			}
			else{
				m_Condition = 'n';
			}
		}
		// ignore the comma and space
		while (istr.peek() == ',' || istr.peek() == ' ') {
			istr.ignore();
		}
		// taking in the top-speed
		// based on the tag
		std::string temp_Speed{};
		if (tag=='c'||tag=='C'){
			std::getline(istr, guansTrimmerV3(temp_Speed), '\n');
		}
		else if(tag=='r'||tag=='R') {
			// prepare for reading the boost//
			std::getline(istr, guansTrimmerV3(temp_Speed), ',');
			while (istr.peek() == ',' || istr.peek() == ' ') {
				istr.ignore();
			}
		}
		m_Top_Speed = std::stod(temp_Speed);
	}

	std::string Car::condition() const{
		std::string res{};
		switch (m_Condition){
		case 'n':
			res = "new";
			break;
		case 'u':
			res = "used";
			break;
		case 'b':
			res = "broken";
			break;
		default:
			res = "invalid conditon";
			break;
		}
		return res;
	}

	double Car::topSpeed() const{
		return m_Top_Speed;
	}

	void Car::display(std::ostream& ostr) const {
		ostr << "| " << std::setw(10)<<std::right << m_Maker << " | " 
			 << std::setw(6) <<std::left<< condition() << " | " 
			 << std::setw(6) << std::setprecision(2) << std::fixed <<std::right<< m_Top_Speed << " |" << std::endl;
	}
	

}

