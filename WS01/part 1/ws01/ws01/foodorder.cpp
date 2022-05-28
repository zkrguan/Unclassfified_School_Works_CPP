#include <iostream>
#include <iomanip>
#include "foodorder.h"

namespace sdds {
	// static int counter used for display()//
	// added in the header file before but it did not work//
	// To the future me, variable should be kept in the .cpp file// 
	static int counter = 0;
	// Two globals from the header initialized here//
	double g_taxrate = 0;
	double g_dailydiscount = 0;
	std::istream& sdds::FoodOrder::read(std::istream& istr){
		if (istr){
			char onSaleTag{};
			// classic C-string extracting without using string class methods//
			istr.get(this->m_custName, 9,',');
			//get rid of that comma//
			// simimar logic used for the rest of the attributes//
			istr.ignore();
			istr.get(this->m_foodDesc, 24,',');
			istr.ignore();
			istr >> m_foodPrice;
			istr.ignore();
			istr >> onSaleTag;
			this->m_dailySpecial = (onSaleTag == 'Y') ? true : false;
			istr.ignore();
		}
		return istr;
	}

	std::ostream& sdds::FoodOrder::display(std::ostream& ostr) const{
		ostr << std::left << std::setw(2) << ++sdds::counter << ". ";
		if (this->validateName()) {
			ostr << std::left << std::setw(10) << this->m_custName;
			ostr << "|" << std::left << std::setw(25) << this->m_foodDesc;
			ostr << "|" << std::left << std::fixed << std::showpoint << std::setprecision(2) << std::setw(12) << (this->m_foodPrice * (1.0 + g_taxrate)) << "|";
			if (this->m_dailySpecial) {
				ostr << std::right << std::fixed << std::showpoint << std::setprecision(2) << std::setw(12) << std::setw(13) << ((this->m_foodPrice * (1.0 + g_taxrate) - g_dailydiscount)) << std::endl;
			}
			else {
				ostr << std::endl;
			}
		}
		else{
			ostr << "No Order" << std::endl;
		}
		return ostr;
	}
	bool FoodOrder::validateName()const{
		return ((this->m_custName[0] >= 'A' && this->m_custName[0] <= 'Z') || (this->m_custName[0] >= 'a' && this->m_custName[0] <= 'z'));
	}
}