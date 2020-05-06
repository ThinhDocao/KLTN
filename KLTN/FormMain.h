#pragma once

#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/ml.h>
#include<opencv/cxcore.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include<stdio.h>	
#include<conio.h>	
#include<string.h>	
#include <msclr\marshal_cppstd.h>
#include "PlateFinder.h"	
#include <iostream>


namespace KLTN {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace cv;
	using namespace std;
	using namespace SVM;
	using namespace Emgu::CV::Structure;
	using namespace Emgu::CV;

	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;


	/// <summary>
	/// Summary for FormMain
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
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
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(319, 25);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 37);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Browser";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormMain::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(25, 25);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(288, 211);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(454, 25);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(288, 211);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(778, 392);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:char* ConverStringToChar(System::String^ str)
	{
		char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		return str2;
	}
	public: Model ^g_modelNum;
	public: Model ^g_modelCharNum;
	public: cv::CascadeClassifier *g_plateDetector;
	public: cv::CascadeClassifier *g_charDetector;
	//private:void LoadData()
	//{
	//		g_modelCharNum = Model::Read("svmCharNum.model");
	//		g_plateDetector = new CascadeClassifier("bienso.xml"); //Load file training biá»ƒn sá»‘
	//		g_charDetector = new CascadeClassifier("kytu.xml"); //Load file traning kÃ­ tá»±
	//		g_modelNum = Model::Read("svmNum.model");
	//}


	public:System::String^ IntToChar(int i)
	{
		string chars[] = { "A", "B", "C", "D", "E", "F", "G", "H", "K", "L", "M", "N", "P", "R", "S", "T", "U", "V", "X", "Y", "Z" };
		//				    10   11  12    13   14   15   16   17   18   19   20    21   22  23   24   25   26   27   28   29  30


			//chuyá»ƒn cÃ¡c nhÃ£n Ä‘Æ°á»£c SVM nháº­n dáº¡ng thÃ nh kÃ½ tá»±
			if (i < 10)
			{
				return i.ToString();
			}
		return marshal_as<System::String^>(chars[i - 10]);
	}

	public: int PredictSVM(System::String ^binaryStringSVM, Model ^model)
	{
		//sá»­ dá»¥ng SVM Ä‘á»ƒ nháº­n dáº¡ng kÃ½ tá»±
		/*string kytu = ""; */
		
		File::WriteAllText("test.test", "0 " + binaryStringSVM);

		Problem ^test = Problem::Read("test.test");
		Prediction::Predict(test, "result.out", model, false);

		System::String^ kytu = File::ReadAllText("result.out");
		
		return int::Parse(kytu->Trim());

	}

	public: System::String ^ImageToSVMToBinaryString(Emgu::CV::Image<Gray, byte> ^img)
	{
		if (img->Data->Length == 0)
		{
			return "";
		}
		System::String ^result ="";


		double dblmucxam = img->GetAverage().Intensity;
		int index = 0;
		for (int m = 0; m <= img->Height - 1; m++)
		{
			for (int n = 0; n <= img->Width - 1; n++)
			{
				if (img[m, n].Intensity > dblmucxam)
				{
					index = m * img->Width + n + 1;
					result += index.ToString() + ":1 ";
				}
			}
		}

		return result;
	}

		  public:System::String ^PredictSVM(Emgu::CV::Image<Gray, byte> img,System::String ^type)
		  {
			  if (img.Data->Length!=0 )
			  {
				  Emgu::CV::Image<Gray, byte> ^grayImg = img.Convert<Gray, byte>();
				  
				  grayImg->Not();


				  System::String ^binaryString = ImageToSVMToBinaryString(grayImg);
				  if (type == "num")
				  {
					  return System::Convert::ToString(PredictSVM(binaryString, g_modelNum));
				  }
				  return IntToChar(PredictSVM(binaryString, g_modelCharNum));
			  }
			  return "_";
		  }





	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ dlg = gcnew OpenFileDialog; //gcnew dọn rác khi k dùng tới
		dlg->Filter = "Image (*.bmp; *.jpg;*.jpeg;*.png) |*.bmp; *.jpg;*.jpeg;*.png|All files(*.*)|*.*||";

		if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		char* ss = ConverStringToChar(dlg->FileName);
		Bitmap^ bmp = gcnew Bitmap(dlg->FileName);  //Load Image khi click Browse
		pictureBox1->Image = bmp;
		pictureBox1->Refresh();

		Emgu::CV::Image<Bgr, Byte>^ img1 = gcnew Emgu::CV::Image<Bgr, Byte>(480, 320);
		/*System::String ^s= ImageToSVMToBinaryString(img);*/
		/*Emgu::CV::Image<Bgr, byte> ^img = gcnew Emgu::CV::Image<Bgr, byte>(bmp);

		bmp = img->ToBitmap();
		pictureBox2->Image = bmp;
		pictureBox2->Refresh();*/
		/*PlateFinder f;
		f.ImageRestoration(ss);*/
		/*LoadData();*/

		///
		
	}
	};
}
