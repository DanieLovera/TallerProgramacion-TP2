#ifndef _URL_H_
#define _URL_H_

#include <string>
class UrlState;

class Url {
	private:
		std::string url;
		UrlState *state;
		Url(const Url &other) = delete;
		Url& operator=(const Url &other) = delete;
		void uninit();

	public:
		Url();
		Url(std::string url);
		Url(Url &&other);
		~Url();
		Url& operator=(Url &&other);
		bool operator<(const Url &other) const;
		bool equals(const Url &other) const;
		void print() const;
};

#endif // _URL_H_
