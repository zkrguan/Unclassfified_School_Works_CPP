#include <deque>
#include <algorithm>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Workstation.h"
namespace sdds {
	//Define global//
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	void sdds::Workstation::fill(std::ostream& os) {
		if (m_orders.size()){
			m_orders.begin()->fillItem(*this,os);
		}
	}
	bool Workstation::attemptToMoveOrder()	{
		bool result{false};
		// added line 21 for avoid some exception//
		if (m_orders.size()){
			// checking the station handled item filled or not//
			// Checking quantity//
			if (m_orders.begin()->isItemFilled(getItemName()) || !getQuantity()) {
				if (!m_pNextStation) {
					if (m_orders.begin()->isOrderFilled()) {
						g_completed.push_back((std::move(*m_orders.begin())));
					}
					else {
						g_incomplete.push_back((std::move(*m_orders.begin())));
					}
					// Once the current order at the last station//
					// It has to be moved to either completed or incompleted//
					// Don't forget to pop out the empty element just moved to the global//
					m_orders.pop_front();
				}
				else {
					// When the current station is not the last station, move order to next station//
					(*m_pNextStation) += std::move(*m_orders.begin());
					m_orders.pop_front();
				}
				result = true;
			}
		}
		return result;
	}
	void Workstation::setNextStation(Workstation* station){
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << "--> " << (m_pNextStation ? m_pNextStation->getItemName() : std::string("End of Line"))<< std::endl;
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}

