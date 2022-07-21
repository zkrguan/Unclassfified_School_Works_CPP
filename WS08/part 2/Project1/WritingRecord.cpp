/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 8 Part 2
	Module:			WritingRecord
	File_Name:		WritingRecord.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#include <memory>
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		for (size_t i = 0; i < emp.size(); i++) {
			for (size_t j = 0; j < sal.size(); j++) {
				if (emp[i].id == sal[j].id) {
					EmployeeWage* temp = new EmployeeWage(emp[i].name, sal[j].salary);
					try {
						temp->rangeValidator();
						if (sal.LuhnsAlogrithm(sal[j].id)) {
							activeEmp += temp;
							delete temp;
						}
						else {
							throw std::string( "Your Luhn sucks lol\n");
						}
					}
					catch (std::string err) {
						// intercept the err and throw it again//
						// Because you want to throw the err to the main 
						// And you want to deallocate too.//
						delete temp;
						throw err;
					}
				}
			}
		}
		return activeEmp;
	}


	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		// The only difference is now you don't need to manually free the memory anymore.//
		GeneratingList<EmployeeWage> activeEmp;
		for (size_t i = 0; i < emp.size(); i++) {
			for (size_t j = 0; j < sal.size(); j++) {
				if (emp[i].id == sal[j].id) {
					std::unique_ptr<EmployeeWage> temp (new EmployeeWage(emp[i].name, sal[j].salary));
					temp->rangeValidator();
					if (sal.LuhnsAlogrithm(sal[j].id)) {
						activeEmp += temp;
					}
					else {
						throw std::string("Your Luhn sucks lol\n");
					}
				}
			}
		}
		return activeEmp;
	}
}