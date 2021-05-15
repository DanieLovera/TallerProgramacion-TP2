#include "Dead.h"
#include <iostream>
#include <string>
#include <utility>

Dead::Dead() : UrlState { } { }

Dead::Dead(Dead &&other) : UrlState {std::move(other)} { }

Dead::~Dead() { }

void Dead::print() const {
	std::cout << "-> dead";
}

void Dead::handleValidation(const Index &indexStructure, 
							std::size_t &offset, 
							std::size_t &size, 
							Url &context) { }

void Dead::handleExploration(IfsMonitor &ifsMonitor, 
					   const std::string &domainFilter, 
					   std::size_t &offset, 
					   std::size_t &size, 
					   std::string &result, 
					   Url &context) { }
