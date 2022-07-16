#include <string>
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds{
	 size_t Station::m_widthField = 0;
	 size_t Station:: id_generator = 0;

	Station::Station(const std::string src){
		Utilities ut{};
		bool more = true;
		size_t next_pos{};
		m_station_ID = ++id_generator;
		m_item_name = ut.extractToken(src, next_pos, more);
		// TD:: ugly design//
		if (more){
			m_serial_num = std::stoull(ut.extractToken(src, next_pos, more));
		}
		if (more){
			m_stock_num = std::stoull(ut.extractToken(src, next_pos, more));
		}
		// before extracting the desc, set the m_widthField to the max//
		Station::m_widthField = (Station::m_widthField < ut.getFieldWidth()) ? ut.getFieldWidth() : Station::m_widthField;
		m_station_desc = ut.extractToken(src, next_pos, more);
	}

	const std::string& sdds::Station::getItemName() const { return m_item_name; }
	size_t sdds::Station::getNextSerialNumber() { return m_serial_num++; }
	size_t Station::getQuantity() const { return m_stock_num; }
	void Station::updateQuantity() { --m_stock_num; }

	void Station::display(std::ostream& os, bool full) const{
		os << std::setw(3)<<std::right << std::setfill('0') << m_station_ID << " | "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_item_name << " | "
			<< std::setw(6) << std::setfill('0') << std::right << m_serial_num << " | ";
		
		// wasted so much time of tenary, couldn't figure out...//
		if (full) {
			os 	<< std::setw(4) << std::setfill(' ') << m_stock_num << " | "
				<< std::left << m_station_desc << std::endl;
		}
		else os << std::endl;
			
	}
	


}


