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
	TargetLoader targetLoader;
	Index indexStructure;
	targetLoader.load(blockingQueue, TARGET_FNAME);
	indexStructure.load(INDEX_FNAME);

	//Worker worker {indexStructure, ifsMonitor, blockingQueue};



	/* BlockingQueue blockingQueue;
	TargetLoader targetLoader;
	targetLoader.load(blockingQueue, TARGET_FNAME);
	Index indexStructure;
	indexStructure.load(INDEX_FNAME); */

	return 0;
}
