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

	double rate = capture.get(CV_CAP_PROP_FPS);//��ȡ��Ƶ�ļ���֡��
	int delay = cvRound(1000.000 / rate);

	if (capture.isOpened()) {
		while (true){
			Mat frame;
			capture >> frame;//����ÿһ֡��ͼ��
			if (frame.empty()) break;
			imshow("����ǰ��Ƶ", frame);
			clock_t start = clock();
			processImage(frame);
			clock_t ends = clock();
			cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
			imshow("�������Ƶ", frame);
			waitKey(delay*2);
		}
	}
}


void Detector::processImage(Mat& frame) {
	Mat gary, histImg;
	cvtColor(frame, gary, CV_RGB2GRAY);
    equalizeHist(gary, histImg);
	vector<KeyPoint> keyPoints;

	//��ȡ������    
    //SurfFeatureDetector surfDetector(40);  // ����������ֵ��������������ȣ�ֵԽ���Խ�٣�Խ��׼ 
    //surfDetector.detect(gary, keyPoints);

	FastFeatureDetector fast(30);
    fast.detect(histImg,keyPoints);

	//OrbFeatureDetector OrbDetector(500);
	//OrbDetector.detect(gary, keyPoints);

	drawKeypoints(frame, keyPoints, frame, Scalar(10,10,255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
}
