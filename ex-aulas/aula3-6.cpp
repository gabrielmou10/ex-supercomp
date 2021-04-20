#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <math.h>

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<double> vecx;
    vector<double> vecy;
    for (int i = 0; i < n; i++) {
        double x;
        cin >> x;
        vecx.push_back(x);
        double y;
        cin >> y;
        vecy.push_back(y);
    }

    std::vector<std::vector<double> > matriz_distancias (n,std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double dx = vecx[i] - vecx[j];
            double dy = vecy[i] - vecy[j];
            matriz_distancias[i][j] = sqrt(dx*dx + dy*dy);
            cout << matriz_distancias[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;

}