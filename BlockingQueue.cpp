#include "BlockingQueue.h"

BlockingQueue::BlockingQueue() : isClose {false} { }

BlockingQueue::~BlockingQueue() { }

void BlockingQueue::push(Url &&url) {
	std::lock_guard<std::mutex> lock {mutex};
	//urls.push(url.clone());
	urls.push(std::move(url));
	cv.notify_all();
}

void BlockingQueue::pop(Url &url) {
	std::unique_lock<std::mutex> lock {mutex};
	
	while (urls.empty()) {
		if (isClose) return;
		cv.wait(lock);
	}

	url = std::move(urls.front());
	urls.pop();
}

void BlockingQueue::close() {
	std::lock_guard<std::mutex> lock {mutex};
	isClose = true;
	cv.notify_all();
}
