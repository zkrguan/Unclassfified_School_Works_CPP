#include <string>
#include <exception>
#include "Utilities.h"
namespace sdds {
	char Utilities::m_delimiter = '\n';
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	
	size_t Utilities::getFieldWidth() const { return m_widthField; }

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
		size_t pos{};
		std::string res{};
		pos = str.find(m_delimiter, next_pos);
		if (pos==next_pos){
			more = false;
			throw std::string("Delimiter is found at the next_pos");
		}
		else{
			if (pos!=std::string::npos){
				// use guan's trimmer latter// 
				res = str.substr(next_pos, pos - next_pos);
				next_pos = pos+1;
				more = true;
			}
			else{
				res = str.substr(next_pos, str.find('\n') - next_pos);
				more = false;
			}
			m_widthField = m_widthField < res.length() ? res.length() : m_widthField;
		}
		return guansTrimmerV3(res);
	}

	void Utilities::setDelimiter(char newDelimiter='|') { m_delimiter = newDelimiter; }

	char Utilities::getDelimiter(){return m_delimiter;}

	std::string& guansTrimmerV3(std::string& src) {
		if (src.c_str()) {
			src.erase(0, src.find_first_not_of(' '));
			src.erase(src.find_last_not_of(' ') + 1);
		}
		return src;
	}



	


}