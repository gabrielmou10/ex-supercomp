#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/random/linear_congruential_engine.h>
#include <thrust/random/uniform_real_distribution.h>

struct rng_transform{

    int SEED;

    __device__ __host__

    double operator() (const int &i){
        thrust::minstd_rand eng(SEED);
        thrust::uniform_real_distribution<double> d(25, 40);
        eng.discard(i);
        return d(eng);

    }
};

int main()
{
    int seed;
    std::cin >> seed;
    
    thrust::minstd_rand eng(seed);
    thrust::uniform_real_distribution<double> d(25, 40);
    
    for(int i = 0; i< 10; i ++)
    {
        std::cout << d(eng) << "\n";
    }    


    rng_transform rt = {.SEED = seed};

    thrust::device_vector <double> vec(10);
    thrust::transform(thrust::make_counting_iterator<int>(0),
                      thrust::make_counting_iterator<int>(10),
                      vec.begin(),
                      rt);

    for(int i = 0; i< 10; i ++)
    {
        std::cout << vec[i] << "\n";
    }  

    std::cout << "\n";
}