/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 5 Part 2
	Module:			SpellChecker
	File_Name:		SpellChecker.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "SpellChecker.h"
namespace sdds {

	SpellChecker::SpellChecker(const char* filename){
		std::ifstream ifs(filename);
		if (ifs){
			unsigned index{};
			while (index<ARRAY_SIZE){
				std::string temp{};
				std::getline(ifs, temp);
				if (ifs){
					m_badWords[index] = temp.substr(0, temp.find_first_of(' '));
					m_goodWords[index] = temp.substr(temp.find_last_of(' ')+1);
					index++;
				}
			}
		}
		else{
			throw ("Bad file name!");
		}
	}

	void SpellChecker::operator()(std::string& text) {
		for (size_t i = 0; i < ARRAY_SIZE; i++){
			size_t found{};
			do {
				found = text.find(m_badWords[i],found);
				if (found != std::string::npos){
					text.replace(found, m_badWords[i].length(), m_goodWords[i]);
					found++;
					m_counts[i]++;
				}
			} while (found != std::string::npos);
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const{
		out << "Spellchecker Statistics\n";
		for (size_t i = 0; i < ARRAY_SIZE; i++)	{
			out << std::right << std::setw(15) << m_badWords[i] << ": " << m_counts[i] << " " << "replacements" << std::endl;
		}
	}
}

