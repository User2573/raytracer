#include <iostream>
#include <algorithm>
#include <execution>
#include <chrono>
#include <thread>
#include <random>

int main() {
	std::vector<int> foo;
	foo.reserve(1000);
	for (int i = 0; i < 1000; i++) {
		foo.push_back(i);
	}

	std::for_each(
		std::execution::par_unseq,
		foo.begin(), foo.end(),
		[](auto &&item) {
			std::cout << item << std::endl;
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(10, 100);
			std::this_thread::sleep_for(std::chrono::milliseconds(dist6(rng)));
			std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
		}
	);
}
