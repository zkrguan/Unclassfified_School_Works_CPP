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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "foodorder.h"

// Two globals from the header initialized here//
double g_taxrate = 0;
double g_dailydiscount = 0;

namespace sdds {
	
	void FoodOrder::deallocate(){
		delete[]this->m_foodDesc;
		m_foodDesc = nullptr;
	}

	FoodOrder::FoodOrder(const FoodOrder& src){
		*this = src;
	}

	FoodOrder& FoodOrder::operator=(const FoodOrder& src){
		if (this!=&src){
			if (src.validateName()){
				this->deallocate();
				strcpy(this->m_custName, src.m_custName);
				this->m_foodDesc = new char[strlen(src.m_foodDesc) + 1];
				strcpy(this->m_foodDesc, src.m_foodDesc);
				this->m_dailySpecial = src.m_dailySpecial;
				this->m_foodPrice = src.m_foodPrice;
			}
		}
		return *this;
	}


	std::istream& sdds::FoodOrder::read(std::istream& istr){
		this->deallocate();
		if (istr){
			char onSaleTag{};
			std::string temp{};
			if (!(istr.get(this->m_custName, 9, ',')))
				istr.setstate(std::ios::failbit);
			else {
				istr.ignore();
				std::getline(istr, temp, ',');
				if (!temp.empty()) {
					m_foodDesc = new char[temp.length() + 1];
					strcpy(m_foodDesc, temp.c_str());
				}
				istr >> m_foodPrice;
				istr.ignore();
				istr >> onSaleTag;
				this->m_dailySpecial = (onSaleTag == 'Y') ? true : false;
				istr.ignore();
			}
		}
		return istr;
	}

	bool FoodOrder::validateName()const{
		return ((this->m_custName[0] >= 'A' && this->m_custName[0] <= 'Z') || (this->m_custName[0] >= 'a' && this->m_custName[0] <= 'z'));
		
	}

	FoodOrder::~FoodOrder(){
		deallocate();
	}

	void FoodOrder::display() const{		
		// static int counter used for display()//
		static int counter = 0;
		std::cout << std::left << std::setw(2) << ++counter << ". ";
		if (this->validateName()) {
			std::cout << std::left << std::setw(10) << this->m_custName;
			std::cout << "|" << std::left << std::setw(25) << this->m_foodDesc;
			std::cout << "|" << std::left << std::showpoint << std::setprecision(2) << std::setw(12) << (this->m_foodPrice * (1.0 + g_taxrate)) << "|";
			if (this->m_dailySpecial) {
				std::cout << std::right << std::showpoint << std::setprecision(2) << std::setw(12) << std::setw(13) << ((this->m_foodPrice * (1.0 + g_taxrate) - g_dailydiscount)) << std::endl;
			}
			else {
				std::cout << std::endl;
			}
		}
		else {
			std::cout << "No Order" << std::endl;
		}
	}
}