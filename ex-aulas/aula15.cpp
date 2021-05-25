#include <vector>
#include <iostream>
#include <unistd.h>


double conta_complexa(int i) {
	return 2 * i;
	sleep(10);
}

int main() {
	std::vector<double> vec;
	int N = 10000; 
	#pragma omp parallel for default(none) shared (vec) firstprivate(N)
	for (int i = 0; i < N; i++) {
		double cc = conta_complexa(i);
		#pragma omp critical
		{
		vec.push_back(cc);
		}
	}
	
	for (int i = 0; i < N; i++) {
		std::cout << vec[i] << " ";
	}
	
	return 0;
}
