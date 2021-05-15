#ifndef _SET_MONITOR_H_
#define _SET_MONITOR_H_

#include <set>
#include <mutex>
class Url;

class SetMonitor {
	private:
		std::set<Url> result;
		std::mutex mutex;
		SetMonitor(const SetMonitor &other) = delete;
		SetMonitor& operator=(const SetMonitor &other) = delete;
	
	public:
		SetMonitor();
		SetMonitor(SetMonitor &&other);
		SetMonitor& operator=(SetMonitor &&other);
		void insert(Url &&url);
		void print();
};

#endif // _SET_MONITOR_H_
