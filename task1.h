#ifndef TASK1_H
#define TASK1_H
#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <string>

using namespace cv;
using namespace std;

void click_event(int event, int x, int y,int ,void* data){
	vector<Point2f> *pts_src = (vector<Point2f>*) data;
	if(event == EVENT_LBUTTONDOWN){
		pts_src->push_back(Point2f(x,y));
		return;
	}
}
struct imgHomography {
	Mat H;
	int w, h;
};
int dist(int x1,int y1,int x2,int y2){
	return sqrt(pow(x2 - x1, 2)+pow(y2 - y1, 2));
}
Mat fun2(Mat img_src, imgHomography H1){
	if(img_src.empty()){
		printf("Image is Empty!");
		exit(1);
	}
	Mat img_trans;	
	warpPerspective(img_src, img_trans, H1.H, img_src.size());
	Mat img_crop;
	img_trans(Rect(472,52,H1.w,H1.h)).copyTo(img_crop);
	return img_crop;	
}

imgHomography fun(string argv){
	string filename = argv;
	Mat img_src = imread(filename, IMREAD_GRAYSCALE);
	if(img_src.empty()){
		printf("Image is Empty!");
		exit(1);
	}
	vector<Point2f> pts_src;
	vector<Point2f> pts_dst;
	int k;
	Mat img_trans;
	imgHomography H1;
	do{
		pts_src.clear();
		pts_dst.clear();
		destroyAllWindows();
		namedWindow("Original Greyscale Image", WINDOW_AUTOSIZE);
		setMouseCallback("Original Greyscale Image",click_event,&pts_src);
		while(pts_src.size()<4){
			imshow("Original Greyscale Image", img_src);
			k=waitKey(1);
			if(k=='e'||k=='E'){
				return H1;
			}
		}
		destroyAllWindows();
	
		H1.w = dist(pts_src[0].x,pts_src[0].y,pts_src[1].x,pts_src[1].y);
		H1.h = (dist(pts_src[0].x,pts_src[0].y,pts_src[3].x,pts_src[3].y)+dist(pts_src[2].x,pts_src[2].y,pts_src[1].x,pts_src[1].y))/2;
	
		pts_dst.push_back(Point2f(472,52));
		pts_dst.push_back(Point2f(472+H1.w,52));
		pts_dst.push_back(Point2f(472+H1.w,52+H1.h));
		pts_dst.push_back(Point2f(472,52+H1.h));
		
		H1.H = findHomography(pts_src,pts_dst);	
		warpPerspective(img_src, img_trans, H1.H, img_src.size());
		imshow("Projected Image", img_trans);
		k = waitKey(0);
	} while(k!='s'&&k!='S');
	imwrite(filename.substr(0,filename.rfind("."))+"Transformed.png",img_trans);
	Mat img_crop;
	img_trans(Rect(472,52,H1.w,H1.h)).copyTo(img_crop);
	imwrite(filename.substr(0,filename.rfind("."))+"Cropped.png",img_crop);
	imshow("Cropped Image", img_crop);
	waitKey(3000);
	destroyAllWindows();
	return H1;	
}
#endif
