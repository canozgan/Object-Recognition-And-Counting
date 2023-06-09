#pragma once
#include "image.h"
#include <stdlib.h>
#include <cmath>
int* RGB_To_Intensity(int w, int h, int* rgb_img_data);
int* Histogram(int w, int h, int* intensity_img_data);
int* Intensity_To_Binary(int w,int h, int* intensity_img_data, int K1, int K2);
double* k_means_euclidean_dist(int* hist);
double* k_means_mahalanobis_dist(int* hist);