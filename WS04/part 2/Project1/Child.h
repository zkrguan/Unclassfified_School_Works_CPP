/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 4 Part 2
	Module:			Child
	File_Name:		Child.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H
#include <memory>
#include <iostream>
#include <string>
#include "Toy.h"
namespace sdds {
	class Child {
		const sdds::Toy** m_Tppr{};
		size_t m_Counter{};
		int m_Age{};
		std::string m_Name{};
		void deallocate();
	public:
		// rule of 5 + multi args constructor//
		Child(std::string name, int age,const Toy* toys[],size_t count);
		Child(const Child& src);
		Child& operator = (const Child& src);
		Child(Child&& src)noexcept;
		Child& operator= (Child&& src)noexcept;
		virtual ~Child();
		// query funciton//
		size_t size()const;
		friend std::ostream& operator <<(std::ostream& ostr, const Child& src);
	};
}
#endif // !SDDS_CHILD_H
