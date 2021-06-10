#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <thrust/iterator/constant_iterator.h>

struct maior_que_zero{
    __host__ __device__
    bool operator()(const double &x){
        return x >= 0;
    }
};

int main() {

    std::vector<double> stocks_ms, stocks_aapl;

    while (std::cin){
        double mstf, aapl;
        std::cin >> mstf >> aapl;
        stocks_aapl.push_back(aapl);
        stocks_ms.push_back(mstf);
    }
    int N = stocks_aapl.size();
    std::cerr << stocks_aapl.size() << "\n";

    thrust::device_vector<double> stocks_ms_dev(stocks_ms), stocks_aapl_dev (stocks_aapl);
    thrust::device_vector<double> diff(N);
    
    thrust::transform(stocks_ms_dev.begin(), stocks_ms_dev.end(),stocks_aapl_dev.begin(),diff.begin(),thrust::minus<double>());
    
    double soma = thrust::reduce(diff.begin(),diff.end());
    double media = soma/stocks_ms.size();

    thrust::device_vector<double> diff_media_dev(N);

    thrust::transform(diff.begin(),diff.end(),thrust::make_constant_iterator(media),diff_media_dev.begin(),thrust::minus<double>());
    thrust::transform(diff_media_dev.begin(),diff_media_dev.end(),diff_media_dev.begin(),diff_media_dev.begin(),thrust::multiplies<double>());

    double std = thrust::reduce(diff_media_dev.begin(),diff_media_dev.end());
    std = std / N;

    auto count = thrust::count_if(diff.begin(),diff.end(),maior_que_zero());

    std::cout << "Media: " << media << " Var: " << std << " Count: " << count << "\n";

    return 0;
}