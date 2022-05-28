#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include "TimedTask.h"

namespace sdds {
	// set the default value of that static variable outside the class//
	int TimedTask::storedRecord = 0;

	void TimedTask::startClock(){
		startTime = std::chrono::steady_clock::now();
	}

	void TimedTask::stopClock(){
		endTime = std::chrono::steady_clock::now();
	}

	void TimedTask::addTask(const char* srcName){
		this->task[storedRecord].setTaskName(srcName);
		this->task[storedRecord].setTimeElapsed(endTime-startTime);
		storedRecord++;
	}

	tp TimedTask:: getStartTime()const {
		return startTime;
	}
	
	tp TimedTask::getEndTime()const {
		return endTime;
	}

	int TimedTask::getStoredNum(){
		return storedRecord;
	}

	std::ostream& operator<<(std::ostream& ostr, const TimedTask& src){
		ostr << "--------------------------\n" << "Execution Times:\n" << "--------------------------\n";
		for (int i = 0; i < TimedTask::getStoredNum();i++) {
			ostr << std::left << std::setw(21) << src.task[i].getTaskName()
				<< std::right << std::setw(13) << src.task[i].getTaskTime().count() << "\n";		
		}
		ostr << "--------------------------\n";
		return ostr;
	}

}