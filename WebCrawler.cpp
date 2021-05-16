#include "IfsMonitor.h"
#include "BlockingQueue.h"
#include "IndexMonitor.h"
#include "TargetLoader.h"
#include "SetMonitor.h"
#include "Workers.h"
#include <string>
#include <thread>
#include <chrono>

#define TARGET_FNAME argv[1]
#define ALLOWED_DOMAINS argv[2]
#define THREADS_NUMBER argv[3]
#define INDEX_FNAME argv[4]
#define PAGE_FNAME argv[5]
#define SLEEP_TIME argv[6]

int main(int argc, const char *argv[]) {
	TargetLoader targetLoader;
	const std::string domainFilter(ALLOWED_DOMAINS);
	Workers workers(atoi(THREADS_NUMBER));
	IndexMonitor indexStructure;
	IfsMonitor ifsMonitor(PAGE_FNAME);
	BlockingQueue blockingQueue;
	SetMonitor result;

	targetLoader.load(blockingQueue, TARGET_FNAME);
	indexStructure.load(INDEX_FNAME);
	workers.start(indexStructure, ifsMonitor, blockingQueue, result, domainFilter);
	std::this_thread::sleep_for(std::chrono::seconds(atoi(SLEEP_TIME)));
	blockingQueue.close();
	workers.join();
	result.print();
	return 0;
}
