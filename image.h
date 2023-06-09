#pragma once
typedef struct image {
	int w;
	int h;
	int c;
	int* data;
} image;

image load_image(const char* filename);
