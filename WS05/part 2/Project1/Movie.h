/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 5 Part 2
	Module:			Movie
	File_Name:		Movie.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <string>
#include <iostream>
namespace sdds {
	class Movie {
		std::string m_title{};
		unsigned m_YOR{};
		std::string m_desc{};
	public:
		Movie() {};
		Movie(const std::string& strMovie);
		const std::string& title() const;
		template<typename T>
		void fixSpelling(T& spellChecker);
		friend std::ostream& operator <<(std::ostream& ostr, const Movie& src);
	};
	std::string& guansTrimmerV2(std::string&& src);

	template<typename T>
	inline void Movie::fixSpelling(T& spellChecker){
		spellChecker.operator()(m_title);
		spellChecker(m_desc);
	}
}
#endif // !SDDS_MOVIE_H

