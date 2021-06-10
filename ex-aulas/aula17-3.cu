#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

int main() {

    std::vector<double> stocks_a;
    std::vector<double> stocks_m;

    int n = 0;

    double stock_a;
    double stock_m;

    while (std::cin){
        n = n + 1;
        std::cin >> stock_a;
        std::cin >> stock_m;
        stocks_a.push_back(stock_a);
        stocks_m.push_back(stock_m);
    }
    

    thrust::device_vector<double> apple(stocks_a);
    thrust::device_vector<double> microsoft(stocks_m);
    thrust::device_vector<double> diff(n);
    
    // diferenca
    thrust::transform(apple.begin(), apple.end(), microsoft.begin(), diff.begin(), thrust::minus<double>());

    double preco_medio = thrust::reduce(diff.begin(), diff.end(), 0, thrust::plus<double>()) / n;
    
    std::cout << "media entre os precos da AAPL e MSFT: " << preco_medio << "\n";


}