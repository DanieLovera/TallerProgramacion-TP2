#include "Worker.h"
#include "BlockingQueue.h"
#include "Index.h"
#include <iostream>
#include <sstream>

Worker::Worker(Index &indexStructure, 
			   IfsMonitor &ifsMonitor, 
			   BlockingQueue &blockingQueue, 
			   std::set<Url> &result, 
			   std::string &domainFilter) :
	indexStructure {indexStructure}, 
	ifsMonitor {ifsMonitor}, 
	blockingQueue {blockingQueue},
	result {result}, 
	domainFilter {domainFilter}{ }
		
Worker::Worker(Worker &&other) :
							indexStructure {other.indexStructure}, 
							ifsMonitor {other.ifsMonitor}, 
							blockingQueue {other.blockingQueue},
							result {other.result}, 
							domainFilter {other.domainFilter}{ 
}

Worker::~Worker() { }

void Worker::pushUrls(std::string &urlsResult) {
	std::istringstream iss {std::move(urlsResult)};
	std::string readWord;
	while(iss >> readWord) {
		Url url {readWord};
		blockingQueue.push(std::move(url));
	}	
}

void Worker::run() {
	std::string urlsResult;
	std::size_t offset = 0;
	std::size_t size = 0;
	try {
		Url url = blockingQueue.pop();
		url.validate(indexStructure, offset, size);
		url.exploreLinks(ifsMonitor, domainFilter, offset, size, urlsResult);
		pushUrls(urlsResult);
		result.insert(std::move(url));
	
	} catch (ClosedQueueException &error) {
		std::cout << error.what() << std::endl;
		return;
	}
}
//std::cout << urlsResult << std::endl;
//std::cout << offset << " " << size << std::endl;