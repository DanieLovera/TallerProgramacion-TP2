#ifndef _URL_H_
#define _URL_H_

#include <string>
class UrlState;
class Index;
class IfsMonitor;

class Url {
	private:
		std::string url;
		UrlState *state;
		Url(const Url &other) = delete;
		Url& operator=(const Url &other) = delete;
		void freeIfNotNullState();
		bool filter(const std::string &url, const std::string &domainFilter);

	public:
		Url();
		explicit Url(std::string url);
		Url(Url &&other);
		~Url();
		Url& operator=(Url &&other);
		bool operator<(const Url &other) const;
		bool equals(const Url &other) const;
		void validate(const Index &indexStructure, 
				   	  std::size_t &offset, 
				   	  std::size_t &size);
		void exploreLinks(IfsMonitor &ifsMonitor, 
					  	  const std::string &domainFilter, 
					  	  std::size_t &offset, 
					  	  std::size_t &size,
					  	  std::string &result);
		bool isSubUrl(const std::string &url, const std::string &domainFilter);
		void setState(UrlState *state);
		void print() const;
};

#endif // _URL_H_
