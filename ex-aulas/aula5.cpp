#include <iostream>
#include <vector>
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

    for (object &o : objetos){
        if (wactual + o.weight <= wmax) {
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
