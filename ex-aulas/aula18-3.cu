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
        return x > 0;
    }
};

struct menor_que_zero{
    __host__ __device__
    bool operator()(const double &x){
        return x < 0;
    }
};

int main() {

    int n = 0;
    std::vector<double> stocks;

    while (std::cin){
        n++;
        double stock;
        std::cin >> stock;
        stocks.push_back(stock);
    }

    thrust::device_vector<double> stocks_dev(stocks);
    thrust::device_vector<double> ganho_diario(n-1);
    
    // ganho diario (diferenca entre a acao atual e anterior)
    thrust::transform(stocks_dev.begin() + 1, stocks_dev.end(), stocks_dev.begin(), ganho_diario.begin(), thrust::minus<double>());
    
    // conta quantas vezes subiu
    int quantos_positivos = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), maior_que_zero());
    std::cout << quantos_positivos << "\n";
    
    // qual o aumento médio, levando em conta só as vezes em que subiu

    //zera todos os negativos
    thrust::replace_if(ganho_diario.begin(), ganho_diario.end(), ganho_diario.begin(), menor_que_zero(), 0);

    double somaganhos = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0.0, thrust::plus<double>());

    double ganhomedio = somaganhos / quantos_positivos;
    std::cout << ganhomedio << "\n";


    return 0;
}