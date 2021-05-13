#include "Dead.h"
#include <iostream>

Dead::Dead() : UrlState { } { }

Dead::Dead(Dead &&other) : UrlState {std::move(other)} { }

Dead::~Dead() { }

void Dead::print() const {
	std::cout << "-> dead";
}
