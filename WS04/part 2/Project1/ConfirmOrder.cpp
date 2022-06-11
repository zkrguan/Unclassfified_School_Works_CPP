/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 4 Part 2
	Module:			ConfirmOrder
	File_Name:		ConfirmOrder.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#include <iostream>
#include <string>
#include "ConfirmOrder.h"
namespace sdds {
	ConfirmOrder& sdds::ConfirmOrder::operator+=(const Toy& toy){
		bool res = true;
		//instead of using another counter
		//iterator i is a perfect for subscript index//
		size_t i = 0;
		for (; i < m_ArrSize&&res; i++){
			if (m_Tppr[i]==&toy) {
				res = false;
			}
		}
		if (res){
			if (m_ArrSize){
				// keep all the existing records in the temp//
				const Toy** temp = new const Toy * [m_ArrSize+1];
				for (size_t j = 0; j < m_ArrSize; j++) {
					temp[j] = m_Tppr[j];
					m_Tppr[j] = nullptr;
				}
				// resize ptr arr pointed by m_Tppr//
				// deallocating//
				delete[] m_Tppr;
				// Now you can increase the size//
				m_ArrSize++;
				// allocating new memory for the ptr array//
				m_Tppr = new const Toy * [m_ArrSize];
				// Swapping right back to the member pointer//
				for (size_t j = 0; j < m_ArrSize; j++){
					m_Tppr[j] = temp[j];
					temp[j] = nullptr;
				}
				delete[] temp;
				// Finally shallow copy the resource onto i index//
				m_Tppr[i] = &toy;
			}
			// handle the senario when array size is 0//
			else{
				// I know this is not elegant//
				// But it saves a little logic on checking//
				m_Tppr = new const Toy * [1];
				m_Tppr[0] = &toy;
				m_ArrSize++;
			}
		}
		return *this;
	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy){
		bool res = false;
		size_t i = 0;
		// again used some unconventional for loop tricks//
		for (; i < m_ArrSize && !res; i++) {
			if (m_Tppr[i] == &toy) {
				res = true;
			}
		}
		if (res){
			// iterator is still there// 
			// shifting by 1 index to the left//
			for (;  i<m_ArrSize; ++i){
				m_Tppr[i - 1] = m_Tppr[i];
			}
			if (m_ArrSize>1) {
				m_Tppr[m_ArrSize - 1] = nullptr;
				m_ArrSize--;
				// resize array by deducting one// 
				// keep all the existing in the temp//
				const Toy** temp = new const Toy * [m_ArrSize];
				for (size_t j = 0; j < m_ArrSize; j++) {
					// move it onto the temp//
					temp[j] = m_Tppr[j];
					m_Tppr[j] = nullptr;
				}
				// resize ptr arr pointed by m_Tppr//
				delete[] m_Tppr;
				m_Tppr = new const Toy * [m_ArrSize];
				for (size_t j = 0; j < m_ArrSize; j++) {
					m_Tppr[j] = temp[j];
					temp[j] = nullptr;
				}
				// clean the temp//
				delete[] temp;
			}
			else {
				delete[] m_Tppr;
				m_Tppr = 0;
			}
		}
		return *this;
	}

	ConfirmOrder::ConfirmOrder(const ConfirmOrder& src){
		*this = src;
	}

	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src){
		if (this!=&src){
			if (src.m_ArrSize){
				// checking if there is any memory has been allocated for m_Tppr//
				if (m_Tppr) {
					delete[] m_Tppr;
				}
				//allocate the memory and ready to shallow copy all the object//
				m_Tppr = new const Toy * [src.m_ArrSize];
				
				// This is the most confusing part//
				// Shallow copying inside a deep copy logic?//
				// Remember the class type is aggregation//
				// My brain fights against to the finger muscle//
				for (size_t i = 0; i < src.m_ArrSize; i++) {
					// letting two ptr pointed at the same object//
					// don't actually create memory for this//
					// cuz you are not controlling the life time of that object//
					// as for deallocation, not your business, because this is aggregation//
					m_Tppr[i] = src.m_Tppr[i];
				}
			}
			m_ArrSize = src.m_ArrSize;
		}
		return *this;
	}

	ConfirmOrder::ConfirmOrder(ConfirmOrder&& src) noexcept{
		*this = std::move(src);
	}

	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src)noexcept{
		if (this!=&src){
			if (src.m_ArrSize){
				if (m_ArrSize) {
					delete[] m_Tppr;
				}
				// I know this is also confusing// 
				// only shallow copy the pointer pointing to the array of pointers//
				// What about the elements inside that array?//
				// Would that be memory leak?//
				// Again this is a aggregation// 
				// We only care about the 1st depth matters//
				// 2nd depth's is not our business//
				// If there is a leak, that must be the other people's problems//
				m_Tppr = src.m_Tppr;
				src.m_Tppr = nullptr;
			}
			m_ArrSize = src.m_ArrSize;
			src.m_ArrSize = 0;
		}
		return *this;
	}

	ConfirmOrder::~ConfirmOrder(){
		// again the whole design makes us to understand what is a real aggregation//
		// You can only touch the array pointer's memory//
		// Going one depth further would be causing issues and violating the aggregation rules//
		delete[] m_Tppr;
	}



	// Just a simple boring display function//
	std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& src){
		if (src.m_ArrSize){
			ostr << "--------------------------\n";
			ostr << "Confirmations to Send\n";
			ostr << "--------------------------\n";
			for (size_t i = 0; i < src.m_ArrSize; i++){
				ostr << *(src.m_Tppr[i]);
			}
			ostr << "--------------------------\n";
		}
		else{
			ostr << "--------------------------\n";
			ostr << "Confirmations to Send\n";
			ostr << "--------------------------\n";
			ostr << "There are no confirmations to send!\n";
			ostr << "--------------------------\n";
		}
		return ostr;
	}

}

