#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include "Url.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class ClosedQueueException : public std::exception {
	public:
		const char *what() {
			return "Queue is closed";
		}
};

class BlockingQueue {
	private:
		std::queue<Url> urls;
		std::mutex mutex;
		std::condition_variable cv;
		bool isClose;
		BlockingQueue(const BlockingQueue &other) = delete;
		BlockingQueue& operator=(const BlockingQueue &other) = delete;
		BlockingQueue(BlockingQueue &&other) = delete;
		BlockingQueue& operator=(BlockingQueue &&other) = delete;
		bool isWaitCondition() const;

	public:
		BlockingQueue();
		~BlockingQueue();
		void push(Url &&url);
		Url pop();
		void close();
};

#endif // _BLOCKING_QUEUE_H_
