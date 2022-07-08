/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Car
	File_Name:		Car.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include <iostream>
#include <string>
#include "Vehicle.h"

namespace sdds {
	class Car : public Vehicle{
		std::string m_Maker{};
		char m_Condition{};
		double m_Top_Speed{};
	public:
		Car(std::istream& istr);
		virtual std::string condition() const;
		virtual double topSpeed() const;
		virtual void display(std::ostream&) const;
		virtual ~Car() {};


	};

}

#endif // !SDDS_CAR_H
