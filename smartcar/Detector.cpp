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
			Mat frame, gary;
			capture >> frame;//读出每一帧的图像
			if (frame.empty()) break;
			imshow("处理前视频", frame);
			clock_t start = clock();
			cvtColor(frame, gary, CV_RGB2GRAY);
			perspective(gary);
			processImage(gary);
			clock_t ends = clock();
			cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
			imshow("处理后视频", gary);
			waitKey(delay);
		}
	}
}


void Detector::processImage(Mat& gary) {
	Mat histImg;
    //equalizeHist(gary, histImg);
	vector<KeyPoint> keyPoints;

	//提取特征点    
    //SurfFeatureDetector surfDetector(40);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准 
    //surfDetector.detect(gary, keyPoints);

	FastFeatureDetector fast(30);
    fast.detect(gary,keyPoints);

	//OrbFeatureDetector OrbDetector(500);
	//OrbDetector.detect(gary, keyPoints);

	drawKeypoints(gary, keyPoints, gary, Scalar(10,10,255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
}


void Detector::perspective(Mat& src) {
                vector<Point> not_a_rect_shape;
                not_a_rect_shape.push_back(Point(0,0));
				not_a_rect_shape.push_back(Point(src.cols-1,0));
				not_a_rect_shape.push_back(Point(0,src.rows-1));
                not_a_rect_shape.push_back(Point(src.cols-1, src.rows-1));
                
                 //  topLeft, topRight, bottomRight, bottomLeft
                Point2f src_vertices[4];
                src_vertices[0] = not_a_rect_shape[0];
                src_vertices[1] = not_a_rect_shape[1];
                src_vertices[2] = not_a_rect_shape[2];
                src_vertices[3] = not_a_rect_shape[3];

                Point2f dst_vertices[4];
                dst_vertices[0] = Point(src.cols*0.1, src.rows*0);
                dst_vertices[1] = Point(src.cols*0.9,0);
				dst_vertices[2] = Point(src.cols*0.26,src.rows);
                dst_vertices[3] = Point(src.cols*0.66,src.rows);

				clock_t start = clock();

                Mat warpMatrix = getPerspectiveTransform(src_vertices, dst_vertices);
                Mat rotated;
                warpPerspective(src, rotated, warpMatrix, rotated.size(), INTER_LINEAR, BORDER_CONSTANT);

				clock_t ends = clock();
				cout <<"perspective Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;
               src = rotated;
}