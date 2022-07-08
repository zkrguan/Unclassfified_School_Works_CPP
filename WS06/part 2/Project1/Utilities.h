/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Utilities
	File_Name:		Utilities.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	Vehicle* createInstance(std::istream& in);
	std::string& guansTrimmerV3(std::string& src);
}
#endif // !SDDS_UTILITIES_H

