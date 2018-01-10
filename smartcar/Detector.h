#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/nonfree/nonfree.hpp"    
#include "opencv2/legacy/legacy.hpp" 
#include <iostream>
#include <time.h>
using namespace cv;
using namespace std;

class Detector
{
public:
	Detector(void);
	~Detector(void);
	void test(void);
	void processImage(Mat&);
};

