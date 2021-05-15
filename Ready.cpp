#include "Ready.h"
#include "Dead.h"
#include "Explored.h"
#include "Url.h"
#include "IfsMonitor.h"
#include "IndexMonitor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

Ready::Ready() : UrlState { } { }

Ready::Ready(Ready &&other) : UrlState {std::move(other)} { }

Ready::~Ready() { }

void Ready::print() const {
	std::cout << "-> ready";
}

void Ready::handleValidation(const IndexMonitor &indexStructure, 
							 std::size_t &offset, 
							 std::size_t &size, 
							 Url &context) {
	indexStructure.lookUp((const Url&)context, offset, size);
	if (size == 0) context.setState(new Dead {});
}

void Ready::handleExploration(IfsMonitor &ifsMonitor, 
							  const std::string &domainFilter, 
							  std::size_t &offset, 
							  std::size_t &size, 
							  std::string &result, 
							  Url &context) {
	char *buffer = new char[size + 1];
	ifsMonitor.readBlockFromTo(buffer, offset, size);
	buffer[size] = '\0';
	std::string string(buffer);

	std::istringstream iss(std::move(string));
	std::string readWord;
	while(iss >> readWord) {
	    if (context.isSubUrl(readWord, domainFilter)) {
	    	result.append(readWord);
	    	result.append(" ");
	    }
	}
	context.setState(new Explored {});
	delete [] buffer;
}
