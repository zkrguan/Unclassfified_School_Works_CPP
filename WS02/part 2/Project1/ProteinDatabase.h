/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 2 Part 2
	Module:			ProteinDatabase
	File_Name:		ProteinDatabase.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_PROTEINDATABASE_H
#define SDDS_PROTEINDATABASE_H
#include <string>

namespace sdds {

	class ProteinDatabase {
		std::string* recordedArr{};
		static size_t recordNum;
	public:
		ProteinDatabase() {};
		ProteinDatabase(std::string fileName);
		std::istream& read(std::istream& istr, bool countMode = true);
		size_t size() const;
		std::string operator[](size_t index) const;

		//rule of 3 //
		ProteinDatabase(const ProteinDatabase& src);
		ProteinDatabase& operator = (const ProteinDatabase& src);
		~ProteinDatabase();

		// move constructor and operator//
		ProteinDatabase(ProteinDatabase&& src)noexcept;
		ProteinDatabase& operator =(ProteinDatabase&& src)noexcept;

	};
	// trimming of all the newline chars//
	std::string& guanStringTrimmer(std::string& src);
}
#endif // !SDDS_PROTEINDATABASE_H

