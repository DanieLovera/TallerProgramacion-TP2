#ifndef _EXPLORED_H_
#define _EXPLORED_H_

#include "UrlState.h"
#include <string>

class Explored : public UrlState {
	private:
		Explored(const Explored &other) = delete;
		Explored& operator=(const Explored &other) = delete;
		Explored& operator=(Explored &&Explored) = delete;

	public:
		Explored();
		Explored(Explored &&other);
		~Explored();
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

#endif // _EXPLORED_H_
