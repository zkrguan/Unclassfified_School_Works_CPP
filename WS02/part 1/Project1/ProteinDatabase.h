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
	};

}
#endif // !SDDS_PROTEINDATABASE_H

