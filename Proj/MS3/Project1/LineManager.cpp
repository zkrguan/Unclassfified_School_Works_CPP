#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
		std::ifstream ifstr (file);
		if (ifstr.is_open()){
			while (ifstr.good()){
				size_t next_pos{};
				bool more{ true };
				std::string line_words{};
				std::string token{};
				std::getline(ifstr, line_words, '\n');
				Utilities ut{};
				ut.setDelimiter();
				// a local lambda? so less repetition?//		
				token = ut.extractToken(line_words, next_pos, more);
				if (more){
					//// if the token does not match any record in the record//
					// Any of should be better here//
					if (m_activeLine.end() == std::find_if(m_activeLine.begin(), m_activeLine.end(),
						[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; })){
						/*create a new record for the active line*/
						m_activeLine.push_back(new Workstation(token));
					}

				}
				
				if (more){
					auto master_index = std::find_if(m_activeLine.begin(), m_activeLine.end(),
						[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; });
					// override the token since it is useless now//
					token = ut.extractToken(line_words, next_pos, more);
					


					(*master_index)->setNextStation(
				}
				else{

				}
			}
		}
		else {
			throw std::string("Unable to open [") + file + "] file.";
		}
		
	}
}

