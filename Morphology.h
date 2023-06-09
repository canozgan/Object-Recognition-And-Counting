#pragma once
#include "image.h"
#include<vector>
int* erosion(int w, int h, int* binary_img_data);
int* dilation(int w, int h, int* binary_img_data);
int* conditionalDilation(int w, int h, int* binary_img_data);