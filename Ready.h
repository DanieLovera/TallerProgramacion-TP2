#ifndef _READY_H_
#define _READY_H_

#include "UrlState.h"
#include <string>

class Ready : public UrlState {
	private:
		Ready(const Ready &other) = delete;
		Ready& operator=(const Ready &other) = delete;
		Ready& operator=(Ready &&ready) = delete;

	public:
		Ready();
		Ready(Ready &&other);
		~Ready();
		void print() const override;
		void handleValidation(const Index &indexStructure, 
							  std::size_t &offset, 
							  std::size_t &size, 
							  Url &context) override;
		void handleExploration(IfsMonitor &ifsMonitor, 
							   const std::string &domainFilter, 
							   std::size_t &offset, 
							   std::size_t &size, 
							   std::string &result, 
							   Url &context) override;
};

#endif // __READY_H_
