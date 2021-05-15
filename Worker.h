#ifndef _WORKER_H_
#define _WORKER_H_

#include "Thread.h"
#include <set>
#include <string>
class Url;
class Index;
class IfsMonitor;
class BlockingQueue;
class SetMonitor;

// Clase que es movible solamente cuando el objeto sea nuevamente
// construido. El objeto movido no deberia ser usado de vuelta pese
// a que nada se lo impide porque su estado seguira siendo el mismo.
class Worker : public Thread {
	private:
		Index &indexStructure;
		IfsMonitor &ifsMonitor;
		BlockingQueue &blockingQueue;
		//std::set<Url> &result;
		SetMonitor &result;
		std::string &domainFilter;

		Worker(const Worker &other) = delete;
		Worker& operator=(const Worker &other) = delete;
		Worker& operator=(Worker &&other) = delete;
		void pushUrls(const std::string &urlsResult);

	public:
		Worker(Index &indexStructure, 
			   IfsMonitor &ifsMonitor, 
			   BlockingQueue &blockingQueue, 
			   SetMonitor &result, 
			   std::string &domainFilter);
		Worker(Worker &&other);
		~Worker();

		void run() override;
};

#endif //_WORKER_H_
