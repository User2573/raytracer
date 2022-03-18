#include <vector>
#include <iostream>
#include <thread>

int main()
{
	std::cout << "lmao\n";
	#pragma omp parallel for
	for (int i=0; i<100; ++i) {
		std::cout << std::this_thread::get_id() << '\n';
	}
}
