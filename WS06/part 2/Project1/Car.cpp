/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Car
	File_Name:		Car.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "Car.h"
#include "Utilities.h"

namespace sdds {
	Car::Car(std::istream& istr){
		char tag = istr.peek();
		istr.ignore();
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
			m_Condition = 'n';
		}
		else if (istr.peek() == ' ') {
			//ignore the space//
			istr.ignore();
			// not equal to , means there isn't just a space in this field//
			if (istr.peek() != ','){
				istr.get(m_Condition);
				if (m_Condition!='n' && m_Condition != 'u'&&m_Condition!='b'){
					istr.ignore(1000, '\n');
					throw std::string("Invalid record!");
				}
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
			std::getline(istr, temp_Speed, '\n');
		}
		else if(tag=='r'||tag=='R') {
			// prepare for reading the boost//
			std::getline(istr, temp_Speed, ',');
			while (istr.peek() == ',' || istr.peek() == ' ') {
				istr.ignore();
			}
		}
		// could have used capture list//
		// But this could be used in the future oopProject//
		auto isNumV1 = [](std::string src)->bool {
			bool res = true;
			for (size_t i = 0; i < src.length()&&res; i++)
				if(!std::isdigit(src.c_str()[i])) res = false;
			return res;
		};
		guansTrimmerV3(temp_Speed);
		if(isNumV1(temp_Speed)){
			m_Top_Speed = std::stod(temp_Speed);
		}
		else{
			istr.ignore(1000, '\n');
			throw std::string("Invalid record!");
		}
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
			res = "Invalid conditon";
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
			 << std::setw(6) << std::setprecision(2) << std::fixed <<std::right<< topSpeed() << " |";
	}


}

