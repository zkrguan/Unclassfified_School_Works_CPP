#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"
namespace sdds {
	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
		void deallocate();
	public:
		CustomerOrder() {};
		CustomerOrder(const std::string src);
		// Disabled copy //
		CustomerOrder(const CustomerOrder& src) { throw "Copying is not allowed\n"; }
		CustomerOrder& operator = (const CustomerOrder& src) = delete;

		// move//
		CustomerOrder& operator = (CustomerOrder&& src)noexcept;
		CustomerOrder(CustomerOrder&& src)noexcept;
		// Destructor//
		~CustomerOrder();

		bool isOrderFilled() const ;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

	};
}

#endif // !SDDS_CUSTOMERORDER_H

