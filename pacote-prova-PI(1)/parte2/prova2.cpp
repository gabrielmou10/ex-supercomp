#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

struct object{
    int id;
    double value;
    bool used = false;
    };

struct people{
    int id;
    double value = 0;
    std::vector<int> objetos_da_pessoa;
    };

bool compara_objetos(object &a, object &b){
        return a.value > b.value;
    }

bool compara_id(int &a, int &b){
        return a < b;
    }


int main() {
   
    int m; // número de objetos
    int n; // número de pessoas
    std::cin >> m;
    std::cin >> n;

    //matriz
    std::vector<std::vector<double> > matriz_valores (n,std::vector<double>(m));

    // listando a matriz de valores dos objetos pra cada pessoa
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            std::cin >> matriz_valores[i][j];
        }
    }

    // lista de objetos
    std::vector<object> objetos_in(m);
    for (int a=0;a<n;a++){
        objetos_in[a].id =a;
        objetos_in[a].used = false;
    }

    // lista de pessoas
    std::vector<people> pessoas(n);
    for (int b=0;b<n;b++){
        pessoas[b].id =b;
    }

    int i = 0; // indíce objeto
    int j = 0; // indíce pessoa

    while (i < m){ 
        if (j == n){
            j = 0;
        }
        // listando a lista de objetos para cada pessoa em questão
        std::vector<object> objetos(m);
        objetos = objetos_in; 
        for (int z = 0; z < m; z++){
            objetos[z].value = matriz_valores[j][z];
        }
        // ordena lista de objetos da pessoa em questão por valor 
        std::sort(objetos.begin(), objetos.end(), compara_objetos);

        // atribui a pessoa o objeto dela
        bool flag = true;
        int k = 0;
        while (flag){
            if(objetos_in[objetos[k].id].used == false){
                pessoas[j].objetos_da_pessoa.push_back(objetos[k].id);
                pessoas[j].value += objetos[k].value;
                objetos_in[objetos[k].id].used = true;
                flag = false;
                i++;
                std::cout << "i: " << i;
            } else{
                k++;
            }
        }
        j++;
    }

    int mms = pessoas[0].value; // MMS

    for (people &p : pessoas){
        if (p.value < mms){
            mms = p.value;
        }
    }

    std::cout <<  mms << "\n" ;
    for (people &p : pessoas){
        std::sort(p.objetos_da_pessoa.begin(), p.objetos_da_pessoa.end(),compara_id);
        for (int id : p.objetos_da_pessoa ){
            std::cout << id << " ";
        }
        std::cout << "\n";
    }


    return 0;

}