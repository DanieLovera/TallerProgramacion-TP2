#include "IfsMonitor.h"
#include <iostream>
#include <string>

IfsMonitor::IfsMonitor(const std::string &fileName) : ifs {fileName} { }

IfsMonitor::IfsMonitor(IfsMonitor &&other) : ifs {std::move(other.ifs)} { }

IfsMonitor::~IfsMonitor() {
	closeIfOpen();
}

IfsMonitor& IfsMonitor::operator=(IfsMonitor &&other) {
	if (this == &other) return *this;
	closeIfOpen();
	ifs = std::move(other.ifs);
	return *this;
}

bool IfsMonitor::readLine(std::string &buffer) {
	return std::getline(ifs, buffer).eof(); 
}

bool IfsMonitor::readWord(std::string &buffer) {
	return (ifs >> buffer).eof();
}

void IfsMonitor::readBlockFromTo(char *buffer, 
								 std::size_t from, 
								 std::size_t to) {
	std::unique_lock<std::mutex> lock(m);
	ifs.seekg(from);
	ifs.read(buffer, to);
}

void IfsMonitor::closeIfOpen() {
	if (ifs.is_open()) {
		ifs.close();
	}
}
