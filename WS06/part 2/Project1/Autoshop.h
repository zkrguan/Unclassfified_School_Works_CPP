/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 6 Part 2
	Module:			Autoshop
	File_Name:		Autoshop.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_AUTOSHOP_H
#define SDDS_AUTOSHOP_H
#include <vector>
#include <list>
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Autoshop {
		std::vector<Vehicle*> m_vehicle{};
	public:
		Autoshop() {};
		Autoshop& operator +=(Vehicle* theVehicle);
		void display(std::ostream& out) const;
		template<typename T>
		void select(T test, std::list<const Vehicle*>& vehicles);
		~Autoshop();
	};
	/// <summary>
	/// 
	/// type name T must be a funciton that returns a bool value and the parameter takes a Vehicle pointer
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="test"></param>
	/// <param name="vehicles"></param>
	template<typename T>
	inline void Autoshop::select(T test, std::list<const Vehicle*>& vehicles){
		std::vector<Vehicle*>::const_iterator i;
		for ( i = m_vehicle.cbegin(); i!=m_vehicle.cend(); ++i){
			// iterator is always a pointer ONE level higher than the container//
			if (test(*i)) vehicles.push_back(*i);
		}
	}
}
#endif // !SDDS_AUTOSHOP_H
