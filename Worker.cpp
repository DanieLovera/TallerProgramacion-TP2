#include "Worker.h"

Worker::Worker() { }
		
Worker::Worker(Worker &&other) { }

Worker::~Worker() { }

Worker& Worker::operator=(Worker &&other) {
	return *this;
}

void Worker::run() {

}