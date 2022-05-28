/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 1 Part 2
	Module:			foodorder
	File_Name:		foodorder.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

	version:	    2
	Notes:			Fixed some issues in the foodOrder module
					Changed a few sentences in the reflect.txt
*/
#ifndef SDDS_FOODORDERS_H
#define SDDS_FOODORDERS_H
#include <iostream>
#include <string>
extern double g_taxrate;
extern double g_dailydiscount;

namespace sdds {

	class FoodOrder{
	private:
		char m_custName[10]{};
		char* m_foodDesc{};
		double m_foodPrice{};
		bool m_dailySpecial{};	
		void deallocate();
		bool validateName()const;
	public:
		FoodOrder() {};
		FoodOrder(const FoodOrder& src);
		FoodOrder& operator = (const FoodOrder& src);
		std::istream& read(std::istream& istr);
		void display()const;
		~FoodOrder();
	};
}

#endif // !SDDS_FOODORDERS_H

