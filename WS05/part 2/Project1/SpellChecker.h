/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 5 Part 2
	Module:			SpellChecker
	File_Name:		SpellChecker.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <string>
namespace sdds {
	const unsigned ARRAY_SIZE = 6;
	class SpellChecker {
		std::string m_badWords[ARRAY_SIZE]{};
		std::string m_goodWords[ARRAY_SIZE]{};
		size_t m_counts[ARRAY_SIZE]{{}};
	public:
		SpellChecker(const char* filename);
		void operator ()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};
}
#endif // !SDDS_SPELLCHECKER_H

