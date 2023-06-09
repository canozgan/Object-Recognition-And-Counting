#pragma once
#include"image.h"
#include<vector>
typedef struct result_of_labelling {
	int* data;
	int* label_list_array;
	int object_number;

} result_of_labelling;

result_of_labelling labelObjects(int w, int h, int* binary_img_data);
int* getObjectBoundingBox(int w, int h, int object_number, int* label_list_array,int* labeled_img_data);