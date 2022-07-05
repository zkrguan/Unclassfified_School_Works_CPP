/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 5 Part 2
	Module:			Book
	File_Name:		Book.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>
#include <iostream>
#include "SpellChecker.h"

namespace sdds {
	class Book {
		std::string m_Author{};
		std::string m_Title{};
		std::string m_PublicationCountry{};
		size_t m_PublicationYear{};
		double m_Price{};
		std::string m_bookSummary{};
	public:
		Book() {};
		Book(const std::string& strBook);
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();
		template<typename T>
		void fixSpelling(T& spellChecker);
		friend std::ostream& operator << (std::ostream& ostr, const Book& src);
		
	};

	std::string& guansTrimmerV2(std::string&& src);
	
	template<typename T>
	inline void Book::fixSpelling(T& spellChecker){
		spellChecker.operator()(m_bookSummary);
	}
}
#endif // !SDDS_BOOK_H
