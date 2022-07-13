#include <iomanip>
#include <algorithm>
#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include "CovidCollection.h"
namespace sdds {
	CovidCollection::CovidCollection(std::string fileName){
		std::ifstream ifstr(fileName);
		if (!ifstr.is_open()){
			throw std::string("Could not open this file\n");
		}
		else{
			// You have a extra line// 
			/*unsigned counter{};*/
			while (!ifstr.eof()){
				/*std::cout << ifstr.peek()<<'\n';*/
				if (ifstr.peek()!=-1){
					Covid temp{};
						/*std::cout << ++counter << "\n";*/
						// When I have time I will make this beautiful logic work//

						//std::string line{};
						//size_t fst_pos{};
						//size_t sec_pos{};
						//// I am assuming my prof doesn't like same codes repeating 5 times//
						//// I guess a lambda does not violate the workshop rules//
						//auto skippingThruSpaces = [](size_t& fst_pos, size_t& sec_pos, const std::string& line) {
						//	fst_pos = sec_pos;
						//	sec_pos = line.find_first_not_of(' ', fst_pos);
						//	if (sec_pos!=std::string::npos && line[sec_pos + 1] != ' '){
						//		sec_pos = line.find_first_not_of(' ', sec_pos+1);
						//	}
						//	fst_pos = sec_pos;
						//	sec_pos = line.find_first_of(' ', fst_pos);
						//};
						//std::getline(ifstr, line);
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_country = guansTrimmerV2(line.substr(fst_pos,  sec_pos - fst_pos));
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_city = guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos));
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_variant = guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos));
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_year = std::stoi(guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos)));
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_caseNum = std::stoull(guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos)));
						//skippingThruSpaces(fst_pos, sec_pos, line);
						//temp.m_deathNum = std::stoull(guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos)));

						// The most ugly code I ever wrote since OOP244//
						// Unfortunately it works//
					char tempCountry[27]{};
					char tempCity[27]{};
					char tempVariant[27]{};
					char tempYear[7]{};
					char tempCases[7]{};
					char tempDeaths[7]{};
					ifstr.get(tempCountry, 26, '\n');
					ifstr.get(tempCity, 26, '\n');
					ifstr.get(tempVariant, 26, '\n');
					ifstr.get(tempYear, 6, '\n'); ;
					ifstr.get(tempCases, 6, '\n');
					ifstr.get(tempDeaths, 6, '\n');
					ifstr.ignore(1000, '\n');
					temp.m_country = guansTrimmerV2(std::string(tempCountry));
					temp.m_city = guansTrimmerV2(std::string(tempCity));
					temp.m_variant = guansTrimmerV2(std::string(tempVariant));
					temp.m_year = std::stoi(guansTrimmerV2(std::string(tempYear)));
					temp.m_caseNum = std::stoull(guansTrimmerV2(std::string(tempCases)));
					temp.m_deathNum = std::stoull(guansTrimmerV2(std::string(tempDeaths)));
					m_collection.push_back(temp);
				}
			}
		}
	}

	void CovidCollection::display(std::ostream& out) const{
		std::for_each(m_collection.begin(), m_collection.end(), [](const Covid& theCovid) {std::cout << theCovid; });
	}

	std::string& guansTrimmerV2(std::string&& src) {
		if (src.c_str()) {
			src.erase(0, src.find_first_not_of(' '));
			src.erase(src.find_last_not_of(' ') + 1);
		}
		return src;
	}
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid){
		out << "| " <<std::left<< std::setw(21) << theCovid.m_country << " | "
			<< std::left << std::setw(15) << theCovid.m_city << " | "
			<< std::left << std::setw(20) << theCovid.m_variant << " | ";
		out << std::setw(6) << std::right;
		if (theCovid.m_year>0){
			out << theCovid.m_year;
		}
		else{
			out << "";
		}
		out << " | " << std::setw(4) << theCovid.m_caseNum << " | "
			<< std::setw(3) << theCovid.m_deathNum << " |\n";
		return out;
	}
}

