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
	FileReader fileReader {fileName};
	loadMap(fileReader);
}

void Index::loadMap(FileReader &fileReader) {
	std::string key;
	std::string buffer;
	const unsigned char buffer_base = 16;

	while (!fileReader.readWord(key)) {
		std::vector<std::size_t> mapped{0,0};

		fileReader.readWord(buffer);
		mapped[PAGE_OFFSET] = std::stoul(buffer, nullptr, buffer_base);
		fileReader.readWord(buffer);
		mapped[PAGE_SIZE] = std::stoul(buffer, nullptr, buffer_base);
		index[key] = std::move(mapped);
		std::cout << key << ' ' << index[key][0] << ' ' << index[key][1] << std::endl;
	}
}
