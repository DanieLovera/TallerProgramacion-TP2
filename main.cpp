#include "Index.h"
#include <iostream>

#define INDEX_FNAME argv[1]

int main(int argc, const char *argv[]) {
	Index indexStructure;
	indexStructure.load(INDEX_FNAME);

	return 0;
}
