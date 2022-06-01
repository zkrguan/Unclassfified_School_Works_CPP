#ifndef SDDS_SET_H
#define SDDS_SET_H
#include <cmath>
#include "Collection.h"

namespace sdds {
	template <typename T>
	class Set : public Collection<T, 100> {
	public:	
		bool add(const T& item);
	};

	template<typename T>
	inline bool Set<T>::add(const T& item){
		bool res = true;
		for (unsigned i = 0; (i < this->size())&&res; i++) {
			if ((*this)[i] == item)
				res = false;
		}
		if (res)
			Collection<T, 100>::add(item);
		return res;
	}

	template<>
	inline bool Set<double>::add(const double& item) {
		bool res = true;
		for (unsigned i = 0; (i < this->size()) && res; i++) {
			if (fabs((*this)[i]-item)<=0.01)
				res = false;
		}
		if (res){
			Collection<double, 100>::add(item);
		}
		return res;
	}

}
#endif // !SDDS_SET_H
