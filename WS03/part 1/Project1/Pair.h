#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H
#include <string>

namespace sdds {
	class Pair
	{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() { return m_key; }
		const std::string& getValue() { return m_value; }
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

		// TODO: Add here the missing prototypes for the members
		//           that are necessary if this class is to be used
		//           with the template classes described below.
		//       Implement them in the Pair.cpp file.

		// operator overload for the ==//
		bool operator == (const Pair& src) const;
		// default constructor//
		Pair() {};
		// assignment operator //
		Pair& operator = (const Pair& src);
		// copy constructor // 
		Pair(const Pair& src);

	};
	// insertion operator overload//
	std::ostream& operator << (std::ostream& ostr, Pair& src);
}
#endif // !SDDS_PAIR_H

