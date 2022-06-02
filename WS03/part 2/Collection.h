/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 3 Part 2
	Module:			Collection
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include "Pair.h"

namespace sdds {
	template <typename T, unsigned capacity>
	class Collection {
		T arrCollection [capacity]{};
		// Used the inline to initialize the static member value//
		// saved some works on initializing this member//
		// inline static size_t eleNumTracker = 0;//
		static size_t eleNumTracker;
		static T dummy;
	public:
		size_t size() const { return eleNumTracker; };
		void display(std::ostream& ostr = std::cout);
		virtual bool add(const T& item);
		T operator [](unsigned index) const;
		virtual ~Collection() {};
	};
	//Also pratice the syntax of initializing a static attribute of a class//
	template<typename T,unsigned capacity>
	size_t Collection<T, capacity> :: eleNumTracker = 0;

	template<typename T, unsigned capacity>
	inline void Collection<T, capacity>::display(std::ostream& ostr) {
		ostr << "----------------------" << "\n";
		ostr << "| Collection Content |\n";
		ostr << "----------------------\n";
		for (unsigned i = 0; i < eleNumTracker; i++)
			ostr << arrCollection[i]<< "\n";
		ostr << "----------------------\n";
	}

	template<typename T, unsigned capacity>
	inline bool Collection<T, capacity>::add(const T& item){
		bool res = true;
		if (eleNumTracker==capacity)
			res = false;
		else{
			arrCollection[eleNumTracker] = item;
			eleNumTracker++;
		}
		return res;
	}

	template<typename T, unsigned capacity>
	inline T Collection<T, capacity>::operator[](unsigned index) const{
		return (index < eleNumTracker) ? arrCollection[index] : dummy;
	}
	
	template<typename T, unsigned capacity>
	T Collection<T, capacity>::dummy{};

	template<>
	Pair Collection<Pair, 100>::dummy = Pair("No Key", "No Value");
	
}
#endif // !SDDS_COLLECTION_H
