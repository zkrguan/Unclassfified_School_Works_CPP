#ifndef SDDS_TOY_H
#define SDDS_TOY_H
#include <string>
#include <iostream>
namespace sdds {
	extern const double TAX_RATE;

	class Toy {
		unsigned m_orderID{};
		std::string m_name{};
		unsigned m_numOrdered{};
		double m_price{};
		double m_HST{};

	public:
		Toy() {};
		Toy(const std::string& toy);
		void update(int numItems);
		friend std::ostream& operator << (std::ostream& ostr, const Toy& src);
	};
	std::string& guansTrimmer(std::string&& src);
}
#endif // !SDDS_TOY_H
