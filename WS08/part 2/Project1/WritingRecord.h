/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 8 Part 2
	Module:			WritingRecord
	File_Name:		WritingRecord.h
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/
#ifndef SDDS_WRITINGRECORD_H
#define SDDS_WRITINGRECORD_H

#include "GeneratingList.h"
#include "EmpProfile.h"

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal);
	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal);
}


#endif // SDDS_WRITINGRECORD_H

