#include "Index.h"

#include <iostream>
#include <string>

#define PAGE_OFFSET 0
#define PAGE_SIZE 1

Index::Index() : index {} { }

Index::Index(Index &&other) : index {std::move(other.index)} { }

Index::~Index() { }

Index& Index::operator=(Index &&other) {
	if (this == &other) return *this;
	this->index = std::move(other.index);

	return *this;
}

void Index::load(const std::string &fileName) {
	IfsMonitor ifsMonitor {fileName};
	loadIndex(ifsMonitor);
}

void Index::loadIndex(IfsMonitor &ifsMonitor) {
	std::string key;
	std::string buffer;
	const unsigned char buffer_base = 16;

	while (!ifsMonitor.readWord(key)) {
		Url url {key};
		std::vector<std::size_t> mapped {0,0};
		//Url url_copy {key};

		ifsMonitor.readWord(buffer);
		mapped[PAGE_OFFSET] = std::stoul(buffer, nullptr, buffer_base);
		ifsMonitor.readWord(buffer);
		mapped[PAGE_SIZE] = std::stoul(buffer, nullptr, buffer_base);
		index[std::move(url)] = std::move(mapped);
		//std::cout << ' ' << index.at(url_copy)[0] << ' ' << index.at(url_copy)[1] << std::endl;
	}
}
