#ifndef SDDS_TIMEDTASK_H
#define SDDS_TIMEDTASK_H
#include <chrono>
#include <string>
#include <iostream>
#include <ratio>
namespace sdds {
	const int MAX_TASKS = 10;
	typedef std::chrono::steady_clock::time_point tp;
	typedef std::chrono::steady_clock::duration duration;
	
	class TimedTask {
	private:
		static int storedRecord;
		tp startTime{};
		tp endTime{};
		// used the nameless class learned from sup vids//
		class {
			std::string taskName{};
			std::string timeUnit{};
			duration timeElapsed{};
		public:
			void setTaskName(const char* srcName) {
				taskName = srcName;
				timeUnit = "nanoseconds";
			}
			duration getTaskTime() const{
				return std::chrono::duration_cast<std::chrono::nanoseconds>(timeElapsed);
			}
			const std::string getTaskName() const{
				return taskName;
			}
			void setTimeElapsed(const duration& src) {
				timeElapsed = src;
			}

		} task[MAX_TASKS]{};

	public:
		TimedTask() {};
		void startClock();
		void stopClock();
		void addTask(const char* srcName);
		static int getStoredNum();
		tp getStartTime()const;
		tp getEndTime()const;
		// private or public//
		friend std::ostream& operator << (std::ostream& ostr, const TimedTask& src);

	};
	
	
}
#endif // !SDDS_TIMEDTASK_H

