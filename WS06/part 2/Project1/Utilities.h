#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	Vehicle* createInstance(std::istream& in);
	std::string& guansTrimmerV3(std::string& src);
}
#endif // !SDDS_UTILITIES_H

