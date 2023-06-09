#include"image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


image load_image(const char* filename)
{
	int w, h, c;
	int channel = 3;
	unsigned char* data = stbi_load(filename, &w, &h, &c, channel);

	if (!data) {
		exit(EXIT_FAILURE);
	}

	image out;
	out.h = h;
	out.w = w;
	out.c = c;
	out.data = new int[out.h * out.w * out.c];
	for (int i = 0; i < out.h * out.w * out.c; i++) {
		out.data[i] = data[i];
	}
	return out;
}