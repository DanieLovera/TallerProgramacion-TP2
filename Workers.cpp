#include "Workers.h"
#include "Worker.h"
#include <string>
#include <utility>

Workers::Workers(const std::size_t nworkers) : 
					nworkers {nworkers}, 
					workers {nworkers} { }

Workers::Workers(Workers &&other) : nworkers {other.nworkers}, 
						   workers {std::move(other.workers)} { }
		
Workers& Workers::operator=(Workers &&other) {
	if (this == &other) return *this;
	workers = std::move(other.workers);
	return *this;
}

void Workers::uninitWorkers() {
	for(std::size_t i = 0; i < nworkers; i++) {
		if (workers[i] != nullptr) {
			delete workers[i];
		}
	}	
}

Workers::~Workers() {
	if (!workers.empty()) {
		uninitWorkers();
	}
}

void Workers::initWorkers(IndexMonitor &indexMonitor, 
				   		  IfsMonitor &ifsMonitor, 
				   		  BlockingQueue &blockingQueue, 
				   		  SetMonitor &result, 
				   		  const std::string &domainFilter) {
	for (std::size_t i = 0; i < nworkers; i++) {
		if (workers[i] != nullptr) delete workers[i];
		Worker* worker = new Worker(indexMonitor, 
									ifsMonitor, 
									blockingQueue, 
									result, 
									domainFilter);
		workers[i] = worker;
	}
}

void Workers::startAllWorkers() {
	for (std::size_t i = 0; i < nworkers; i++) {
		workers[i]->start();
	}	
}

void Workers::start(IndexMonitor &indexMonitor, 
				   	IfsMonitor &ifsMonitor, 
				   	BlockingQueue &blockingQueue, 
				   	SetMonitor &result, 
				   	const std::string &domainFilter) {
	initWorkers(indexMonitor, ifsMonitor, blockingQueue, result, domainFilter);
	startAllWorkers();
}

void Workers::join() {
	for(std::size_t i = 0; i < nworkers; i++) {
		workers[i]->join();
	}
}
