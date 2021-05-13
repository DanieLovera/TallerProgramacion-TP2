#include "Explored.h"
#include <iostream>

Explored::Explored() : UrlState { } { }

Explored::Explored(Explored &&other) : UrlState {std::move(other)} { }

Explored::~Explored() { }

void Explored::print() const {
	std::cout << "-> explored";
}
