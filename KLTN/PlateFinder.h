#pragma once
#include "opencv2\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>

#include <opencv2/opencv.hpp>
#include <vector>
#include <assert.h>


class PlateFinder
{
private:
	IplConvKernel* S1;  //Ma trận nhân S1
	IplConvKernel* S2;  //Ma trận nhân S2
	IplImage* plate;  //Ảnh kết quả biển số




public:
	PlateFinder(void);
	virtual ~PlateFinder(void);
	void ImageRestoration(char* Anh);  //Hàm truyền vào ảnh gốc (Ảnh xám)  (Tiền xử lí ảnh)
	
};