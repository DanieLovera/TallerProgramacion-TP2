#include "Worker.h"
#include "BlockingQueue.h"
#include "Index.h"
#include <iostream>
#include <sstream>

Worker::Worker(Index &indexStructure, 
			   IfsMonitor &ifsMonitor, 
			   BlockingQueue &blockingQueue, 
			   std::set<Url> &result) :
	indexStructure {indexStructure}, 
	ifsMonitor {ifsMonitor}, 
	blockingQueue {blockingQueue},
	result {result} { }
		
Worker::Worker(Worker &&other) :
							indexStructure {other.indexStructure}, 
							ifsMonitor {other.ifsMonitor}, 
							blockingQueue {other.blockingQueue},
							result {other.result} { 
}

Worker::~Worker() { }

void Worker::run() {
	Url url;
	std::size_t offset = 0;
	std::size_t size = 0;
	blockingQueue.pop(url);
	indexStructure.lookUp(url, offset, size);
	//std::cout << offset << " " << size << std::endl;
	//std::cout << url.url << std::endl;

	/*if (size > 0) {
		char *buffer = new char[size + 1];
		ifsMonitor.readBlockFromTo(buffer, offset, size);
		buffer[size] = '\0';
		std::string string {buffer};
		std::istringstream iss {std::move(string)};
		std::string word;

		while(iss >> word) {
			std::size_t found = word.find(url.url);
			//word.find(url.url);
			if (found != std::string::npos) {
		//		url.statusToExplored();
		//		result.insert(std::move(word));
			//	std::cout << url.url << std::endl;
			}
			//std::cout << word << std::endl;
		}

		if (buffer != nullptr) delete[] buffer;
	} else {
		url.statusToDead();
		if (url.isValid()) result.insert(std::move(url));
	}*/
}
