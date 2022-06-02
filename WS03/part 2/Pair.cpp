/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 3 Part 2
	Module:			Pair.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#include <string>
#include <iostream>
#include <iomanip>
#include "Pair.h"

namespace sdds {
	bool Pair::operator==(const Pair& src) const{
		return !((this->m_key).compare(src.m_key));
	}

	Pair& Pair::operator=(const Pair& src){
		if (this!=&src && src.m_key.c_str()){
			this->m_key = src.m_key;
			this->m_value = src.m_value;
		}
		return *this;
	}

	Pair::Pair(const Pair& src){
		*this = src;
	}


	std::ostream& operator<<(std::ostream& ostr, const Pair& src){
		return ostr << std::setw(20)<<std::right << src.getKey() << ": " << std::left << src.getValue();
	}


}