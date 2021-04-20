#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct fornecedor{
       int id;
       double preco;
       bool used;
    };  

struct pacote{
       int id;
       double dist;
       bool used;
       fornecedor fornec;
    };

bool compara_pacotes_dist(pacote &a, pacote &b){
        return a.dist > b.dist;
    }

bool compara_pacotes_id(pacote &a, pacote &b){
        return a.id < b.id;
    }    

bool compara_fornecedores(fornecedor &a, fornecedor &b){
        return a.preco < b.preco;
    }


int main() {
   
    int n;
    std::cin >> n;
    std::vector<pacote> pacotes(n);
    std::vector<fornecedor> fornecedores(n);

    for (int i=0;i<n;i++){
        pacotes[i].id =i;
        pacotes[i].used = false;
        std::cin >> pacotes[i].dist;
    }

    for (int i=0;i<n;i++){
        fornecedores[i].id =i;
        fornecedores[i].used = false;
        std::cin >> fornecedores[i].preco;
    }

    double custo_atual = 0;    

    // Ordenando pacotes da maior distância pra menor
    // Ordenando fornecedores do menor preço pro maior
    std::sort(pacotes.begin(), pacotes.end(), compara_pacotes_dist);
    std::sort(fornecedores.begin(), fornecedores.end(), compara_fornecedores);

    for (int i = 0; i < n ; i++){
        pacotes[i].fornec = fornecedores[i];
        custo_atual += pacotes[i].dist * fornecedores[i].preco;
    }

    std::cout << custo_atual << " " << "\n";

    std::sort(pacotes.begin(), pacotes.end(), compara_pacotes_id);
    
    for (pacote &p : pacotes){
        std::cout << p.fornec.id + 1 << "\n";
    }

    return 0;
}