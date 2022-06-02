/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 3 Part 2
	Module:			Pair.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H
#include <string>
#include <iostream>
namespace sdds {
	class Pair{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() const { return m_key; }
		const std::string& getValue() const { return m_value; }
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

		// TODO: Add here the missing prototypes for the members
		//           that are necessary if this class is to be used
		//           with the template classes described below.
		//       Implement them in the Pair.cpp file.

		// operator overload for the ==//
		bool operator == (const Pair& src) const;
		// default constructor//
		Pair() {};
		// assignment operator //
		Pair& operator = (const Pair& src);
		// copy constructor // 
		Pair(const Pair& src);
	};
	// insertion operator overload//
	std::ostream& operator << (std::ostream& ostr,const Pair& src);
}
#endif // !SDDS_PAIR_H

