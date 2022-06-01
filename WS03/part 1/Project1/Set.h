#ifndef SDDS_SET_H
#define SDDS_SET_H
#include "Collection.h"

namespace sdds {
	template <typename T>
	class Set : public Collection<T, 100> {
		bool add(const T& item);
	};

}
#endif // !SDDS_SET_H
