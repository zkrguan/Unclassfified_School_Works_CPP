#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
namespace sdds {
	class Station {
		size_t m_station_ID{};
		std::string m_item_name{};
		std::string m_station_desc{};
		size_t m_serial_num{};
		size_t m_stock_num{};
		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string src);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};

}

#endif // !SDDS_STATION_H
