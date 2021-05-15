#include "Worker.h"
#include "BlockingQueue.h"
#include "SetMonitor.h"
#include <sstream>
#include <string>
#include <utility>

Worker::Worker(IndexMonitor &indexStructure, 
			   IfsMonitor &ifsMonitor, 
			   BlockingQueue &blockingQueue, 
			   SetMonitor &result,
			   const std::string &domainFilter) :
	indexStructure {indexStructure}, 
	ifsMonitor {ifsMonitor}, 
	blockingQueue {blockingQueue},
	result {result}, 
	domainFilter {domainFilter} { }
		
Worker::Worker(Worker &&other) :
							indexStructure {other.indexStructure}, 
							ifsMonitor {other.ifsMonitor}, 
							blockingQueue {other.blockingQueue},
							result {other.result}, 
							domainFilter {other.domainFilter} { }

Worker::~Worker() { }

void Worker::pushUrls(const std::string &urlsFetched) {
	std::istringstream iss(std::move(urlsFetched));
	std::string readWord;
	while(iss >> readWord) {
		Url url(readWord);
		blockingQueue.push(std::move(url));
	}	
}

void Worker::run() {
	bool keepWorking = true;

	while (keepWorking) {
		try {
			std::string urlsFetched;
			std::size_t offset = 0;
			std::size_t size = 0;

			Url url = blockingQueue.pop();
			url.validate(indexStructure, offset, size);
			url.exploreLinks(ifsMonitor, domainFilter, offset, size, urlsFetched);
			pushUrls(urlsFetched);
			result.insert(std::move(url));
		} catch(ClosedQueueException &error) {
			keepWorking = false;
		}
	}
}
