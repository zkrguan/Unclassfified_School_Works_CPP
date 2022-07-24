#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {

	void LineManager::deallocate(){
		for (auto& x : m_activeLine) {
			delete x;
		}
		m_firstStation = nullptr;
		m_cntCustomerOrder = 0;
	}
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
		std::ifstream ifstr (file);
		m_activeLine.resize(stations.size());
		auto master_index = m_activeLine.begin();
		if (ifstr.is_open()){
			while (ifstr.good()) {
				size_t next_pos{};
				bool more{ true };
				std::string line_words{};
				std::string token{};
				std::getline(ifstr, line_words, '\n');
				Utilities ut{};
				ut.setDelimiter();
				std::vector<Workstation*>::const_iterator src_index{};
				//auto master_index = m_activeLine.begin();
				token = ut.extractToken(line_words, next_pos, more);
				src_index = std::find_if(stations.begin(), stations.end(),
					[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; });
				// get ready to let the pointer pointing to something//
				//master_index = std::find_if(m_activeLine.begin(), m_activeLine.end(),
				//	[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; });
				(*master_index) = *src_index;
				// index will be useful for updating the pointing to station..//
				// Last time use the current token, feel free to override// 
				//reading the second part of the line// 
				if (more) {
					token = ut.extractToken(line_words, next_pos, more);
					auto sub_index = std::find_if(stations.begin(), stations.end(),
						[=](const Workstation* srcPtr) {return srcPtr->getItemName() == token; }); 
					(*master_index)->setNextStation((*sub_index));
				}
				else{
					// specialised for reading the one station line//
					// This means the master station is pointing at nothing lol//
					(*master_index)->setNextStation();
				}
				++master_index;
			}
			m_cntCustomerOrder = g_pending.size();

		}
		else {
			throw std::string("Unable to open [") + file + "] file.";
		}

	}

	void LineManager::reorderStations()	{
		//// create a new vector//
		//std::vector<Workstation*> temp (m_activeLine.size());
		//// firstly find the last_pos of the vector
		//temp.push_back(new Workstation((*last_index)->getItemName()));
 
		auto current_index = std::find_if(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* src) {return !src->getNextStation(); });
		// swap the last one to the last pos // 
		// might not work//
		auto vector_position = m_activeLine.end() - 1;
		std::iter_swap(current_index, vector_position);
		//started from the second last index// 
		for (auto i = vector_position; i != m_activeLine.begin() + 1; --i) {
			current_index = std::find(m_activeLine.begin(), i, (*i)->getNextStation());
			std::iter_swap(current_index, i);
		}
		//std::reverse(m_activeLine.begin(),m_activeLine.end());
		m_firstStation = (*m_activeLine.begin());
	}

	bool LineManager::run(std::ostream& os){
		static size_t itr_cnt{};
		os << "Line Manager Iteration: " << ++itr_cnt << std::endl;
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* src) {*src += std::move(*g_pending.begin()); });
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* src) {src->fill(os); });
		g_pending.pop_front();
		return !g_pending.size();
	}

	void LineManager::display(std::ostream& os) const{
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* src) { src->display(os); });
	}

	//LineManager::~LineManager(){
	//	for (auto& x : m_activeLine) {
	//		delete x;
	//	}
}

