#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	void CustomerOrder::deallocate(){
		for (size_t i = 0; i < m_cntItem; i++){
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	CustomerOrder::CustomerOrder(const std::string src)	{
		Utilities ut{};
		// previous main code already give the Delimiter as |.
		//ut.setDelimiter('|');
		bool more = true;
		size_t next_pos{};
		m_name = ut.extractToken(src, next_pos, more);

		if (more) {
			 m_product = ut.extractToken(src, next_pos, more);
		}
		// how to determine the size of the Dynamic arr//
		// Two solutions 
		// 1. Keep resizing while reading( headache ).. Resizing is very expensive.
		// 2. Determine the size before allocating.
		if (more){
			size_t arr_size = std::count_if(src.begin(), src.end(), [=](const char ele) {return ele == ut.getDelimiter(); });
			// itemNum = arr_size  - 1 (2 |s meaning 2items but don't forget the first field and second field are delimited by | too.
			m_lstItem = new Item* [arr_size-1];
		}
		while (more) {
			// Now let the single element point to the new resource//
			m_lstItem[m_cntItem] = new Item(ut.extractToken(src, next_pos, more));
			m_cntItem++;
		}
		// before extracting the desc, set the m_widthField to the max//
		CustomerOrder::m_widthField = (CustomerOrder::m_widthField < ut.getFieldWidth()) ? ut.getFieldWidth() : CustomerOrder::m_widthField;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept {
		if (this != &src){
			m_name = src.m_name;
			src.m_name = "";
			m_product = src.m_product;
			src.m_product = "";
			if (src.m_lstItem){
				if (m_lstItem) deallocate();
				m_lstItem = src.m_lstItem;
				for (size_t i = 0; i < src.m_cntItem; i++) {
					m_lstItem[i] = src.m_lstItem[i];
					/*src.m_lstItem[i] = nullptr;*/
				}
				src.m_lstItem = nullptr;
			}
			m_cntItem = src.m_cntItem;
			src.m_cntItem = 0ull;
		}
		return *this;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept{
		*this = std::move(src);
	}

	CustomerOrder::~CustomerOrder(){
		deallocate();
	}

	bool CustomerOrder::isOrderFilled() const{
		return std::all_of(&m_lstItem[0], &m_lstItem[m_cntItem], [](const Item* ele) {return ele->m_isFilled; });
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const	{
		return std::all_of(&m_lstItem[0], &m_lstItem[m_cntItem], [](const Item* ele) {return !(ele->m_itemName == ""); });
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os){
		auto indexPtr = std::find_if(m_lstItem, &m_lstItem[m_cntItem], [=](const Item* ele) {return ele->m_itemName == station.getItemName(); });
		/*std::any_of(m_lstItem,&m_lstItem[m_cntItem],[=](const Item* ele) {return ele->m_itemName == station.getItemName();})*/
		// Don't know this would work//
		if (indexPtr!=&m_lstItem[m_cntItem]) {
			if (station.getQuantity()){
				//TD: might need one more if clause or change the predicate in the find_if
				station.updateQuantity();
				(*indexPtr)->m_isFilled = true;
				// might not be right//
				(*indexPtr)->m_serialNumber = station.getNextSerialNumber();
				os << "Filled " + m_name + ", " + m_product + " [" + (*indexPtr)->m_itemName + "]\n";
			}
			else{
				os << "Unable to fill " + m_name + ", " + m_product + " [" + (*indexPtr)->m_itemName + "]\n";
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const	{
		os << m_name << " - " << m_product << "\n";
		std::for_each(m_lstItem, &m_lstItem[m_cntItem], [&os](const Item* ele) {
			os << "[" << std::setw(6) << ele->m_serialNumber << "]"
				<< std::setw(m_widthField) << ele->m_itemName
				<< " - " << (ele->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
			});
	}

}
