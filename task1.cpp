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

int dist(int x1,int y1,int x2,int y2){
	return sqrt(pow(x2 - x1, 2)+pow(y2 - y1, 2));
}

int main(int argc, char* argv[]){
	string filename = argv[1];
	Mat img_src = imread(filename, IMREAD_GRAYSCALE);
	if(img_src.empty()){
		printf("Image is Empty!");
		exit(1);
	}
	vector<Point2f> pts_src;
	vector<Point2f> pts_dst;
	int k;
	int w,h;
	Mat img_trans;
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
				return 0;
			}
		}
		destroyAllWindows();
	
		w = dist(pts_src[0].x,pts_src[0].y,pts_src[1].x,pts_src[1].y);
		h = (dist(pts_src[0].x,pts_src[0].y,pts_src[3].x,pts_src[3].y)+dist(pts_src[2].x,pts_src[2].y,pts_src[1].x,pts_src[1].y))/2;
	
		pts_dst.push_back(Point2f(472,52));
		pts_dst.push_back(Point2f(472+w,52));
		pts_dst.push_back(Point2f(472+w,52+h));
		pts_dst.push_back(Point2f(472,52+h));
		
		Mat H = findHomography(pts_src,pts_dst);	
		warpPerspective(img_src, img_trans, H, img_src.size());
		imshow("Projected Image", img_trans);
		k = waitKey(0);
	} while(k!='s'&&k!='S');
	imwrite(filename.substr(0,filename.rfind("."))+"Transformed.jpg",img_trans);
	Mat img_crop;
	img_trans(Rect(472,52,w,h)).copyTo(img_crop);
	imwrite(filename.substr(0,filename.rfind("."))+"Cropped.jpg",img_crop);
	imshow("Cropped Image", img_crop);
	waitKey(0);
	return 0;
	
}

