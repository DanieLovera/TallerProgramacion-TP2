#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>

class Thread {
	private:
		std::thread thread;
		Thread(const Thread &thread) = delete;
		Thread& operator=(const Thread &thread) = delete;

	public:
		Thread();
		Thread(Thread &&other);
		virtual ~Thread();
		Thread& operator=(Thread &&other);
		void start();
		void join();
		virtual void run() = 0;
};

#endif //_THREAD_H_
