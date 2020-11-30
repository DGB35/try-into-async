#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <future>
#include "Txt.h"
#define TIMEP(start, end) (std::chrono::duration_cast<std::chrono::milliseconds>((end) - (begin)).count())
#define ASYNC

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << argv[0] << ": missing file \n";
		return 1;
	}
	else if (argc != 2)
	{
		std::cout << argv[0] << ": too many arg\n";
		return 2;
	}


	l1::Txt a, b;
	auto begin = std::chrono::high_resolution_clock::now();

#ifdef ASYNC
	auto f = std::async(std::launch::async, [&a, argv]() { a(argv[1]); });
	auto f1 = std::async(std::launch::async, [&b, argv]() { b(argv[1]); });
	f.wait();
	f1.wait();
#else
	a(argv[1]);
	b(argv[1]);
#endif
	std::cout << a.size() << std::endl;
	std::cout << b.size() << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "End:" << std::setw(9) << TIMEP(begin, end) << " milliseconds" << std::endl;
	
	return 0;
}
