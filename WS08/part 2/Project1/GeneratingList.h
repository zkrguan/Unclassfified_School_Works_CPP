/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 8 Part 2
	Module:			GeneratingList
	File_Name:		GeneratingList.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
		bool LuhnsAlogrithm(const std::string src) const {

			size_t num_digits = src.length();
			int sum = (int)src[num_digits - 1] - 48;
			unsigned parity = (num_digits - 2) % 2;
			// I was stuck on the iterating time for a long long time//
			// God it was suffering//
			for (size_t i = 0; i < (num_digits - 1); i++) {
				int digit = (int)src[i] - 48;
				if (i % 2 == parity) {
					digit = digit * 2;
				}
				if (digit > 9) {
					digit -= 9;
				}
				sum += digit;
			}
			return (sum % 10) == 0;
		}

		//TODO: Overload the += operator with a smart pointer
		// as a second operand.
		// Very delicate process, it has to be a reference to a unqiue pointer then it will work. 
		// Otherwise, it won't compile//
		void operator += (std::unique_ptr<T>& srcPtr) {
			// dereference //
			list.push_back(*srcPtr);
		}
		

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.

		void operator += (T* srcPtr){
			// dereference //
			list.push_back(*srcPtr);
		}
		
		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
