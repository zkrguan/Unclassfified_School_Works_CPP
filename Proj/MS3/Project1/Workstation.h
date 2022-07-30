#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {
	// Declare global//
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;
	class Workstation : public Station{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};

	public:
		// disabled methods//
		Workstation& operator= (const Workstation& src) = delete;
		Workstation& operator= (Workstation&& src) = delete;
		Workstation(const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;

		Workstation(const std::string& src) : Station(src) {};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif // !SDDS_WORKSTATION_H

