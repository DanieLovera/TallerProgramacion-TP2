#include "IfsMonitor.h"

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

void IfsMonitor::closeIfOpen() {
	if (ifs.is_open()) {
		ifs.close();
	}
}
