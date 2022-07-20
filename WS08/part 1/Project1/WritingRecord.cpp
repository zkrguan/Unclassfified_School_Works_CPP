#include <algorithm>
#include <iostream>
#include <string>
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		for (size_t i = 0; i < emp.size(); i++){
			for (size_t j = 0; j < sal.size(); j++){
				if (emp[i].id == sal[j].id) {
					EmployeeWage* temp = new EmployeeWage(emp[i].name, sal[j].salary);
					try	{
						temp->rangeValidator();
						if (sal.LuhnsAlogrithm(sal[j].id)){
							activeEmp += temp;
							delete temp;
						}
					}
					catch (std::string err)	{
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
}