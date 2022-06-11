/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 4 Part 2
	Module:			Child
	File_Name:		Child.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#include <iostream>
#include <string>
#include "Child.h"

namespace sdds {
	unsigned CALL_CNT = 0;

	void Child::deallocate(){
		// class relation is composite//
		// Clean up needs to reach 2nd depth//
		for (size_t i = 0; i < m_Counter; i++){
			delete m_Tppr[i];
		}
		delete[] m_Tppr;
	}
	Child::Child(std::string name, int age, const Toy* toys[], size_t count){
		m_Name = name;
		m_Age = age;
		m_Counter = count;
		if (toys&&count){
			// since this is a constructor, there is no memory allocated yet for the member pptr//
			// so do not deallocate//
			m_Tppr = new const Toy* [count];
			// deep copy//
			// this is honestly same like what I did for the OOP beginner class project//
			// Since Toy Class has no resources involved//
			// using the compiler inserted constructor to build a nameless object on a dynamic mem//
			// then assign it to the arr element//
			for (size_t i = 0; i < count; i++){
				m_Tppr[i] = new Toy(*(toys[i]));
			}
		}
	}

	Child::Child(const Child& src){
		*this = src;
	}

	Child& Child::operator=(const Child& src){
		if (this!=&src){
			// just wanna make sure arr of pointer has something inside//
			if (src.m_Tppr&&src.m_Counter){
				if (m_Counter){
					this->deallocate();
				}
				m_Tppr = new const Toy*[src.m_Counter];
				for (size_t i = 0; i < src.m_Counter; i++){
					m_Tppr[i] = new Toy(*(src.m_Tppr[i]));
				}
			}
			m_Age = src.m_Age;
			m_Counter = src.m_Counter;
			m_Name = src.m_Name;
		}
		return *this;
	}

	Child::Child(Child&& src)noexcept{
		*this = std::move(src);
	}

	Child& Child::operator=(Child&& src)noexcept{
		if (this!=&src){
			if (src.m_Tppr&&src.m_Counter){
				if (m_Counter){
					this->deallocate();
				}
				m_Tppr = new const Toy * [src.m_Counter];
				for (size_t i = 0; i < src.m_Counter; i++) {
					m_Tppr[i] = src.m_Tppr[i];
					src.m_Tppr[i] = nullptr;
				}
				delete[] src.m_Tppr;
				src.m_Tppr = nullptr;
			}
			m_Age = src.m_Age;
			src.m_Age = 0;
			m_Counter = src.m_Counter;
			src.m_Counter = 0;
			m_Name = src.m_Name;
			src.m_Name = "";
		}
			return *this;
	}
	
	

	Child::~Child(){
		this->deallocate();
	}

	size_t Child::size() const{
		return size_t();
	}
	
	// simple boring display function// 
	std::ostream& operator<<(std::ostream& ostr, const Child& src){
		CALL_CNT++;
		ostr << "--------------------------\n";
		ostr << "Child " << CALL_CNT << ": " << src.m_Name <<" "<< src.m_Age << " years old:\n";
		ostr << "--------------------------\n";
		if (src.m_Counter){
			for (size_t i = 0; i < src.m_Counter; i++){
				ostr << *(src.m_Tppr[i]);
			}
		}
		else{
			ostr << "This child has no toys!\n";
		}
		ostr << "--------------------------\n";
		return ostr;
	}

}
