#include"Clustering.h"
int* RGB_To_Intensity(int w, int h, int* rgb_img_data) {
	int* intensity_data = new int[w * h];
	int bufpos = 0;
	int newpos = 0;
	for (int row = 0; row < h; row++) {
		for (int column = 0; column < w; column++) {
			newpos = row * w + column;
			bufpos = (row * w + column)*3;
			intensity_data[newpos] = unsigned char(0.30 * rgb_img_data[bufpos] + 0.59 * rgb_img_data[bufpos + 1] + 0.11 * rgb_img_data[bufpos + 2]);
		}
	}
	return intensity_data;
}
int* Histogram(int w, int h, int* intensity_img_data) {
	int* hist = new int[256];
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}
	for (int i = 0; i < h * w; i++) {
		hist[intensity_img_data[i]]++;
	}
	return hist;
}
int* Intensity_To_Binary(int w, int h, int* intensity_img_data, int K1, int K2) {
	int* binary_img_data = new int[w * h];
	for (int i = 0; i < h * w; i++) {
		if (abs(intensity_img_data[i] - K1) <= abs(intensity_img_data[i] - K2)) {
			binary_img_data[i] = 1;
		}
		else {
			binary_img_data[i] = 0;
		}
	}
	return binary_img_data;
}
double* k_means_euclidean_dist(int* hist) {
	double* k_means = new double[2];
	float K1 = 50.0f, K2 = 150.0f;
	float newK1 = 0.0f, newK2 = 0.0f;
	float payK1 = 0.0f, payK2 = 0.0f;
	float paydaK1 = 0.0f, paydaK2 = 0.0f;
	while (true) {
		for (int i = 0; i < 256; i++) {
			if (abs(i - K1) <= abs(i - K2)) {
				payK1 += i * hist[i];
				paydaK1 += hist[i];
			}
			else {
				payK2 += i * hist[i];
				paydaK2 += hist[i];
			}
		}
		newK1 = payK1 / paydaK1;
		newK2 = payK2 / paydaK2;
		if (newK1 == K1 && newK2 == K2) {
			break;
		}
		else {
			payK1 = 0.0f; payK2 = 0.0f; paydaK1 = 0.0f; paydaK2 = 0.0f;
			K1 = newK1; K2 = newK2;

		}
	}
	k_means[0] = K1;
	k_means[1] = K2;
	return k_means;
}
double* k_means_mahalanobis_dist(int* hist) {
	double* k_means = new double[2];
	float K1 = 50.0f, K2 = 150.0f;
	float ss1 = 1.0f, ss2 = 1.0f;
	float newK1 = 0.0f, newK2 = 0.0f;
	float newSS1 = 0.0f, newSS2 = 0.0f;
	float payK1 = 0.0f, payK2 = 0.0f;
	float paydaK1 = 0.0f, paydaK2 = 0.0f;
	float paySS1 = 0.0f, paySS2 = 0.0f;
	while (true) {
		for (int i = 0; i < 256; i++) {
			if (abs((i - K1) / sqrt(ss1)) <= abs((i - K2)) / sqrt(ss2)) {
				payK1 += i * hist[i];
				paydaK1 += hist[i];
				paySS1 += pow(i - K1, 2) * hist[i];
			}
			else {
				payK2 += i * hist[i];
				paydaK2 += hist[i];
				paySS2 += pow(i - K2, 2) * hist[i];
			}
		}
		newK1 = payK1 / paydaK1;
		newK2 = payK2 / paydaK2;
		newSS1 = sqrt(paySS1 / (paydaK1 - 1));
		newSS2 = sqrt(paySS2 / (paydaK2 - 1));
		if (newK1 == K1 && newK2 == K2 && newSS1 == ss1 && newSS2 == ss2) {
			break;
		}
		else {
			payK1 = 0.0f; payK2 = 0.0f; paydaK1 = 0.0f; paydaK2 = 0.0f; paySS1 = 0.0f; paySS2 = 0.0f;
			K1 = newK1; K2 = newK2;
			ss2 = newSS2; ss1 = newSS1;
		}
	}
	k_means[0] = K1;
	k_means[1] = K2;
	return k_means;
}
