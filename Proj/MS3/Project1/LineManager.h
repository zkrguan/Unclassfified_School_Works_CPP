#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
		void deallocate();
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
		// Rule of 5 needed here//
		// could only implement destructor since the Workstation disabled the copy and move//
		//~LineManager();
	};
}
#endif // !SDDS_LINEMANAGER_H

