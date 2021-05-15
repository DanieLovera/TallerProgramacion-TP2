#include "Index.h"

#include <iostream>
#include <string>
#include <vector>

#define INDEX_PARAMS 2
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

void Index::loadIndex(IfsMonitor &ifsMonitor) {
	std::string key;
	std::string buffer;
	const unsigned char buffer_base = 16;

	while (!ifsMonitor.readWord(key)) {
		Url url(key);
		std::vector<std::size_t> mapped(INDEX_PARAMS, 0);
		ifsMonitor.readWord(buffer);
		
		mapped[PAGE_OFFSET] = std::stoul(buffer, nullptr, buffer_base);
		ifsMonitor.readWord(buffer);
		mapped[PAGE_SIZE] = std::stoul(buffer, nullptr, buffer_base);
		index[std::move(url)] = std::move(mapped);
	}
}

void Index::load(const std::string &fileName) {
	IfsMonitor ifsMonitor(fileName);
	loadIndex(ifsMonitor);
}

void Index::lookUp(Url &url, std::size_t &offset, std::size_t &size) const {
	try {
		const std::vector<std::size_t> &mapped = index.at(url);
		offset = mapped[0];
		size = mapped[1];
	} catch(const std::out_of_range &exception) {
		size = 0;
		offset = 0;
	}
}
