#include<string>
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include "Toy.h"

namespace sdds {
	// initialize the global TAX_RATE
	const double TAX_RATE = 0.13;
	Toy::Toy(const std::string& toy){
		// if the string is not empty//
		// then start the construction // 
		if (toy.c_str()){
			std::string temp = toy;
			size_t fst_Pos{};
			size_t sec_Pos{};
			sec_Pos = temp.find(':');
			m_orderID = std::stoi(guansTrimmer((temp.substr(fst_Pos, (sec_Pos - fst_Pos)))));
			fst_Pos = ++sec_Pos;
			// preincrement to avoid the : // 
			sec_Pos = temp.find(':',fst_Pos);
			m_name = guansTrimmer(temp.substr(fst_Pos, (sec_Pos - fst_Pos)));
			fst_Pos = ++sec_Pos;
			sec_Pos = temp.find(':', fst_Pos);
			// similar logic used for getting the orderID//
			m_numOrdered =std::stoi(guansTrimmer((temp.substr(fst_Pos, (sec_Pos - fst_Pos)))));
			fst_Pos = ++sec_Pos;
			sec_Pos = temp.find(':', fst_Pos);
			m_price = std::stod(guansTrimmer((temp.substr(fst_Pos, (sec_Pos - fst_Pos)))));
			m_HST = m_numOrdered * m_price * TAX_RATE;
		}
	}
	void Toy::update(int numItems){
		this->m_numOrdered = numItems;
		this->m_HST = numItems * m_price * TAX_RATE;
	}
	std::ostream& operator<<(std::ostream& ostr, const Toy& src){
		// since we have already used the key word friend//
		// no need to use query methods to get the member attributes' value//
		ostr <<"Toy" <<std::right<< std::setw(8) << src.m_orderID << ":";
		ostr << std::setw(18) << std::right << src.m_name;
		ostr << std::setw(3) << std::right << src.m_numOrdered << " items";
		ostr << std::setw(8) << std::fixed << std::setprecision(2) <<std::right << src.m_price<<"/item  subtotal:";
		ostr << std::setw(7)<<std::setprecision(2) << std::right << src.m_price * src.m_numOrdered;
		ostr << " tax:" << std::setw(6) << std::right << src.m_HST;
		ostr << " total:" << std::setw(7) << std::right << src.m_price * src.m_numOrdered + src.m_HST<<"\n";
		return ostr;
	}

	std::string& guansTrimmer(std::string&& src){
		if (src.c_str()){
			// learned find first not of and find last not of //
			// tried the other ways, they will remove all the white space
			// or it is taking too many lines of code.// 
			// this is the best solution so far//
				src.erase(0,src.find_first_not_of(' '));
				src.erase(src.find_last_not_of(' ')+1);
		}
		
		return src;
	}
}

