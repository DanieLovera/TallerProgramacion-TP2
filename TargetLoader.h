#ifndef _TARGET_LOADER_H_
#define _TARGET_LOADER_H_

#include "IfsMonitor.h"
#include "BlockingQueue.h"
#include <string>

class TargetLoader {
	private:
		TargetLoader(const TargetLoader &other) = delete;
		TargetLoader& operator=(const TargetLoader &other) = delete;
		void loadQueue(BlockingQueue &blockingQueue, IfsMonitor &ifsMonitor) const;

	public:
		TargetLoader();
		TargetLoader(TargetLoader &&other);
		~TargetLoader();
		TargetLoader& operator=(TargetLoader &&other);
		void load(BlockingQueue &blockingQueue, std::string fileName);
};

#endif
