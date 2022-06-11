/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 4 Part 2
	Module:			Toy
	File_Name:		Toy.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
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
	std::string& guansTrimmerV2(std::string&& src);
}
#endif // !SDDS_TOY_H
