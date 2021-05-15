#ifndef _DEAD_H_
#define _DEAD_H_

#include "UrlState.h"
#include <string>

class Dead : public UrlState {
	private:
		Dead(const Dead &other) = delete;
		Dead& operator=(const Dead &other) = delete;
		Dead& operator=(Dead &&Dead) = delete;

	public:
		Dead();
		Dead(Dead &&other);
		~Dead();
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

#endif // _DEAD_H_
