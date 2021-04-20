#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <math.h>

using namespace std;
;

int main() {

    int n;
    double s;
    std::cin >> n;
    s = 0.0000000;
    for (int i=0;i<n;i++){
        s = s + 1 / pow(2,i);
    }

    std::cout << "s = " << s << "\n";
    return 0;
}