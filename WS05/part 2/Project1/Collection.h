/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 5 Part 2
	Module:			Collection
	File_Name:		Collection.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <iostream>
#include <string>
namespace sdds {
	template<typename T>
	class Collection {
		std::string m_desc{};
		T* m_arrPtr{};
		size_t m_arrSize{};
		void (*m_funcPtr) (const Collection<T>&, const T&) {};
	public:
		Collection(const std::string& name);
		Collection(const Collection<T>& src) = delete;
		Collection<T>& operator= (const Collection<T>& src) = delete;
		const std::string& name() const;
		size_t size() const;
		void setObserver(void (*observer)(const Collection<T>&, const T&));
		Collection<T>& operator+=(const T& item);
		T& operator[](size_t idx) const;
		T* operator[](const std::string& title) const;
		~Collection();
	};

	template<typename T>
	std::ostream& operator <<(std::ostream& ostr, const Collection<T>& src);

	template<typename T>
	inline Collection<T>::Collection(const std::string& name) :m_desc {name} {;}

	template<typename T>
	inline const std::string& Collection<T>::name() const{
		return m_desc;
	}

	template<typename T>
	inline size_t Collection<T>::size() const{
		return m_arrSize;
	}

	template<typename T>
	inline void Collection<T>::setObserver(void(*observer)(const Collection<T>&, const T&)){
		m_funcPtr = observer;
	}

	template<typename T>
	inline Collection<T>& Collection<T>::operator+=(const T& item){
		bool found{ false };
		for (size_t i = 0; i < m_arrSize&&!found; i++){
			if (item.title() == m_arrPtr[i].title()){
				found = true;
			}
		}
		if (!found){
			T* temp = new T[m_arrSize+1];
			for (size_t i = 0; i < m_arrSize; i++){
				temp[i] = m_arrPtr[i];
			}
			delete[] m_arrPtr;
			m_arrSize++;
			m_arrPtr = temp;
			m_arrPtr[m_arrSize-1] = item;
			if (m_funcPtr) {
				m_funcPtr(*this, item);
			}
		}
		return *this;
	}

	template<typename T>
	inline T& Collection<T>::operator[](size_t idx) const{
		if (idx<0 || idx>=m_arrSize){
			throw std::out_of_range(std::string("Bad index [") + std::to_string(idx) + std::string("]. ") + std::string("Collection has [")+std::to_string(m_arrSize) + std::string("] items."));
		}
		else{
			return m_arrPtr[idx];
		}
	}

	template<typename T>
	inline T* Collection<T>::operator[](const std::string& title) const{
		size_t i{};
		T* res{};
		bool found{ false };
		for (; i < m_arrSize&&!found; i++){
			if (title == m_arrPtr[i].title()) {
				found = true;
			}
		}
		if (found) {
			res = (i == 0) ? &m_arrPtr[i] : &m_arrPtr[i - 1];
		}
		return res;
	}

	template<typename T>
	inline Collection<T>::~Collection(){
		delete[] m_arrPtr;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& ostr, const Collection<T>& src){
		for (size_t i = 0; i < src.size(); i++){
			ostr << src[i];
		}
		return ostr;
	}

}
#endif // !SDDS_COLLECTION_H
