#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
namespace sdds {
	struct Covid {
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		size_t m_caseNum{};
		int m_year{};
		size_t m_deathNum{};
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};
	public:
		CovidCollection(std::string fileName);
		void display(std::ostream& out) const;

	};
	std::string& guansTrimmerV2(std::string&& src);
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif // !SDDS_COVIDCOLLECTION

