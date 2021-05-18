#include "IndexMonitor.h"
#include "IfsMonitor.h"
#include <string>
#include <vector>
#include <utility>

#define PAGE_OFFSET 0
#define PAGE_SIZE 1
#define INDEX_PARAMS 2

IndexMonitor::IndexMonitor() : index {} { }

IndexMonitor::~IndexMonitor() { }

void IndexMonitor::load(const std::string &fileName) {
	IfsMonitor ifsMonitor(fileName);
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

		std::lock_guard<std::mutex> lock(mutex);
		index[std::move(url)] = std::move(mapped);
	}
}

void IndexMonitor::lookUp(const Url &url, 
				   		  std::size_t &offset, 
				   		  std::size_t &size) const {
	try {
		const std::vector<std::size_t> &mapped = index.at(url);
		offset = mapped[0];
		size = mapped[1];
	} catch(const std::out_of_range &exception) {
		size = 0;
		offset = 0;
	}
}
