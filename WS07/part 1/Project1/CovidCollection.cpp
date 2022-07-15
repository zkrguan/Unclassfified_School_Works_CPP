#include <numeric>
#include <functional>
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
						//temp.m_deaths = std::stoull(guansTrimmerV2(line.substr(fst_pos, sec_pos - fst_pos)));

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
					temp.m_deaths = std::stoull(guansTrimmerV2(std::string(tempDeaths)));
					m_collection.push_back(temp);
				}
			}
		}
	}

	void CovidCollection::display(std::ostream& out) const{
		std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& theCovid) {out << theCovid<<"\n"; });
		size_t CaseResult{};
		size_t DeathResult{};
		CaseResult = std::accumulate(m_collection.begin(), m_collection.end(), 0ull, [](size_t acc, const Covid& src2) {return acc + src2.m_caseNum; } );
		DeathResult = std::accumulate(m_collection.begin(), m_collection.end(), 0ull, [](size_t acc, const Covid& src2) {return acc + src2.m_deaths; });
		out << "----------------------------------------------------------------------------------------\n";
		out << "|"<<std::setw(78)<<"Total Cases Around the World:"<<"  " << std::setw(5) << CaseResult << " |" << std::endl
			<< "|"<< std::setw(78) <<"Total Deaths Around the World:"<<"  " << std::setw(5) << DeathResult << " |\n";
	}

	void CovidCollection::cleanList(){
		// overload an assignment operator for Covid class//
		std::replace_if(m_collection.begin(), m_collection.end(), [](const Covid& src) {return src.m_variant == std::string("[None]"); }, std::string(""));
	}

	void CovidCollection::sort(std::string keyWord){
		if (keyWord=="country")	{
			std::sort(m_collection.begin(), m_collection.end(), [](const Covid& src1, const Covid& src2) {return src1.m_country < src2.m_country; });
		}
		else if (keyWord == "variant") {
			std::sort(m_collection.begin(), m_collection.end(), [](const Covid& src1, const Covid& src2) {return src1.m_variant< src2.m_variant; });
		}
		else if (keyWord == "cases") {
			std::sort(m_collection.begin(), m_collection.end(), [](const Covid& src1, const Covid& src2) {return src1.m_caseNum < src2.m_caseNum; });
		}
		else if (keyWord == "deaths"){
			std::sort(m_collection.begin(), m_collection.end(), [](const Covid& src1, const Covid& src2) {return src1.m_deaths < src2.m_deaths; });
		}
		else{
			std::cout << "You enter some wrong stuff\n";
		}
	}

	bool CovidCollection::inCollection(const char* VName) const{
		std::string paraAdapter (VName);
		return std::any_of(m_collection.begin(), m_collection.end(), [=](const Covid& src) { return src.m_variant == paraAdapter; });
	}

	std::list<Covid> CovidCollection::getListForCountry(const char* countryName) const	{
		std::string paraAdapter(countryName);
		std::list<Covid> resList(std::count_if(m_collection.begin(), m_collection.end(), [=](const Covid& src) {return src.m_country == paraAdapter; }));
		// learned the copy_if algorithm from C++ reference.
		std::copy_if(m_collection.begin(), m_collection.end(), resList.begin(),
			[=](const Covid& srcCollection) {return !srcCollection.m_country.compare(paraAdapter); });
		return resList;
	}

	std::list<Covid> CovidCollection::getListForVariant(const char* variantName) const	{
		std::string paraAdapter(variantName);
		std::list<Covid>resList(m_collection.size());
		std::transform(m_collection.begin(), m_collection.end(), resList.begin(), [=](const Covid& src) {Covid res{}; if (src.m_variant == paraAdapter) res = src; return res; });
		resList.erase(std::remove_if(resList.begin(), resList.end(), [](const Covid& src) {return src.m_country == ""; }),resList.end());
		return resList;
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
			<< std::setw(3) << theCovid.m_deaths << " |";
		return out;
	}
}

