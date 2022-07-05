/*
    Course_Name:	OOP 345
    Section:		A
    Title:			Workshop 5 Part 2
    Module:			Movie
    File_Name:		Movie.cpp
    Student_Name:	Zhaokai_Guan
    Student_ID:		130988215

*/
#include <string>
#include <iostream>
#include <iomanip>
#include "Movie.h"
#include "Book.h"
namespace sdds {
    Movie::Movie(const std::string& strMovie){
        size_t fst_Pos{};
        size_t sec_Pos{};
        sec_Pos = strMovie.find(',');
        m_title = guansTrimmerV2(strMovie.substr(fst_Pos, sec_Pos));
        fst_Pos = ++sec_Pos;
        sec_Pos = strMovie.find(',', fst_Pos);
        m_YOR = std::stoi(guansTrimmerV2(strMovie.substr(fst_Pos, (sec_Pos-fst_Pos))));
        fst_Pos = ++sec_Pos;
        m_desc = guansTrimmerV2(strMovie.substr(fst_Pos));
    }
    
    const std::string& sdds::Movie::title() const {
        return m_title;
    }

    std::ostream& operator <<(std::ostream& ostr, const Movie& src) {
       return ostr << std::setw(40) << src.m_title << " | " << std::setw(4) << src.m_YOR << " | " << src.m_desc << std::endl;
    }
}

