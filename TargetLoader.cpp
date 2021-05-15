#include "TargetLoader.h"
#include <iostream>
#include <string>
#include <utility>

TargetLoader::TargetLoader() { }

TargetLoader::TargetLoader(TargetLoader &&other) { }

TargetLoader::~TargetLoader() { }

TargetLoader& TargetLoader::operator=(TargetLoader &&other) {
	return *this;
}

void TargetLoader::loadQueue(BlockingQueue &blockingQueue, 
							 IfsMonitor &ifsMonitor) const {
	std::string domain;
	while (!ifsMonitor.readWord(domain)) {
		Url url(domain);
		blockingQueue.push(std::move(url));
	}
}

void TargetLoader::load(BlockingQueue &blockingQueue, std::string fileName) {
	IfsMonitor ifsMonitor(fileName);
	loadQueue(blockingQueue, ifsMonitor);
}
