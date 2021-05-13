#include "Ready.h"
#include <iostream>

Ready::Ready() : UrlState { } { }

Ready::Ready(Ready &&other) : UrlState {std::move(other)} { }

Ready::~Ready() { }

void Ready::print() const {
	std::cout << "Estado READY" << std::endl;
}
