#include <iostream>
#include "Url.h"

Url::Url() { }

Url::Url(std::string url) : url {url} { }

Url::Url(Url &&other) : url {std::move(other.url)} { }

Url::~Url() { }

Url& Url::operator=(Url &&other) {
	if (this == &other) return *this;
	url = std::move(other.url);

	return *this;
}

bool Url::equals(const Url &other) const {
	return this->url.compare(other.url) == 0;
}

bool Url::operator<(const Url &other) const {
	return this->url < other.url;
}

void Url::print() const {
	std::cout << url << std::endl;
}

Url Url::clone() const {
	Url urlCopy {url};
	return urlCopy;
}
