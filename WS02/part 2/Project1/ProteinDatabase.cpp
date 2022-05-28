/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 2 Part 2
	Module:			ProteinDatabase
	File_Name:		ProteinDatabase.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215

*/
#include <iostream>
#include <fstream>
#include <string>
#include "ProteinDatabase.h"

namespace sdds {
	// literally slap my self for forgetting the format to initialize the static variable//
	size_t ProteinDatabase:: recordNum = 0;

	ProteinDatabase::ProteinDatabase(std::string fileName) {
		std::ifstream fp{};
		fp.open(fileName.c_str());
		// the whole process is just counting the record num//
		while (!fp.eof()){
			read(fp);
		}
		// if there is anything to read//
		if (recordNum){
			// now it is for allocating memory//
			recordedArr = new std::string[recordNum];
			// move the cursor up to the begining and reset the fp's state//
			// TO THE FUTURE ME, USE THE IFSTREAM OBJECT. CLEAR BEFORE SEEKG//
			fp.clear();
			fp.seekg(0, std::ios::beg);
			recordNum = 0;
			while (!fp.eof()) {
				read(fp, false);
			}
		}
		
	}

	std::istream& ProteinDatabase::read(std::istream& istr,bool countMode) {
		// Ignore the first line immediately//
		istr.ignore(1000, '\n');
		if (countMode){
			// counting by writting this into a temp string and discard it//
			// So we could get the accurate record number first//
			// Then do the allocation// 
			std::string temp{};
			std::getline(istr, temp, '>');
			if (temp.c_str()){
				recordNum++;
			}
		}
		else {
			std::getline(istr, recordedArr[recordNum], '>');
			if (recordedArr[recordNum].c_str())
				guanStringTrimmer(recordedArr[recordNum]);
			recordNum++;
		}
		return istr;
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& src){
		*this = src;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src){
		if (this!=&src){
			delete[] this->recordedArr;
			if (src.recordedArr){
				this->recordedArr = new std::string[this->recordNum];
				for (unsigned i = 0u; i < this->recordNum; i++){
					this->recordedArr[i] = src.recordedArr[i];
				}
			}
		}
		return *this;
	}

	ProteinDatabase::~ProteinDatabase(){
		delete[] recordedArr;
	}
	ProteinDatabase::ProteinDatabase(ProteinDatabase&& src)noexcept {
		*this = std::move(src);
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src)noexcept{
		if (this!=&src){
			delete[] this->recordedArr;
			this->recordedArr = nullptr;
			// shallow copy if the src is not empty//
			if (src.recordedArr){
				// move the resource from the src to the current object//
				this->recordedArr = src.recordedArr;
				// let the null terminator pointing to the nullptr//
				//else it will cause some memory thrown// 
				src.recordedArr = nullptr;
			}
			
		}
		return *this;
	}

	size_t ProteinDatabase::size() const {
		return recordNum;
	}


	std::string ProteinDatabase::operator[](size_t index) const{
		std::string res{};
		if (index<recordNum && index>=0){
			if (recordedArr)
			res = recordedArr[index];
		}
		return res;
	}

	// Created a helper functions to trim off the newline chars from the reading file//
	std::string& guanStringTrimmer(std::string& src) {
		unsigned index = 0;
		do {
			if (src.c_str()[index] == '\n') 
				src.erase(index,1);
			index++;
		} while (index<src.length());
		return src;
	}
}