#include "Detector.h"


Detector::Detector(void)
{
}


Detector::~Detector(void)
{
}


void Detector::test(void) {
	VideoCapture capture;
	capture.open("5.avi");

	double rate = capture.get(CV_CAP_PROP_FPS);//获取视频文件的帧率
	int delay = cvRound(1000.000 / rate);

	if (capture.isOpened()) {
		while (true){
			Mat frame;
			capture >> frame;//读出每一帧的图像
			if (frame.empty()) break;
			imshow("处理前视频", frame);
			clock_t start = clock();
			processImage(frame);
			clock_t ends = clock();
			cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
			imshow("处理后视频", frame);
			waitKey(delay*2);
		}
	}
}


void Detector::processImage(Mat& frame) {
	Mat gary, histImg;
	cvtColor(frame, gary, CV_RGB2GRAY);
    equalizeHist(gary, histImg);
	vector<KeyPoint> keyPoints;

	//提取特征点    
    //SurfFeatureDetector surfDetector(40);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准 
    //surfDetector.detect(gary, keyPoints);

	FastFeatureDetector fast(30);
    fast.detect(histImg,keyPoints);

	//OrbFeatureDetector OrbDetector(500);
	//OrbDetector.detect(gary, keyPoints);

	drawKeypoints(frame, keyPoints, frame, Scalar(10,10,255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
}
