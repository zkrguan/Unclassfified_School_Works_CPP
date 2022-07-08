/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Autoshop
	File_Name:		Autoshop.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#include <iostream>
#include "Autoshop.h"
#include "Vehicle.h"

namespace sdds {
	Autoshop& Autoshop::operator+=(Vehicle* theVehicle){
		m_vehicle.push_back(theVehicle);
		return *this;
	}

	void Autoshop::display(std::ostream& out) const{
		out << "--------------------------------\n"
			<< "| Cars in the autoshop!        |\n"
			<< "--------------------------------\n";
		// Mindset before learning STL //
		/*for (size_t i = 0; i < m_vehicle.size(); i++){
			out << m_vehicle[i]<<std::endl;
		}
		out << "--------------------------------\n";*/
		// Or a range based for loop//
		// Mindset after learning STL iterators//
		std::vector<Vehicle*>::const_iterator ptr_i{};
		for (ptr_i = m_vehicle.cbegin(); ptr_i !=m_vehicle.cend(); ++ptr_i){
			// m_veichile is already a vector of pointer//
			// the iterator is the pointer of the pointer (level2)//
			(*ptr_i)->display(out);
			out << "\n";
		}
		out << "--------------------------------\n";
	}

	/*Autoshop::Autoshop(const Autoshop& src){
		*this = src;
	}*/

	/*Autoshop::Autoshop(Autoshop&& src)noexcept{
		*this = std::move(src);
	}*/

	//Autoshop& Autoshop::operator=(const Autoshop& src){
	//	// std vector has the copy assignment overloaded//
	//	if (this!=&src){
	//		for  (auto& x : m_vehicle){
	//			delete x;
	//		}
	//		// deep copy the vector first//
	//		m_vehicle = src.m_vehicle;
	//		// deep copy the element// 
	//		//
	//		for (size_t i = 0; i < src.m_vehicle.size(); i++){
	//			memcpy(&m_vehicle[i], &src.m_vehicle[i], sizeof(src.m_vehicle[i]));
	//		}
	//	}
	//	return *this;
	//}

	//Autoshop& Autoshop::operator=(Autoshop&& src)noexcept{
	//	// std vector has the move assignment overloaded//
	//	if (this!=&src){
	//		m_vehicle = src.m_vehicle;
	//	}
	//	return *this;
	//}

	Autoshop::~Autoshop(){
		// Understand the STL from here//
		// Level 1 is managed by the STL lib//
		// But remember m_vehicle is vector of object pointers//
		// They are pointing to some dynamic memory// 
		// So you need to deallocate those memories pointed by the vector elements//
		for (auto & i:m_vehicle){
			delete i;
		}
	}


}