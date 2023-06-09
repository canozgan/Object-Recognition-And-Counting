#include "Morphology.h"
int* erosion(int w, int h, int* binary_img_data){
	int* erosioned_img_data = new int[w * h];
	int top_left, top, top_right, left, right, bottom_left, bottom, bottom_right;


	for (int i = 0; i < w * h; i++) {
		erosioned_img_data[i] = 0;
	}
	for (int i = 0; i < w * h; i++) {
		if (binary_img_data[i] == 1 && (i + 1) % w != 1 && (i + 1) % w != 0 && (i + 1 - w) > 0 && (i + 1 + w) <= w * h) {


			top_left = binary_img_data[(i - w - 1)];

			top = binary_img_data[(i - w)];

			top_right = binary_img_data[(i - w + 1)];

			left = binary_img_data[(i - 1)];

			right = binary_img_data[(i + 1)];

			bottom_left = binary_img_data[(i + w - 1)];

			bottom = binary_img_data[(i + w)];

			bottom_right = binary_img_data[(i + w + 1)];

			if (top_left == 1 && top == 1 && top_right == 1 && left == 1 && right == 1 && bottom_left == 1 && bottom == 1 && bottom_right == 1) {
				erosioned_img_data[i] = 1;
			}
			else {
				erosioned_img_data[i] = 0;
			}

		}
		else {
			erosioned_img_data[i] = 0;
		}
	}
	return erosioned_img_data;
}
int* dilation(int w, int h, int* binary_img_data){
	int* dilationed_img_data = new int[w * h];

	for (int i = 0; i < w * h; i++) {

		dilationed_img_data[i] = 0;
	}

	for (int i = 0; i < w * h; i++) {
		if (binary_img_data[i] == 1) {

			dilationed_img_data[i] = 1;

			if ((i + 1) % w != 1 && (i + 1 - w) > 0) {
				dilationed_img_data[(i - w - 1)] = 1;
			}
			if ((i + 1 - w) > 0) {
				dilationed_img_data[(i - w)] = 1;
			}
			if ((i + 1) % w != 0 && (i + 1 - w) > 0) {
				dilationed_img_data[(i - w + 1)] = 1;
			}
			if ((i + 1) % w != 1) {
				dilationed_img_data[(i - 1)] = 1;
			}
			if ((i + 1) % w != 0) {
				dilationed_img_data[(i + 1)] = 1;
			}
			if ((i + 1) % w != 1 && (i + 1 + w) <= w * h) {
				dilationed_img_data[(i + w - 1)] = 1;
			}
			if ((i + 1 + w) <= w * h) {
				dilationed_img_data[(i + w)] = 1;
			}
			if ((i + 1) % w != 0 && (i + 1 + w) <= w * h) {
				dilationed_img_data[(i + w + 1)] = 1;
			}

		}
	}
	return dilationed_img_data;
}
int* conditionalDilation(int w, int h, int* binary_img_data){
	int* dilationed_img_data = new int[w * h];

	unsigned char* binary_img_data_complement = new unsigned char[w * h];
	unsigned char* first_img_data = new unsigned char[w * h];
	unsigned char* second_img_data = new unsigned char[w * h];

	for (int i = 0; i < w * h; i++) {

		dilationed_img_data[i] = 1;

		first_img_data[i] = 0;

		second_img_data[i] = 0;

		if (binary_img_data[i] == 1) {
			binary_img_data_complement[i] = 0;
		}
		else {
			binary_img_data_complement[i] = 1;
		}
	}
	for (int i = 0; i < w * h; i++) {
		if (binary_img_data[i] == 0) {
			first_img_data[i] = 1;
			bool equalite = true;
			std::vector<int> first;
			first.push_back(i);
			std::vector<int> second;
			std::vector<int> third;
			while (true) {
				for (int k = 0; k < first.size(); k++) {
					int j = first.at(k);
					if (second_img_data[j] == 0) {
						second_img_data[j] = 1;
						second.push_back(j);
					}
					if ((j + 1 - w) > 0) {
						if (second_img_data[(j - w)] == 0) {
							second_img_data[(j - w)] = 1;
							second.push_back((j - w));
						}

					}
					if ((j + 1) % w != 1) {
						if (second_img_data[(j - 1)] == 0) {
							second_img_data[(j - 1)] = 1;
							second.push_back((j - 1));
						}
					}
					if ((j + 1) % w != 0) {
						if (second_img_data[(j + 1)] == 0) {
							second_img_data[(j + 1)] = 1;
							second.push_back((j + 1));
						}
					}
					if ((j + 1 + w) <= w * h) {
						if (second_img_data[(j + w)] == 0) {
							second_img_data[(j + w)] = 1;
							second.push_back((j + w));
						}
					}
				}
				for (int k = 0; k < second.size(); k++) {
					int j = second.at(k);
					if (second_img_data[j] == 1 && binary_img_data_complement[j] == 1) {
						third.push_back(j);
					}
					else {
						second_img_data[j] = 0;
					}
				}

				if (first.size() == third.size()) {
					equalite = true;
				}
				else {
					equalite = false;
				}



				if (equalite == false) {
					first.clear();
					second.clear();
					for (int k = 0; k < third.size(); k++) {
						int j = third.at(k);
						first_img_data[j] = second_img_data[j];
						second_img_data[j] = 0;
						first.push_back(j);
					}
					third.clear();
				}
				else {
					break;
				}
			}
			for (int k = 0; k < third.size(); k++) {
				int j = third.at(k);
				dilationed_img_data[j] = 0;
				first_img_data[j] = 0;
				second_img_data[j] = 0;
			}
			break;

		}
	}
	return dilationed_img_data;

}