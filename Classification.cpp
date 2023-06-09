#include "Classification.h"
double* extractFeaturesOfObjects(int w, int h, int object_number, int* bounding_box_list, int* binary_img_data) {
	double* features_array = new double[object_number * 7];
	unsigned char* object_matris = NULL;
	for (int i = 0; i < object_number; i++) {
		int bufpos_for_bounding_box = i * 4;
		int height = bounding_box_list[bufpos_for_bounding_box + 1] - bounding_box_list[bufpos_for_bounding_box] + 1;
		int width = bounding_box_list[bufpos_for_bounding_box + 3] - bounding_box_list[bufpos_for_bounding_box + 2] + 1;
		int counter = 0;
		object_matris = new unsigned char[width * height];
		for (int row = bounding_box_list[bufpos_for_bounding_box]; row < bounding_box_list[bufpos_for_bounding_box] + height; row++) {
			for (int column = bounding_box_list[bufpos_for_bounding_box + 2]; column < bounding_box_list[bufpos_for_bounding_box + 2] + width; column++) {
				object_matris[counter++] = binary_img_data[row * w + column];
			}
		}
		double m_10 = 0, m_01 = 0, m_00 = 0;
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					m_10 += row;
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					m_01 += column;
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					m_00 += 1;
				}
			}
		}
		double r_ = m_10 / m_00;
		double c_ = m_01 / m_00;
		double mean_00 = 0, mean_01 = 0, mean_10 = 0, mean_11 = 0, mean_02 = 0, mean_20 = 0, mean_12 = 0, mean_21 = 0, mean_03 = 0, mean_30 = 0;
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_00 += 1;
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_01 += (column - c_);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_10 += (row - r_);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_11 += (row - r_) * (column - c_);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_02 += pow((column - c_), 2);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_20 += pow((row - r_), 2);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_12 += (row - r_) * pow((column - c_), 2);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_21 += pow((row - r_), 2) * (column - c_);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_03 += pow((column - c_), 3);
				}
			}
		}
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				if (object_matris[row * width + column] == 1) {
					mean_30 += pow((row - r_), 3);
				}
			}
		}
		int bufpos = i * 7;
		features_array[bufpos] = mean_20 / pow(mean_00, 2) + mean_02 / pow(mean_00, 2);
		features_array[bufpos + 1] = pow(mean_20 / pow(mean_00, 2) - mean_02 / pow(mean_00, 2), 2) + 4 * pow(mean_11 / pow(mean_00, 2), 2);
		features_array[bufpos + 2] = pow(mean_30 / pow(mean_00, 5.0 / 2.0) - 3 * mean_12 / pow(mean_00, 5.0 / 2.0), 2) + pow(3 * mean_21 / pow(mean_00, 5.0 / 2.0) - mean_03 / pow(mean_00, 5.0 / 2.0), 2);
		features_array[bufpos + 3] = pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) + pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2);
		features_array[bufpos + 4] = (mean_30 / pow(mean_00, 5.0 / 2.0) - 3 * mean_12 / pow(mean_00, 5.0 / 2.0)) * (mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0)) * (pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) - 3 * pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2)) + (3 * mean_21 / pow(mean_00, 5.0 / 2.0) - mean_03 / pow(mean_00, 5.0 / 2.0)) * (mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0)) * (3 * pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) - pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2));
		features_array[bufpos + 5] = (mean_20 / pow(mean_00, 2) - mean_02 / pow(mean_00, 2)) * (pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) - pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2)) + 4 * (mean_11 / pow(mean_00, 2)) * (mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0)) * (mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0));
		features_array[bufpos + 6] = (3 * mean_21 / pow(mean_00, 5.0 / 2.0) - mean_03 / pow(mean_00, 5.0 / 2.0)) * (mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0)) * (pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) - 3 * pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2)) - (mean_30 / pow(mean_00, 5.0 / 2.0) - 3 * mean_12 / pow(mean_00, 5.0 / 2.0)) * (mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0)) * (3 * pow(mean_30 / pow(mean_00, 5.0 / 2.0) + mean_12 / pow(mean_00, 5.0 / 2.0), 2) - pow(mean_21 / pow(mean_00, 5.0 / 2.0) + mean_03 / pow(mean_00, 5.0 / 2.0), 2));

		delete[] object_matris;
	}
	return features_array;
}