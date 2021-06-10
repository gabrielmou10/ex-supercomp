#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

int main() {

    std::vector<double> stocks;

    while (std::cin){
        double stock_day;
        std::cin >> stock_day;
        stocks.push_back(stock_day);

    }
    
    auto start = std::chrono::steady_clock::now();
    thrust::device_vector<double> dev(stocks);
    auto end = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> time_seconds = end-start;
    
    std::cout << "time: " << time_seconds.count() << "s\n";

}