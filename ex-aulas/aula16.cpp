#include <vector>
#include <iostream>
#include <random>
#include <omp.h>

int main(){
    long sum = 0;
    long N = 100000;

    #pragma omp parallel default(none) shared(sum) firstprivate(N)
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        std::default_random_engine eng(id*137321);
        std::uniform_real_distribution<double> dist;

        long chunk_size = N/num_threads;
        long start = id * chunk_size;
        long end = (id + 1) * chunk_size;
        if (end > N) end = N;

        for (long i =start; i < end; i++){
            double x,y;
            x = dist(eng);
            y = dist(eng);
            if (x*x + y*y <= 1){
                #pragma omp critical
                sum++;
            } 
        }
    }
    double pi = 4.0 * sum / N;
    std::cout << pi << "\n";
    std::cerr << sum << "\n";

}
