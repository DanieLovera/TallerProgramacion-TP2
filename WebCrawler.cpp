#include "Index.h"
#include "Url.h"
#include "Worker.h"
#include "BlockingQueue.h"
#include "TargetLoader.h"
#include "Index.h"

#include <iostream>
#include <thread>
#include <chrono>
#include "Url.h"

#define TARGET_FNAME argv[1]
#define INDEX_FNAME argv[2]
#define PAGE_FNAME argv[3]

int main(int argc, const char *argv[]) {
	IfsMonitor ifsMonitor {PAGE_FNAME}; //Ifstream es compartido entre hilos
	BlockingQueue blockingQueue; //Cola bloqueante es compartida entre hilos
	Index indexStructure; //La estructura index es compartida entre hilos
	TargetLoader targetLoader;
	std::set<Url> result;

	indexStructure.load(INDEX_FNAME);
	targetLoader.load(blockingQueue, TARGET_FNAME);
	

	Worker worker {indexStructure, ifsMonitor, blockingQueue, result};
	Worker worker2 {indexStructure, ifsMonitor, blockingQueue, result};
	worker.start();
	worker2.start();


	worker.join();
	worker2.join();

	return 0;
}
