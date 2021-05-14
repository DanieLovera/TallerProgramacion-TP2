#ifndef _URL_STATE_H_
#define _URL_STATE_H_

class Url;
#include "Index.h"
#include <cstddef>

class UrlState {
	private:
		UrlState(const UrlState &other) = delete;
		UrlState& operator=(const UrlState &other) = delete;
		UrlState& operator=(UrlState &&other) = delete;

	public:
		UrlState();
		UrlState(UrlState &&other);
		virtual ~UrlState();
		virtual void print() const = 0;
		virtual void handleValidation(const Index &indexStructure, 
							  std::size_t &offset, 
							  std::size_t &size, 
							  Url &context) = 0;
		virtual void handleExploration(IfsMonitor &ifsMonitor, 
							   		   const std::string &domainFilter, 
							   		   std::size_t &offset, 
							   		   std::size_t &size, 
							   		   std::string &result, 
							   		   Url &context) = 0;
};

#endif // _URL_STATE_H_
