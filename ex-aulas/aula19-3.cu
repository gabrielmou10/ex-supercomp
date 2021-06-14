#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <string>
#include <thrust/functional.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <math.h>
#include "imagem.hpp"
#include <thrust/iterator/counting_iterator.h>

struct media {
    
    int cols;
    unsigned char *pixels;

    media(int cols, unsigned char *pixels) : cols(cols),pixels(pixels) {};

     __host__ __device__
    unsigned char operator()(const int &i){
        //int x = i % cols;
        //int y = i / cols;
        return (pixels[i-1]+pixels[i]+pixels[i+1])/3;
        //return 0;
    }
};

int main(int argc, char *argv[]) {

    Imagem im = Imagem::read("download.pgm");

    // copiar gpu
    thrust::device_vector <unsigned char> pixels_gpu(im.pixels,im.pixels + im.total_size);
    thrust::device_vector <unsigned char> pixels_out(im.total_size);

    //transform
    media med(im.cols,pixels_gpu.data().get());
    thrust::transform(thrust::make_counting_iterator<int>(0),thrust::make_counting_iterator<int>(im.total_size),pixels_out.begin(),med);

    //copia de volta cpu

    thrust::copy(pixels_out.begin(),pixels_out.end(),im.pixels);

    im.write("out2.pgm");

    return 0;
}