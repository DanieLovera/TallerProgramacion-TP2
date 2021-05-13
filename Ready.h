#ifndef _READY_H_
#define _READY_H_

#include "UrlState.h"

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
};

#endif // __READY_H_