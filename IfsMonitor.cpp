#include "IfsMonitor.h"
#include <iostream>
#include <string>
#include <utility>

IfsMonitor::IfsMonitor(const std::string &fileName) : ifs {fileName} { }

IfsMonitor::~IfsMonitor() {
	closeIfOpen();
}

// cppcheck-suppress constParameter
bool IfsMonitor::readWord(std::string &buffer) {
	std::lock_guard<std::mutex> lock(mutex);
	return (ifs >> buffer).eof();
}

void IfsMonitor::readBlockFromTo(char *buffer, 
								 const std::size_t from, 
								 const std::size_t to) {
	std::lock_guard<std::mutex> lock(mutex);
	ifs.seekg(from);
	ifs.read(buffer, to);
}

void IfsMonitor::closeIfOpen() {
	if (ifs.is_open()) {
		ifs.close();
	}
}
