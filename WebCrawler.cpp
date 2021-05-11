#include "Index.h"
#include "Url.h"
#include "Worker.h"
#include "BlockingQueue.h"
#include <iostream>
#include <thread>
#include <chrono>

#define INDEX_FNAME argv[1]

/*Index indexStructure;
	indexStructure.load(INDEX_FNAME);*/

int main(int argc, const char *argv[]) {
	
	BlockingQueue bq;
	Url url_1 {"cualquiera.com"};
	Url url_2 {"nose.com"};
	bq.push(url_1);
	bq.push(url_2);
	Url url1 {" "};
	Url url2 {" "};

	bq.pop(url2);
	bq.pop(url1);
	url2.print();
	url1.print();
	std::thread thread {[&]{
							bq.pop(url2);
							url2.print();
						    std::cout << "DENTRO DEL THREAD"<< std::endl;}};

	bq.push(url1);
	bq.close();

	thread.join();

	return 0;
}
