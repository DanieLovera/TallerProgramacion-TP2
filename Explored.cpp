#include "Explored.h"
#include <iostream>

Explored::Explored() : UrlState { } { }

Explored::Explored(Explored &&other) : UrlState {std::move(other)} { }

Explored::~Explored() { }

void Explored::print() const {
	std::cout << "-> explored";
}

void Explored::handleValidation(const Index &indexStructure, 
					  			std::size_t &offset, 
					 			std::size_t &size, 
					 			Url &context) { }

void Explored::handleExploration(IfsMonitor &ifsMonitor, 
					   const std::string &domainFilter, 
					   std::size_t &offset, 
					   std::size_t &size, 
					   std::string &result, 
					   Url &context) { }
