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

struct solucao{
    std::vector<bool> usado;
    int valor;
    int peso;

    solucao(int N){
        usado.resize(N,false);
        valor = peso = 0;
    }
};

long num_copy = 0, num_leafs = 0, num_bounds = 0;
std::vector<long> bound_level;

void busca_exaustiva(const std::vector<object> &obj, int C, solucao &solucao_melhor, solucao &solucao_atual,int valor_total, int i = 0){

    if (i == obj.size()){
        num_leafs++;
        if (solucao_atual.valor > solucao_melhor.valor){
            solucao_melhor = solucao_atual;
            num_copy++;
        }
        return;
    }

    // vale a pena continuar?
    int inclui_todos = solucao_atual.valor + valor_total;
    if (inclui_todos <= solucao_melhor.valor){
        num_bounds++;
        bound_level[i]++;
        return;
    }

    if (obj[i].weight <= C){
        solucao_atual.usado[i] = true;
        solucao_atual.valor += obj[i].value;
        solucao_atual.peso += obj[i].weight;
        
        busca_exaustiva(obj,C - obj[i].weight, solucao_melhor, solucao_atual,valor_total - obj[i].value, i+1); 
        
        solucao_atual.usado[i] = false;
        solucao_atual.valor -= obj[i].value;
        solucao_atual.peso -= obj[i].weight;
    } 

    solucao_atual.usado[i] = false;
    busca_exaustiva(obj,C, solucao_melhor, solucao_atual,valor_total - obj[i].value, i+1); 
}


int main() {
   
    int n;
    int wmax;
    std::cin >> n;
    std::cin >> wmax;
    
    std::vector<object> objetos(n);

    int valor_total = 0;

    for (int i=0;i<n;i++){
        objetos[i].id =i;
        std::cin >> objetos[i].weight;
        std::cin >> objetos[i].value;
        valor_total += objetos[i].value;
    }

    bound_level.resize(n,0);

    solucao best_solution(n);
    solucao actual(n);  

    busca_exaustiva(objetos,wmax,best_solution,actual,valor_total);


    std::cout << best_solution.peso << " " << best_solution.valor << " 1" << "\n";
     
    for (int i = 0; i < n ; i++){
        if (best_solution.usado[i]){
            std::cout << i << " ";
        }
    }
    
    std::cout << "\n";
    std::cerr << num_copy << "\n";
    std::cerr << num_leafs << "\n";
    std::cerr << num_bounds << "\n";
    for (int i = 0;i<n;i++){
        std::cout << bound_level[i] << " ";
    }
    std::cout << "\n";

    return 0;

}
