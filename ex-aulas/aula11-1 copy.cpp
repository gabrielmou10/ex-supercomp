#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

struct object{
       int id;
       int weight;
       int value;
       bool operator <(object &a){
           return double(value)/weight > double(a.value)/a.weight;
       }
    };


int main() {
   
    int n;
    int wmax;
    std::cin >> n;
    std::cin >> wmax;
    
    std::vector<object> objetos(n);
    std::vector<double> usados (n,0);


    for (int i=0;i<n;i++){
        objetos[i].id =i;
        std::cin >> objetos[i].weight;
        std::cin >> objetos[i].value;
    }

    double wactual = 0;
    double vactual = 0;

    std::vector<int> result;
    result.reserve(n);


    std::sort(objetos.begin(), objetos.end());

    for (auto &o : objetos){
        if (wactual + o.weight <= wmax) {
            wactual += o.weight;
            vactual += o.value;
            usados[o.id] = 1.0;
        } else if(wactual < wmax){
            double frac = double(wmax - wactual)/o.weight;
            wactual += frac * o.weight;
            vactual += frac * o.value;
            usados[o.id] = frac;
        }
    }

    //std::sort(result.begin(), result.end());
    std:cout << wactual << " " << vactual << " 1" << "\n";
     
    for (int i = 0; i < n; i++){
        std::cout << usados[i] << " ";
    }
    std::cout << "\n";

    return 0;

}