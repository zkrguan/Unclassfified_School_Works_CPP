#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Workstation.h"
namespace sdds {
	void sdds::Workstation::fill(std::ostream& os) {
		if (m_orders.size()){
			/*m_orders.begin()->fillItem(os)*/
		}
	}
	bool Workstation::attemptToMoveOrder()	{
		bool result{};

		return result;
	}
}

