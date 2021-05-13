#include <iostream>
#include "Url.h"
#include "Ready.h"
#include "Dead.h"
#include "Explored.h"

Url::Url() : Url { " " } { }

Url::Url(std::string url) : url {url}, state {new Ready { }} { }

Url::Url(Url &&other) : url {std::move(other.url)}, state {other.state} { 
	other.state = nullptr;
}

Url::~Url() { 
	freeIfNotNullState();
}

Url& Url::operator=(Url &&other) {
	if (this == &other) return *this;
	freeIfNotNullState();
	url = std::move(other.url);
	state = other.state;
	other.state = nullptr;

	return *this;
}

bool Url::equals(const Url &other) const {
	return this->url.compare(other.url) == 0;
}

bool Url::operator<(const Url &other) const {
	return this->url < other.url;
}

void Url::print() const {
	std::cout << url << " ";
	state->print();
	std::cout << std::endl;
}

void Url::freeIfNotNullState() {
	if (state != nullptr) {
		delete state;
	}
}

void Url::statusToExplored() {
	freeIfNotNullState();
	state = new Explored { };
}

void Url::statusToDead() {
	freeIfNotNullState();
	state = new Dead { };
}

bool Url::isValid() {
	return url != " ";
}
