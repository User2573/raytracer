#include <vector>
#include <iostream>


int main()
{
	std::cout << "lmao\n";
	#pragma omp parallel for
	for (int i=0; i<100; ++i) {
		std::cout << i << '\n';
	}
}
