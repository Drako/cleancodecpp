#include <iostream>

int main(int argc, char** argv) {
	return
		argc ? (std::cout << *argv << std::endl, main(argc - 1, argv + 1))
		: 0;
}
