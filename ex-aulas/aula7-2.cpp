#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


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

    int seed = 10;
    char *SEED_VAR = getenv("SEED");
    if (SEED_VAR != NULL){
        seed = atoi(SEED_VAR);
    }

    for (int i=0;i<n;i++){
        objetos[i].id =i;
        std::cin >> objetos[i].weight;
        std::cin >> objetos[i].value;
    }


    std::sort(objetos.begin(), objetos.end(), compara_objetos);

    int best_value = 0;
    int best_weight = 0;
    std::vector<bool> best_result(n,false);

    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> d;
    
    for (int k = 0; k < 10; k++){
        
        int wactual = 0;
        int vactual = 0;
        std::vector<bool> result(n,false);

        for (auto &o : objetos){
            double rnd = d(eng);
            if (rnd <= 0.5 && wactual + o.weight < wmax){
                o.used = true;
                result[o.id] = true;
                wactual += o.weight;
                vactual += o.value;
            }
        }
        if (vactual > best_value){
            best_value = vactual;
            best_weight = wactual; 
            best_result = result;
        }
        for (auto &obj : objetos){
            if (best_weight + obj.weight < wmax && !best_result[obj.id]){
                best_result[obj.id] = true;
                best_weight += obj.weight;
                best_value += obj.value;
            }
        }
    }
    
    std:cout << best_weight << " " << best_value << " 0" << "\n";
     
    for (int i = 0; i < n ; i++){
        if (best_result[i]){
            std::cout << i << " ";
        }
    }
    
    std::cout << "\n";

    return 0;

}
