#ifndef _EXPLORED_H_
#define _EXPLORED_H_

#include "UrlState.h"

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
};

#endif // _EXPLORED_H_
