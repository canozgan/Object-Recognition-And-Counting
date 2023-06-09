#include "Labelling.h"
result_of_labelling labelObjects(int w, int h, int* binary_img_data){
	result_of_labelling result;
	result.data = new int[w * h];
	int label_counter = 1;
	std::vector<int> label_list;
	std::vector<int> collision_list;
	std::vector<int> labels_around;
	for (int i = 0; i < w * h; i++) {
		if (binary_img_data[i] == 0) {
			result.data[i] = 0;
		}
		else {
			if ((i + 1) % w != 1 && (i + 1 - w) > 0) {
				if (result.data[i - w - 1] != 0) {
					labels_around.push_back(result.data[i - w - 1]);
				}
			}
			if ((i + 1 - w) > 0) {
				if (result.data[i - w] != 0) {
					labels_around.push_back(result.data[i - w]);
				}
			}
			if ((i + 1) % w != 0 && (i + 1 - w) > 0) {
				if (result.data[i - w + 1] != 0) {
					labels_around.push_back(result.data[i - w + 1]);
				}
			}
			if ((i + 1) % w != 1) {
				if (result.data[i - 1] != 0) {
					labels_around.push_back(result.data[i - 1]);
				}
			}

			if (labels_around.size() == 0) {
				result.data[i] = label_counter++;
				label_list.push_back(result.data[i]);
			}
			else if (labels_around.size() == 1) {
				result.data[i] = labels_around.at(0);
			}
			else {
				bool all_equal = true;
				int first_label = labels_around.at(0);
				for (int j = 0; j < labels_around.size(); j++) {
					if (first_label != labels_around.at(j)) {
						all_equal = false;
					}
				}
				if (all_equal) {
					result.data[i] = first_label;
				}
				else {
					int small_label = 1000000;
					for (int j = 0; j < labels_around.size(); j++) {
						if (labels_around.at(j) < small_label) {
							small_label = labels_around.at(j);
						}
					}
					result.data[i] = small_label;
					collision_list.push_back(i);
				}

			}
			labels_around.clear();
		}
	}

	for (int i = 0; i < collision_list.size(); i++) {
		int collision_index = collision_list.at(i);

		if ((collision_index + 1) % w != 1 && (collision_index + 1 - w) > 0) {
			if (result.data[collision_index - w - 1] != 0) {
				labels_around.push_back(result.data[collision_index - w - 1]);
			}
		}
		if ((collision_index + 1 - w) > 0) {
			if (result.data[collision_index - w] != 0) {
				labels_around.push_back(result.data[collision_index - w]);
			}
		}
		if ((collision_index + 1) % w != 0 && (collision_index + 1 - w) > 0) {
			if (result.data[collision_index - w + 1] != 0) {
				labels_around.push_back(result.data[collision_index - w + 1]);
			}
		}
		if ((collision_index + 1) % w != 1) {
			if (result.data[collision_index - 1] != 0) {
				labels_around.push_back(result.data[collision_index - 1]);
			}
		}
		int small_label = 1000;
		for (int j = 0; j < labels_around.size(); j++) {
			if (labels_around.at(j) < small_label) {
				small_label = labels_around.at(j);
			}
		}
		for (int j = 0; j < w * h; j++) {
			for (int k = 0; k < labels_around.size(); k++) {
				if (result.data[j] == labels_around.at(k)) {
					result.data[j] = small_label;
				}
			}
		}
		std::vector<int> label_list_to_remove;
		for (int j = 0; j < labels_around.size(); j++) {
			for (int k = 0; k < label_list.size(); k++) {
				if (labels_around.at(j) == label_list.at(k) && labels_around.at(j) != small_label) {
					label_list.erase(label_list.begin() + k);
				}
			}
		}

		labels_around.clear();
	}
	result.object_number = label_list.size();
	result.label_list_array = new int[result.object_number];
	for (int i = 0; i < result.object_number; i++) {
		result.label_list_array[i] = label_list.at(i);
	}
	return result;
}
int* getObjectBoundingBox(int w, int h, int object_number, int* label_list_array, int* labeled_img_data) {
	int* bounding_box_list = new int[object_number * 4];
	int counter = 0;
	for (int i = 0; i < object_number; i++) {

		//for min row
		for (int row = 0; row < h; row++) {
			bool finish_scanning = false;
			for (int column = 0; column < w; column++) {
				if (labeled_img_data[row * w + column] == label_list_array[i]) {
					bounding_box_list[counter++] = row;
					finish_scanning = true;
					break;
				}
			}
			if (finish_scanning) {
				break;
			}
		}
		//for max row
		int max_row;
		for (int row = 0; row < h; row++) {
			for (int column = 0; column < w; column++) {
				if (labeled_img_data[row * w + column] == label_list_array[i]) {
					max_row = row;
				}
			}
		}
		bounding_box_list[counter++] = max_row;

		//for min col
		for (int column = 0; column < w; column++) {
			bool finish_scanning = false;
			for (int row = 0; row < h; row++) {
				if (labeled_img_data[row * w + column] == label_list_array[i]) {
					bounding_box_list[counter++] = column;
					finish_scanning = true;
					break;
				}
			}
			if (finish_scanning) {
				break;
			}
		}
		//for max col
		int max_column;
		for (int column = 0; column < w; column++) {
			for (int row = 0; row < h; row++) {
				if (labeled_img_data[row * w + column] == label_list_array[i]) {
					max_column = column;
				}
			}
		}
		bounding_box_list[counter++] = max_column;
	}
	return bounding_box_list;
}
