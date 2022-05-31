#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
namespace sdds {
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <typename T ,unsigned capacity>
	class Collection {
		T arrCollection [capacity]{};
		// Used the inline to initialize the static member value//
		// saved some works on initializing this member//
		inline static size_t eleNumTracker = 0;
		T dummy{};
	public:
		size_t size() const { return eleNumTracker; };
		void display(std::ostream& ostr = std::cout);
		bool add(const T& item);
		T operator [](int index) const;
	};

	template<typename T, unsigned capacity>
	inline void Collection<T, capacity>::display(std::ostream& ostr) {
		ostr << "----------------------" << "\n";
		ostr << "| Collection Content |\n";
		ostr << "----------------------\n";
		for (int i = 0; i < eleNumTracker; i++) 
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
	inline T Collection<T, capacity>::operator[](int index) const{
		T res{};
		return res = (index <= eleNumTracker)?arrCollection[index] : dummy;
	}


	
}
#endif // !SDDS_COLLECTION_H
