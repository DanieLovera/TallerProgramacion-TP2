#include "SetMonitor.h"
#include "Url.h"
#include <utility>

SetMonitor::SetMonitor() : result { } { }

SetMonitor::SetMonitor(SetMonitor &&other) : 
			result {std::move(other.result)} { }

SetMonitor::~SetMonitor() { }

SetMonitor& SetMonitor::operator=(SetMonitor &&other) {
	if (this == &other) return *this;
	result = std::move(other.result);
	return *this;
}

void SetMonitor::insert(Url &&url) {
	std::lock_guard<std::mutex> lock(mutex);
	result.insert(std::move(url));
}

void SetMonitor::print() {
	std::lock_guard<std::mutex> lock(mutex);
	for (const Url &url : result) {
		url.print();
	}
}
