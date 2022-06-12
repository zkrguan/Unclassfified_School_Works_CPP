#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"

namespace sdds {
    const std::string& sdds::Book::title() const{
        return m_Title;
    }

    const std::string& Book::country() const{
        return m_PublicationCountry;
    }

    const size_t& Book::year() const{
        return m_PublicationYear;
    }

    double& Book::price(){
        return m_Price;
    }
   
    Book::Book(const std::string& strBook) {
        size_t fst_Pos{};
        size_t sec_Pos{};
        sec_Pos = strBook.find(',');
        m_Author = guansTrimmerV2(strBook.substr(fst_Pos, (sec_Pos - fst_Pos)));
        fst_Pos = ++sec_Pos;
        sec_Pos = strBook.find(',', fst_Pos);
        m_Title = guansTrimmerV2(strBook.substr(fst_Pos, (sec_Pos - fst_Pos)));
        fst_Pos = ++sec_Pos;
        sec_Pos = strBook.find(',', fst_Pos);
        m_PublicationCountry = guansTrimmerV2(strBook.substr(fst_Pos, (sec_Pos - fst_Pos)));
        fst_Pos = ++sec_Pos;
        sec_Pos = strBook.find(',', fst_Pos);
        m_Price = std::stod(guansTrimmerV2((strBook.substr(fst_Pos, (sec_Pos - fst_Pos)))));
        fst_Pos = ++sec_Pos;
        sec_Pos = strBook.find(',', fst_Pos);
        m_PublicationYear = std::stoi(guansTrimmerV2((strBook.substr(fst_Pos, (sec_Pos - fst_Pos)))));
        m_bookSummary = guansTrimmerV2(strBook.substr(++sec_Pos));
    }


    std::ostream& operator<<(std::ostream& ostr, const Book& src){
        return 
             ostr << std::setw(20) << src.m_Author << " | " << std::setw(22) << src.m_Title << " | "
             << std::setw(5) << src.m_PublicationCountry << " | " << std::setw(4) << src.m_PublicationYear << " | "
             << std::fixed << std::setw(6) << std::setprecision(2) << src.m_Price << " | "
             << src.m_bookSummary << "\n";
  
    }

    std::string& guansTrimmerV2(std::string&& src) {
        if (src.c_str()) {
            src.erase(0, src.find_first_not_of(' '));
            src.erase(src.find_last_not_of(' ') + 1);
        }
        return src;
    }
}

