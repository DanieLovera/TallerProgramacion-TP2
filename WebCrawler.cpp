#include "IfsMonitor.h"
#include "BlockingQueue.h"
#include "IndexMonitor.h"
#include "TargetLoader.h"
#include "SetMonitor.h"
#include "Worker.h"
#include <chrono>
#include <string>
#include <vector>

#define TARGET_FNAME argv[1]
#define ALLOWED_DOMAINS argv[2]
#define THREADS_NUMBER argv[3]
#define INDEX_FNAME argv[4]
#define PAGE_FNAME argv[5]
#define SLEEP_TIME argv[6]

int main(int argc, const char *argv[]) {
	IfsMonitor ifsMonitor(PAGE_FNAME);
	BlockingQueue blockingQueue;
	IndexMonitor indexStructure;
	TargetLoader targetLoader;
	SetMonitor result;
	const std::string domainFilter(ALLOWED_DOMAINS);

	indexStructure.load(INDEX_FNAME);
	targetLoader.load(blockingQueue, TARGET_FNAME);

	std::vector<Worker*> workers(atoi(THREADS_NUMBER));

	for (int i = 0; i < atoi(THREADS_NUMBER); i++) {
		Worker* worker = new Worker(indexStructure, 
									ifsMonitor, 
									blockingQueue, 
									result, 
									domainFilter);
		workers[i] = worker;
	}

	for (int i = 0; i < atoi(THREADS_NUMBER); i++) {
		workers[i]->start();
	}

	std::this_thread::sleep_for(std::chrono::seconds(atoi(SLEEP_TIME)));
	blockingQueue.close();

	for (int i = 0; i < atoi(THREADS_NUMBER); i++) {
		workers[i]->join();
		delete workers[i];
	}

	result.print();

	return 0;
}
