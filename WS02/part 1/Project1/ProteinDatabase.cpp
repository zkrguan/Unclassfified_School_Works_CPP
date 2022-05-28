#include <iostream>
#include <fstream>
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
		istr.ignore(1000, '\n');
		if (countMode){
			std::string temp{};
			std::getline(istr, temp, '>');
			if (temp.c_str()){
				recordNum++;
			}
		}
		else {
			std::getline(istr, recordedArr[recordNum], '>');
			if (recordedArr[recordNum].c_str()){
				recordNum++;
			}
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
	/// <summary>
	/// neeeeeeeeeeeeed to fix, this is definitely not right.. 
	/// Need to figure out why this is 
	/// why it has to be minus one
	/// what record it accidentally read. 
	/// </summary>
	/// <returns></returns>
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

}