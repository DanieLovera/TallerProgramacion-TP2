#include "Worker.h"
#include "BlockingQueue.h"
#include "Index.h"
#include <iostream>

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
	
	/*if (size > 0) {
		//PROCESAMOS
		//SETEAMOS STATE DE URL A EXPLORED
	} else {
		//SETEAMOS STATE DE URL A DEAD
	}*/

	url.print();
	//std::cout << "PROBANDO PROBANDO" << std::endl;
	//std::cout << "PROBANDO PROBANDO2" << std::endl;
}
