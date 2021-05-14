#include "Url.h"
#include "Index.h"
#include "Ready.h"
#include "Dead.h"
#include "Explored.h"
#include "IfsMonitor.h"
#include <iostream>

Url::Url() : Url { " " } { }

Url::Url(std::string url) : url {url}, state {new Ready {}} { }

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

void Url::setState(UrlState *state) {
	freeIfNotNullState();
	this->state = state;
}

void Url::validate(const Index &indexStructure, 
				   std::size_t &offset, 
				   std::size_t &size) {
	state->handleValidation(indexStructure, offset, size, *this);
}

void Url::exploreLinks(IfsMonitor &ifsMonitor, 
					   const std::string &domainFilter, 
					   std::size_t &offset, 
					   std::size_t &size,
					   std::string &result) {
	state->handleExploration(ifsMonitor, domainFilter, 
							 offset, size, 
							 result, *this);
}

bool Url::isSubUrl(const std::string url, const std::string &domainFilter) {
	bool status = false;
	std::size_t found = url.find("http://");

	if (found != std::string::npos) {
		status = filter(url, domainFilter);
	}
	return status;
}

bool Url::filter(const std::string url, const std::string &domainFilter) {
	bool status = false;
	std::size_t found = url.find(domainFilter);

	if (found != std::string::npos) {
		status = true;
	}
	return status;
}
