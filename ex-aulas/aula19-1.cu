#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/transform_reduce.h>
#include <math.h>

struct var{
    double media;
    int N;

    var(double m, int n) : media(m) , N(n) {};
    __host__ __device__ 
    double operator()(const double &vi){
        return (vi - media)*(vi - media)/ N;
    }
};

int main() {

    std::vector<double> stocks;

    while (std::cin){
        double s;
        std::cin >> s;
        stocks.push_back(s);
    }
    int N = stocks.size();

    thrust::device_vector<double> stocks_dev(stocks);

    double soma = thrust::reduce(stocks_dev.begin(),stocks_dev.end());
    double media = soma/N;

    thrust::device_vector<double> variancias(N);

    thrust::transform(stocks_dev.begin(),stocks_dev.end(),variancias.begin(),var(media,N));

    double variancia = thrust::reduce(variancias.begin(),variancias.end(),0.0,thrust::plus<double>());


    std::cout << "Media: " << media << " Var: " << variancia << " desvio padrao: " << sqrt(variancia) << "\n";

    return 0;
}