/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 4 Part 2
	Module:			ConfirmOrder
	File_Name:		ConfirmOrder.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H
#include <iostream>
#include "Toy.h"

namespace sdds {
	class ConfirmOrder {
		const Toy** m_Tppr{};
		size_t m_ArrSize{};
	public:
		ConfirmOrder& operator += (const Toy& toy);
		ConfirmOrder& operator -= (const Toy& toy);
		
		ConfirmOrder() {};
		ConfirmOrder(const ConfirmOrder& src);
		ConfirmOrder& operator = (const ConfirmOrder& src);
		ConfirmOrder(ConfirmOrder&& src)noexcept;
		ConfirmOrder& operator = (ConfirmOrder&& src)noexcept;
		virtual ~ConfirmOrder();

		friend std::ostream& operator << (std::ostream& ostr, const ConfirmOrder& src);
	};
}
#endif // !SDDS_CONFIRMORDER_H
