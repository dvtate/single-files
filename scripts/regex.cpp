#include <regex>
#include <iostream>
#include <sys/mman.h>
#include <cstdlib>
#include <fstream>

int main(int argc, char** argv) {

	// open file
	char* fname = argv[1];
	std::ifstream f(fname);

	// compile regex
	std::regex rxp("[^\t]*?",
		std::regex::optimize | std::regex_constants::ECMAScript);
	
	
	// TODO use mmap for even more fasts :)
	int total = 0;
	for (std::string line; std::getline(f, line); ) {
		// get results	
		total +=(bool) std::regex_match(line.c_str(), rxp);
	}
	std::cout <<total;
}

/// how is this same speed as perl???
