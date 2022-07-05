#include <iostream>
#include <iomanip>
#include <string>
#include "Car.h"
#include "Utilities.h"

namespace sdds {
	Car::Car(std::istream& istr){
		// taking in the maker
		std::getline(istr, m_Maker, ',');
		guansTrimmerV3(m_Maker);
		istr.ignore();
		// taking in the Conditon
		istr.get(m_Condition);
		istr.ignore(2);
		// taking in the top-speed
		std::string temp_Speed{};
		std::getline(istr, temp_Speed, '\n');
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

