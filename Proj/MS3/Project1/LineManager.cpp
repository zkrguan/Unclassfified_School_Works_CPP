#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
		// supposly we should have two funcs to delegate//
		// But to follow the guidelines, I implemented like this//
		std::ifstream ifstr (file);
		if (ifstr.is_open()){
			Utilities ut{};
			ut.setDelimiter();
			m_activeLine.resize(stations.size());
			auto master_index = m_activeLine.begin();
			while (ifstr.good()) {
				size_t next_pos{};
				bool more{ true };
				std::string line_words{};
				std::string token{};
				// src_index is defined for finding the existence of the token word in the source stations vec.//
				std::vector<Workstation*>::const_iterator src_index{};
				std::getline(ifstr, line_words, '\n');
				//Modified setDelimiter with a default value//
				token = ut.extractToken(line_words, next_pos, more);
				src_index = std::find_if(stations.begin(), stations.end(),
					[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; });
				// validation here to check if the src_index could not be found from the file//
				if (src_index == stations.end()){
					throw std::string("Program could not find the Word ") + token + std::string(" from the parameter stations during searching defining main stations");
				}
				else{
					// Don't forget these two iterators are always 1 level higher than whatever contained inside the containers//
					// On the first iteration, first element of the m_active line will be pointed to target of the src_index//
					(*master_index) = *src_index;
					// Reading the second part of the line// 
					if (more) {
						token = ut.extractToken(line_words, next_pos, more);
						auto sub_index = std::find_if(stations.begin(), stations.end(),
							[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; });
						if (sub_index == stations.end()){
							throw std::string("Program could not find the Word ") + token + std::string(" from the parameter stations during defining next station");
						}
						else{
							(*master_index)->setNextStation((*sub_index));
						}
					}
					// If more is false, that means this station is the last station//
					else {
						// specialised for reading the one station line//
						// This means the master station is pointing at nothing lol//
						(*master_index)->setNextStation();
					}
				}
				// so the master_index will move one size forward onto the next element//
				++master_index;
			}
			// validating the recorded data using Counters//
			auto index = m_activeLine.begin();
			unsigned fstStationCounter{};
			unsigned lstStationCounter{};
			std::for_each(m_activeLine.begin(), m_activeLine.end(),
				// First lambda inside the for_each algo's predicate
				[&](const Workstation* srcL1){
					if (std::find_if(m_activeLine.begin(), m_activeLine.end(),
						//Second lambda inside for each logic to compare with the 
						[=](const Workstation* src) {return srcL1 == src->getNextStation(); }) == m_activeLine.end()) {
						m_firstStation = *index; 
						++fstStationCounter;
					}
					if (srcL1->getNextStation() == nullptr)++lstStationCounter; 
					++index;
				});
			// check the counter and throw different error msg//
			// switch case is faster than the if right?//
			switch (fstStationCounter){
			case 1:
				break;
			default:
				throw std::string("Hey you have multiple FIRST station, the data from the file is corrupted");
				break;
			}
			
			switch (lstStationCounter){
			case 1:
				break;
			default:
				throw std::string("Hey you have multiple LAST station, the data from the file is corrupted");
				break;
			}
			m_cntCustomerOrder = g_pending.size();
		}
		// can not open file//
		else {
			throw std::string("Unable to open [") + file + "] file.";
		}

	}

	void LineManager::reorderStations()	{
		// I am impressed with myself with this logic//
		// Since the data is validated via the constructor, there must be a last_station, so no need to consider the std_find_if returns a activeline.end()//
		auto first_position = std::find_if(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* src) {return !src->getNextStation(); });
		// swap the last one to the last pos // 
		auto now_position = m_activeLine.end() - 1;
		std::iter_swap(first_position, now_position);
		//started from the second last index// 
		for (auto i = now_position; i != m_activeLine.begin() + 1; --i) {
			now_position = std::find_if(m_activeLine.begin(), i, [=](const Workstation* src) {return src->getNextStation() == *i; });
			std::iter_swap(now_position, i-1);
		}
	}

	bool LineManager::run(std::ostream& os){
		static size_t itr_cnt{};
		os << "Line Manager Iteration: " << ++itr_cnt << std::endl;
		// instead you should move it down by 1!!!//
		if (g_pending.size()){
			*(*m_activeLine.begin()) += std::move(*g_pending.begin());
			g_pending.pop_front();
		}
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* src) {src->fill(os); });
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* src) {src->attemptToMoveOrder(); });
		return m_cntCustomerOrder==g_completed.size()+g_incomplete.size();
	}

	void LineManager::display(std::ostream& os) const{
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* src) { src->display(os); });
	}

}

