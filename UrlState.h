#ifndef _URL_STATE_H_
#define _URL_STATE_H_

class UrlState {
	//Url &url;
	private:
		UrlState(const UrlState &other) = delete;
		UrlState& operator=(const UrlState &other) = delete;
		UrlState& operator=(UrlState &&other) = delete;

	public:
		UrlState();
		UrlState(UrlState &&other);
		virtual ~UrlState();
		virtual void print() const = 0;
};

#endif