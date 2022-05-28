#ifndef SDDS_FOODORDERS_H
#define SDDS_FOODODERS_H
#include <iostream>

namespace sdds {
	class FoodOrder{
	private:
		char m_custName[10]{};
		char m_foodDesc[25]{};
		double m_foodPrice{};
		bool m_dailySpecial{};
	public:
		FoodOrder() {};
		std::istream& read(std::istream& istr);
		std::ostream& display(std::ostream& ostr)const;
		bool validateName()const;
	};
	// the two globals goes here//
	extern double g_taxrate;
	extern double g_dailydiscount;
}

#endif // !SDDS_FOODORDERS_H

