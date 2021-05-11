#ifndef _WORKER_H_
#define _WORKER_H_

#include "Thread.h"

class Worker : public Thread {
	private:
		Worker(const Worker &other) = delete;
		Worker& operator=(const Worker &other) = delete;

	public:
		Worker();
		Worker(Worker &&other);
		~Worker();
		Worker& operator=(Worker &&other);

		void run() override;
};

#endif //_WORKER_H_
