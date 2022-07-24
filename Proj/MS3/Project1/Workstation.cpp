#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Workstation.h"
namespace sdds {
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
		if (m_orders.begin()->isOrderFilled()||!Station::getQuantity())	{
			if (!m_pNextStation){
				if (m_orders.begin()->isOrderFilled()){
					g_completed.push_back((std::move(*m_orders.begin())));
				}
				else{
					g_incomplete.push_back((std::move(*m_orders.begin())));
				}
			}
			else{
				(*m_pNextStation) += std::move(*m_orders.begin());
			}
			result = true;
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

