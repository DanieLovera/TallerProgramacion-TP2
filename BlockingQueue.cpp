#include "BlockingQueue.h"
#include <utility>

BlockingQueue::BlockingQueue() : isClose {false} { }

BlockingQueue::~BlockingQueue() { }

void BlockingQueue::push(Url &&url) {
	std::lock_guard<std::mutex> lock(mutex);
	urls.push(std::move(url));
	cv.notify_all();
}

Url BlockingQueue::pop() {
	std::unique_lock<std::mutex> lock(mutex);
	
	while (urls.empty()) {
		if (isClose) throw ClosedQueueException();
		cv.wait(lock);
	}

	Url url = std::move(urls.front());
	urls.pop();
	return url;
}

void BlockingQueue::close() {
	std::lock_guard<std::mutex> lock(mutex);
	isClose = true;
	cv.notify_all();
}
