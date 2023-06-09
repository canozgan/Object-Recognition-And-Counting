#pragma once
#include <atlstr.h>
#include "image.h"
#include "Clustering.h"
#include "Morphology.h"
#include "Labelling.h"
#include "Classification.h"
#include "TypeConversions.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

namespace ComputerVisionProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		int* rgb_img_data = NULL;
		int img_w, img_h;
		int* intensity_img_data = NULL;
		int* binary_img_data = NULL;
		int* labeled_img_data = NULL;
		int* label_list_array = NULL;
		int object_number;
		int* bounding_box_list = NULL;
		int* hist;
		double* features_array = NULL;
		int* test_result_data=NULL;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::ToolStripMenuItem^ clusteringToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ convertToIntensityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ extractHistogramToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::ToolStripMenuItem^ kMeansForEucledianDistanceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ morphologyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ conditionalDilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ labellingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ labelObjectsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ getObjectsBoundingBoxToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ classificationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ continueTraining;
	private: System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void Show_RGB_Images() {
			pictureBox1->Width = img_w;
			pictureBox1->Height = img_h;
			pictureBox1->Refresh();
			Bitmap^ surface = gcnew Bitmap(img_w, img_h);
			pictureBox1->Image = surface;
			int bufpos;
			Color c;
			for (int row = 0; row < img_h; row++)
				for (int col = 0; col < img_w; col++) {
					bufpos = (row * img_w + col) * 3;
					c = Color::FromArgb(rgb_img_data[bufpos], rgb_img_data[bufpos + 1], rgb_img_data[bufpos + 2]);
					surface->SetPixel(col, row, c);
				}
		}
		void Show_Intensity_Images() {
			Bitmap^ surface = gcnew Bitmap(img_w, img_h);
			pictureBox1->Image = surface;
			Color c;
			int bufpos;
			for (int row = 0; row < img_h; row++)
				for (int col = 0; col < img_w; col++) {
					bufpos = row * img_w + col;
					c = Color::FromArgb(intensity_img_data[bufpos], intensity_img_data[bufpos], intensity_img_data[bufpos]);
					surface->SetPixel(col, row, c);
				}
		}
		void Show_Binary_Images() {
			Bitmap^ surface = gcnew Bitmap(img_w, img_h);
			pictureBox1->Image = surface;
			Color c;
			int bufpos;
			for (int row = 0; row < img_h; row++)
				for (int col = 0; col < img_w; col++) {
					bufpos = row * img_w + col;
					if (binary_img_data[bufpos] == 1) {
						c = Color::FromArgb(0, 0, 0);
					}
					else {
						c = Color::FromArgb(255, 255, 255);
					}
					surface->SetPixel(col, row, c);
				}
		}
		void Show_Labeled_Images() {
			Bitmap^ surface = gcnew Bitmap(img_w, img_h);
			pictureBox1->Image = surface;
			Color c;
			int bufpos;
			for (int row = 0; row < img_h; row++)
				for (int col = 0; col < img_w; col++) {
					bufpos = row * img_w + col;
					if (binary_img_data[bufpos] == 1) {
						c = Color::FromArgb(0, 0, 0);
						if (labeled_img_data[bufpos] % 6 == 0) {
							c = Color::FromArgb(255, 0, 0);
						}
						else if (labeled_img_data[bufpos] % 6 == 1) {
							c = Color::FromArgb(0, 255, 0);
						}
						else if (labeled_img_data[bufpos] % 6 == 2) {
							c = Color::FromArgb(0, 0, 255);
						}
						else if (labeled_img_data[bufpos] % 6 == 3) {
							c = Color::FromArgb(255, 255, 0);
						}
						else if (labeled_img_data[bufpos] % 6 == 4) {
							c = Color::FromArgb(0, 255, 255);
						}
						else if (labeled_img_data[bufpos] % 6 == 5) {
							c = Color::FromArgb(255, 0, 255);
						}
					}
					else {
						c = Color::FromArgb(255, 255, 255);
					}
					surface->SetPixel(col, row, c);
				}
		}
		void Show_Test_Result(String^ message) {
			Bitmap^ surface = gcnew Bitmap(img_w, img_h);
			pictureBox1->Image = surface;
			Color c;
			int bufpos;
			for (int row = 0; row < img_h; row++)
				for (int col = 0; col < img_w; col++) {
					bufpos = row * img_w + col;
					if (test_result_data[bufpos] == 0) {
						c = Color::FromArgb(255, 255, 255);
					}
					else if (test_result_data[bufpos] == 1) {
						c = Color::FromArgb(255, 0, 0);
					}
					else if (test_result_data[bufpos] == 2) {
						c = Color::FromArgb(0, 255, 0);
					}
					else if (test_result_data[bufpos] == 3) {
						c = Color::FromArgb(0, 0, 255);
					}
					else if (test_result_data[bufpos] == 4) {
						c = Color::FromArgb(255, 255,0);
					}
					else if (test_result_data[bufpos] == 5) {
						c = Color::FromArgb(0, 255, 255);
					}
					else if (test_result_data[bufpos] == 6) {
						c = Color::FromArgb(255, 0, 255);
					}
					else if (test_result_data[bufpos] == 7) {
						c = Color::FromArgb(0, 0, 0);
					}
					surface->SetPixel(col, row, c);
				}
			MessageBox::Show(message);
		}

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clusteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->convertToIntensityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->extractHistogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansForEucledianDistanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->morphologyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->conditionalDilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labellingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->labelObjectsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->getObjectsBoundingBoxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->classificationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->continueTraining = (gcnew System::Windows::Forms::Button());
			this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->fileToolStripMenuItem,
					this->clusteringToolStripMenuItem, this->morphologyToolStripMenuItem, this->labellingToolStripMenuItem, this->classificationToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1526, 33);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(122, 29);
			this->fileToolStripMenuItem->Text = L"Load Image";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(158, 34);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// clusteringToolStripMenuItem
			// 
			this->clusteringToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->convertToIntensityToolStripMenuItem,
					this->extractHistogramToolStripMenuItem, this->kMeansForEucledianDistanceToolStripMenuItem, this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem
			});
			this->clusteringToolStripMenuItem->Name = L"clusteringToolStripMenuItem";
			this->clusteringToolStripMenuItem->Size = System::Drawing::Size(107, 29);
			this->clusteringToolStripMenuItem->Text = L"Clustering";
			// 
			// convertToIntensityToolStripMenuItem
			// 
			this->convertToIntensityToolStripMenuItem->Name = L"convertToIntensityToolStripMenuItem";
			this->convertToIntensityToolStripMenuItem->Size = System::Drawing::Size(554, 34);
			this->convertToIntensityToolStripMenuItem->Text = L"Convert To Intensity";
			this->convertToIntensityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::convertToIntensityToolStripMenuItem_Click);
			// 
			// extractHistogramToolStripMenuItem
			// 
			this->extractHistogramToolStripMenuItem->Name = L"extractHistogramToolStripMenuItem";
			this->extractHistogramToolStripMenuItem->Size = System::Drawing::Size(554, 34);
			this->extractHistogramToolStripMenuItem->Text = L"Extract Histogram";
			this->extractHistogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::extractHistogramToolStripMenuItem_Click);
			// 
			// kMeansForEucledianDistanceToolStripMenuItem
			// 
			this->kMeansForEucledianDistanceToolStripMenuItem->Name = L"kMeansForEucledianDistanceToolStripMenuItem";
			this->kMeansForEucledianDistanceToolStripMenuItem->Size = System::Drawing::Size(554, 34);
			this->kMeansForEucledianDistanceToolStripMenuItem->Text = L"K-Means Clustering According To Euclidean Distance";
			this->kMeansForEucledianDistanceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansClusteringAccordingToEucledianDistanceToolStripMenuItem_Click);
			// 
			// kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem
			// 
			this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem->Name = L"kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem";
			this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem->Size = System::Drawing::Size(554, 34);
			this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem->Text = L"K-Means Clustering According To Mahalanobis Distance";
			this->kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem_Click);
			// 
			// morphologyToolStripMenuItem
			// 
			this->morphologyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->erosionToolStripMenuItem,
					this->dilationToolStripMenuItem, this->conditionalDilationToolStripMenuItem
			});
			this->morphologyToolStripMenuItem->Name = L"morphologyToolStripMenuItem";
			this->morphologyToolStripMenuItem->Size = System::Drawing::Size(128, 29);
			this->morphologyToolStripMenuItem->Text = L"Morphology";
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(271, 34);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(271, 34);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// conditionalDilationToolStripMenuItem
			// 
			this->conditionalDilationToolStripMenuItem->Name = L"conditionalDilationToolStripMenuItem";
			this->conditionalDilationToolStripMenuItem->Size = System::Drawing::Size(271, 34);
			this->conditionalDilationToolStripMenuItem->Text = L"Conditional Dilation";
			this->conditionalDilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::conditionalDilationToolStripMenuItem_Click);
			// 
			// labellingToolStripMenuItem
			// 
			this->labellingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->labelObjectsToolStripMenuItem,
					this->getObjectsBoundingBoxToolStripMenuItem
			});
			this->labellingToolStripMenuItem->Name = L"labellingToolStripMenuItem";
			this->labellingToolStripMenuItem->Size = System::Drawing::Size(98, 29);
			this->labellingToolStripMenuItem->Text = L"Labelling";
			// 
			// labelObjectsToolStripMenuItem
			// 
			this->labelObjectsToolStripMenuItem->Name = L"labelObjectsToolStripMenuItem";
			this->labelObjectsToolStripMenuItem->Size = System::Drawing::Size(322, 34);
			this->labelObjectsToolStripMenuItem->Text = L"Label Objects";
			this->labelObjectsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::labelObjectsToolStripMenuItem_Click);
			// 
			// getObjectsBoundingBoxToolStripMenuItem
			// 
			this->getObjectsBoundingBoxToolStripMenuItem->Name = L"getObjectsBoundingBoxToolStripMenuItem";
			this->getObjectsBoundingBoxToolStripMenuItem->Size = System::Drawing::Size(322, 34);
			this->getObjectsBoundingBoxToolStripMenuItem->Text = L"Get Objects Bounding Box";
			this->getObjectsBoundingBoxToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::getObjectsBoundingBoxToolStripMenuItem_Click);
			// 
			// classificationToolStripMenuItem
			// 
			this->classificationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->trainingToolStripMenuItem,
					this->testingToolStripMenuItem
			});
			this->classificationToolStripMenuItem->Name = L"classificationToolStripMenuItem";
			this->classificationToolStripMenuItem->Size = System::Drawing::Size(130, 29);
			this->classificationToolStripMenuItem->Text = L"Classification";
			// 
			// trainingToolStripMenuItem
			// 
			this->trainingToolStripMenuItem->Name = L"trainingToolStripMenuItem";
			this->trainingToolStripMenuItem->Size = System::Drawing::Size(270, 34);
			this->trainingToolStripMenuItem->Text = L"Training";
			this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::trainingToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(37, 124);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(627, 410);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(797, 124);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series1->Legend = L"Legend1";
			series1->Name = L"Histogram";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(666, 410);
			this->chart1->TabIndex = 2;
			this->chart1->Text = L"chart1";
			this->chart1->Visible = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(37, 62);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(417, 26);
			this->textBox1->TabIndex = 3;
			this->textBox1->Visible = false;
			// 
			// continueTraining
			// 
			this->continueTraining->Location = System::Drawing::Point(477, 58);
			this->continueTraining->Name = L"continueTraining";
			this->continueTraining->Size = System::Drawing::Size(172, 35);
			this->continueTraining->TabIndex = 4;
			this->continueTraining->Text = L"Continue Training";
			this->continueTraining->UseVisualStyleBackColor = true;
			this->continueTraining->Visible = false;
			this->continueTraining->Click += gcnew System::EventHandler(this, &MyForm::continueTraining_Click);
			// 
			// testingToolStripMenuItem
			// 
			this->testingToolStripMenuItem->Name = L"testingToolStripMenuItem";
			this->testingToolStripMenuItem->Size = System::Drawing::Size(270, 34);
			this->testingToolStripMenuItem->Text = L"Testing";
			this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::testingToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1526, 673);
			this->Controls->Add(this->continueTraining);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			if (im.c != 3) {
				MessageBox::Show("Please choose an image in RGB format!");
			}
			else {
				rgb_img_data = im.data;
				img_w = im.w;
				img_h = im.h;
				Show_RGB_Images();
				MessageBox::Show("Image opened successfully.");
			}
			
		}
		
	}
	private: System::Void convertToIntensityToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (rgb_img_data == NULL) {
			MessageBox::Show("Image must be selected first.");
		}
		else {
			intensity_img_data = RGB_To_Intensity(img_w,img_h,rgb_img_data);
			Show_Intensity_Images();
			MessageBox::Show("Image was successfully converted to intensity level");
		}
	}
	private: System::Void extractHistogramToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (intensity_img_data == NULL) {
			MessageBox::Show("Image must be converted to intensity level first");
		}
		else {
			hist = Histogram(img_w,img_h,intensity_img_data);
			chart1->Visible = true;
			chart1->Series["Histogram"]->Points->Clear();
			chart1->Location = System::Drawing::Point(pictureBox1->Width + 200, 100);
			for (int i = 0; i < 256; i++) {
				chart1->Series["Histogram"]->Points->AddXY(i, hist[i]);
			}
			MessageBox::Show("The histogram was successfully extracted.");
		}
	}
	private: System::Void kMeansClusteringAccordingToEucledianDistanceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (hist == NULL) {
			MessageBox::Show("The histogram must be extracted first.");
		}
		else {
			chart1->Visible = false;
			double* k_means = k_means_euclidean_dist(hist);
			binary_img_data = Intensity_To_Binary(img_w,img_h,intensity_img_data, k_means[0], k_means[1]);
			Show_Binary_Images();
			MessageBox::Show("Clustering completed successfully.");
		}

	}
	private: System::Void kMeansClusteringAccordingToMahalanobisDistanceToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (hist == NULL) {
			MessageBox::Show("The histogram must be extracted first.");
		}
		else {
			chart1->Visible = false;
			double* k_means = k_means_mahalanobis_dist(hist);
			binary_img_data = Intensity_To_Binary(img_w, img_h, intensity_img_data, k_means[0], k_means[1]);
			Show_Binary_Images();
			MessageBox::Show("Clustering completed successfully.");
		}
	}
	private: System::Void erosionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (binary_img_data == NULL) {
			MessageBox::Show("Clustering should be done according to euclidean distance or mahalanobis distance first.");
		}
		else {
			binary_img_data = erosion(img_w,img_h,binary_img_data);
			Show_Binary_Images();
			MessageBox::Show("Erosion process completed successfully.");
		}
	}
	private: System::Void dilationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (binary_img_data == NULL) {
			MessageBox::Show("Clustering should be done according to euclidean distance or mahalanobis distance first.");
		}
		else {
			binary_img_data = dilation(img_w, img_h, binary_img_data);
			Show_Binary_Images();
			MessageBox::Show("Dilation process completed successfully.");
		}

	}
	private: System::Void conditionalDilationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (binary_img_data == NULL) {
			MessageBox::Show("Clustering should be done according to euclidean distance or mahalanobis distance first.");
		}
		else {
			binary_img_data = conditionalDilation(img_w, img_h, binary_img_data);
			Show_Binary_Images();
			MessageBox::Show("Conditional Dilation process completed successfully.");
		}
	}
	private: System::Void labelObjectsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (binary_img_data == NULL) {
			MessageBox::Show("Clustering should be done according to euclidean distance or mahalanobis distance first.");
		}
		else {
			result_of_labelling result = labelObjects(img_w,img_h,binary_img_data);
			labeled_img_data = result.data;
			label_list_array = result.label_list_array;
			object_number = result.object_number;
			Show_Labeled_Images();
			if (object_number == 0) {
				String^ s = "Object not detected!";
				MessageBox::Show(s);
			}
			else {
				String^ s = "Objects successfully labeled. " + object_number + " objects detected.";
				MessageBox::Show(s);
			}
		}

		
	}
	private: System::Void getObjectsBoundingBoxToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (labeled_img_data == NULL) {
			MessageBox::Show("Labelling objects must be done first.");
		}
		else {
			bounding_box_list = getObjectBoundingBox(img_w, img_h, object_number, label_list_array, labeled_img_data);
			MessageBox::Show("Objects successfully transferred to the bounding box.");
		}
	}
	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (bounding_box_list == NULL) {
			MessageBox::Show("Get Into Bounding Box must be done first.");
		}
		else {
			MessageBox::Show("Type the name of the object in the text box that will open above.");
			textBox1->Visible = Visible;
			continueTraining->Visible = Visible;
		}
	}
	private: System::Void continueTraining_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->TextLength == 0) {
			MessageBox::Show("Please enter a name.");
		}
		else {
			textBox1->Visible = FALSE;
			continueTraining->Visible = FALSE;
			features_array = extractFeaturesOfObjects(img_w, img_h, object_number, bounding_box_list, binary_img_data);
			std::ofstream file("data.txt", std::ios::app);
			if (file.is_open()) {
				std::string name = "";
				for (int i = 0; i < textBox1->TextLength; i++) {
					name = addCharToStdString(name, textBox1->Text[i]);
				}
				file << name << "\n";
				double pay_k_means_array[7] = { 0,0,0,0,0,0,0 };
				for (int i = 0; i < object_number; i++) {
					int bufpos = i * 7;
					for (int k = 0; k < 7; k++) {
						pay_k_means_array[k] += features_array[bufpos + k];
					}

				}

				for (int i = 0; i < 7; i++) {
					file << pay_k_means_array[i] / object_number << "\n";
				}

				file.close();
				MessageBox::Show("The training process has been successfully completed.");
			}
			else {
				MessageBox::Show("The file could not be opened.The file could not be opened. If the file is open, close it and try again.");
			}
		}
	}
	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (bounding_box_list == NULL) {
			MessageBox::Show("Getting Into Bounding Box must be done first.");
		}
		else {
			features_array = extractFeaturesOfObjects(img_w, img_h, object_number, bounding_box_list, binary_img_data);
			std::ifstream file("data.txt");
			if (file.is_open()) {
				std::string row = "";
				int size = 0;
				while (getline(file, row)) {
					size++;
				}
				file.close();
				if (size != 0) {
					std::vector<std::string> name_list;
					std::vector<double> feature_1_list;
					std::vector<double> feature_2_list;
					std::vector<double> feature_3_list;
					std::vector<double> feature_4_list;
					std::vector<double> feature_5_list;
					std::vector<double> feature_6_list;
					std::vector<double> feature_7_list;
					String^ str = "";
					int mod = 0;
					std::ifstream file("data.txt");
					if (file.is_open()) {
						while (getline(file, row)) {
							str = stdStringToSystemString(row);
							if (mod % 8 == 0) {
								name_list.push_back(row);
							}
							else if (mod % 8 == 1)
							{
								feature_1_list.push_back(systemStringToDouble(str));
							}
							else if (mod % 8 == 2)
							{
								feature_2_list.push_back(systemStringToDouble(str));
							}
							else if (mod % 8 == 3)
							{
								feature_3_list.push_back(systemStringToDouble(str));
							}
							else if (mod % 8 == 4)
							{
								feature_4_list.push_back(systemStringToDouble(str));
							}
							else if (mod % 8 == 5)
							{
								feature_5_list.push_back(systemStringToDouble(str));
							}
							else if (mod % 8 == 6)
							{
								feature_6_list.push_back(systemStringToDouble(str));
							}
							else {
								feature_7_list.push_back(systemStringToDouble(str));
							}
							mod++;
						}
						test_result_data = new int[img_w * img_h];
						String^ s1 = "", ^ s2 = "", ^ s3 = "", ^ s4 = "", ^ s5 = "", ^ s6 = "";
						int bufpos;
						for (int row = 0; row < img_h; row++)
							for (int col = 0; col < img_w; col++) {
								bufpos = row * img_w + col;
								if (binary_img_data[bufpos] == 1) {
									int label = labeled_img_data[bufpos];
									int object_index = 0;
									for (int i = 0; i < object_number; i++) {
										if (label_list_array[i] == label) {
											object_index = i;
										}
									}
									double minimum_distance = 10000000;
									int minimun_index = 0;
									for (int i = 0; i < name_list.size(); i++) {
										double distance = pow(feature_1_list.at(i) - features_array[object_index * 7], 2) + pow(feature_2_list.at(i) - features_array[object_index * 7 + 1], 2) + pow(feature_3_list.at(i) - features_array[object_index * 7 + 2], 2) + pow(feature_4_list.at(i) - features_array[object_index * 7 + 3], 2) + pow(feature_5_list.at(i) - features_array[object_index * 7 + 4], 2) + pow(feature_6_list.at(i) - features_array[object_index * 7 + 5], 2) + pow(feature_7_list.at(i) - features_array[object_index * 7 + 6], 2);
										if (distance < minimum_distance) {
											minimum_distance = distance;
											minimun_index = i;
										}
									}
									if (minimun_index == 0) {
										test_result_data[bufpos] = 1;
										s1 =stdStringToSystemString(name_list.at(0)) + " -> Red Color\n";
									}
									else if (minimun_index == 1) {
										test_result_data[bufpos] = 2;
										s2 =stdStringToSystemString(name_list.at(1)) + " -> Green Color\n";
									}
									else if (minimun_index == 2) {
										test_result_data[bufpos] = 3;
										s3 =stdStringToSystemString(name_list.at(2)) + " -> Blue Color\n";
									}
									else if (minimun_index == 3) {
										test_result_data[bufpos] = 4;
										s4 =stdStringToSystemString(name_list.at(3)) + " = Yellow Color\n";
									}
									else if (minimun_index == 4) {
										test_result_data[bufpos] = 5;
										s5 = stdStringToSystemString(name_list.at(4)) + " = Cyan Color\n";
									}
									else if (minimun_index == 5) {
										test_result_data[bufpos] = 6;
										s6 = stdStringToSystemString(name_list.at(5)) + " = Purple Color\n";
									}
									else {
										test_result_data[bufpos] = 7;
									}
								}
								else {
									test_result_data[bufpos] = 0;
								}
							}
						String^ message = "Total number of objects is " + object_number + "\n" + s1 + s2 + s3 + s4 + s5 + s6;
						Show_Test_Result(message);
					}
					else {
						MessageBox::Show("The file could not be opened.The file could not be opened. If the file is open, close it and try again.");
					}
				}
				else {
					MessageBox::Show("You must have trained at least once for the test.");
				}
			}
			else {
				MessageBox::Show("The file could not be opened.The file could not be opened. If the file is open, close it and try again.");
			}
			
		}	
		
	}
};
}
