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

/* 
#define TARGET_FNAME argv[1]
#define ALLOWED_DOMAINS argv[2]
#define THREADS_NUMBER argv[3]
#define INDEX_FNAME argv[4]
#define PAGE_FNAME argv[5]
#define SLEEP_TIME argv[6]
*/

int main(int argc, const char *argv[]) {
	IfsMonitor ifsMonitor {PAGE_FNAME}; //Ifstream es compartido entre hilos
	BlockingQueue blockingQueue; //Cola bloqueante es compartida entre hilos
	Index indexStructure; //La estructura index es compartida entre hilos
	TargetLoader targetLoader;
	std::set<Url> result;
	std::string domainFilter {"savewalterwhite.com"};

	indexStructure.load(INDEX_FNAME);
	targetLoader.load(blockingQueue, TARGET_FNAME);

	Worker worker {indexStructure, ifsMonitor, blockingQueue, result, domainFilter};
	//Worker worker2 {indexStructure, ifsMonitor, blockingQueue, result, domainFilter};
	//Worker worker3 {indexStructure, ifsMonitor, blockingQueue, result, domainFilter};
	//worker2.start();
	//worker3.start();
	worker.start();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	blockingQueue.close();

	worker.join();
	//worker2.join();
	//worker3.join();

	for (const Url &url : result) {
		url.print();
	}

	return 0;
}
