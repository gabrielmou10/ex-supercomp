#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

struct object{
       int id;
       int weight;
       int value;
       bool used;
    };


bool compara_objetos(object &a, object &b){
        return a.value > b.value;
    }

int main() {
   
    int n;
    int wmax;
    std::cin >> n;
    std::cin >> wmax;
    
    std::vector<object> objetos(n);


    for (int i=0;i<n;i++){
        objetos[i].id =i;
        std::cin >> objetos[i].weight;
        std::cin >> objetos[i].value;
    }

    int wactual = 0;
    int vactual = 0;

    std::vector<int> result;
    result.reserve(n);

    std::sort(objetos.begin(), objetos.end(), compara_objetos);

    int i = 0;

    std::default_random_engine eng(20);
    std::uniform_real_distribution<double> d(0.0,1.0);


    while(i < n){

        double rnd = d(eng);
        int idx;

        if (rnd < 0.25){
            std::uniform_int_distribution<int> d_nao_usado(i,n-1);
            idx = d_nao_usado(eng);

        } else {
            idx = i++;
        }

        object &o = objetos[idx];

        if (o.used == false && wactual + o.weight < wmax){
            o.used = true;
            result.push_back(o.id);
            wactual += o.weight;
            vactual += o.value;
        }
    }


    std::sort(result.begin(), result.end());
    std:cout << wactual << " " << vactual << " 0" << "\n";

    for (int id : result){
        std::cout << id << " ";
    }
    
    std::cout << "\n";

    return 0;

}