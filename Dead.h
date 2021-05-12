#ifndef _DEAD_H_
#define _DEAD_H_

#include "UrlState.h"

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
};

#endif // _DEAD_H_