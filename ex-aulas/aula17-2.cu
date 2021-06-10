#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>

int main() {

    std::vector<double> stocks;
    int n = 0;

    while (std::cin){
        n = n + 1;
        double stock_day;
        std::cin >> stock_day;
        stocks.push_back(stock_day);
    }
    

    auto start = std::chrono::steady_clock::now();
    thrust::device_vector<double> dev(stocks);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_seconds = end-start;

    double preco_medio = thrust::reduce(dev.begin(), dev.end(), 0, thrust::plus<double>()) / n;
    double preco_medio_ano = thrust::reduce(dev.begin() + n - 365, dev.end(), 0, thrust::plus<double>()) / 360;
    double maior_preco = thrust::reduce(dev.begin(), dev.end(), 0, thrust::maximum<double>());;
    double menor_preco = thrust::reduce(dev.begin(), dev.end(), maior_preco, thrust::minimum<double>());;
    double maior_ano = thrust::reduce(dev.begin() + n - 365, dev.end(), 0, thrust::maximum<double>());
    double menor_ano = thrust::reduce(dev.begin() + n - 365, dev.end(), maior_ano, thrust::minimum<double>());

    
    
    std::cout << "media: " << preco_medio << " media ano: " << preco_medio_ano << " maior: " << maior_preco << " menor: " << menor_preco << " maior ano: " << maior_ano << " menor ano: " << menor_ano << "\n";

    

}