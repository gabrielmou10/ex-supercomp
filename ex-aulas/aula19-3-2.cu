#include "imagem.hpp"
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>
#include <iostream>

struct raw_access {
    unsigned char *ptr;
    int height, width;


    raw_access (unsigned char *ptr, int height, int width) : ptr(ptr), height(height), width(width) {};

    __device__ __host__
    unsigned char operator()(const int &i) {
        int y = i % width;
        int x = i / width;

        unsigned char pxl = ptr[y * width + x];

        unsigned char left;
        if(x - 1 >= 0){
            left = ptr[y * width + (x - 1)];
        }
        else{
            left = 0;
        }

        unsigned char right;
        if(x + 1 <= height){
            right = ptr[y * width + (x + 1)];
        }
        else{
            right = 0;
        }

        unsigned char up;
        if(y + 1 <= width){
            up = ptr[(y + 1) * width + x];
        }
        else{
            up = 0;
        }

        unsigned char down;
        if(y - 1 >= 0){
            down = ptr[(y - 1) * width + x];
        }
        else{
            down = 0;
        }

        return (pxl + up + down + left + right);
    }
};

int main(){
    Imagem img = Imagem::read("download.pgm");

    thrust::device_vector<unsigned char> image(img.pixels, img.pixels + img.total_size);
    thrust::device_vector<unsigned char> resultado(img.total_size);

    thrust::counting_iterator<int> iter(0);
    raw_access ra(thrust::raw_pointer_cast(image.data()), img.cols, img.rows);
    thrust::transform(iter, iter+image.size(), resultado.begin(), ra);

    thrust::copy(resultado.begin(), resultado.end(), img.pixels);
    img.write("teste1.pgm");

}