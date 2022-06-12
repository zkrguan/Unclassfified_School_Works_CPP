#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>
#include <iostream>

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

		friend std::ostream& operator << (std::ostream& ostr, const Book& src);
		
	};
	std::string& guansTrimmerV2(std::string&& src);
}
#endif // !SDDS_BOOK_H
