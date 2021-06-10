#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/random/uniform_real_distribution.h>


int main()
{
    int seed;
    std::cin >> seed;
    
    thrust::minstd_rand eng(seed);
    thrust::uniform_real_distribution<double> d(25, 40);

    for(int i = 0; i< 10; i ++)
    {
        std::cout << d(eng) << " ";
    }    

    std::cout << "\n";
}