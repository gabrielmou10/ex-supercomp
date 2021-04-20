#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <math.h>

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<double> vec;
    for (int i = 0; i < n; i++) {
        vec.push_back(i * i);
    }
    cout << "Tamanho do vetor: " << vec.size() << "\n";
    cout << "Primeiro elemento: " << vec.front() << "\n";
    cout << "Último elemento: " << vec.back() << "\n";
    cout << "Elemento 2: " << vec[1] << "\n";
    cout << "Elemento 3: " << vec[2] << "\n";
    cout << "Elemento 4: " << vec[3] << "\n";
    return 0;

}