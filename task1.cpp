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
	Mat img_trans;
	do{
		pts_src.clear();
		pts_dst.clear();
		destroyAllWindows();
		namedWindow("Original Greyscale Image", WINDOW_AUTOSIZE);
		setMouseCallback("Original Greyscale Image",click_event,&pts_src);
		while(pts_src.size()<4){
			imshow("Original Greyscale Image", img_src);
			waitKey(50);
		}
		destroyAllWindows();
	
		pts_dst.push_back(Point2f(472,52));
		pts_dst.push_back(Point2f(472,900));
		pts_dst.push_back(Point2f(800,900));
		pts_dst.push_back(Point2f(800,52));
		
		Mat H = findHomography(pts_src,pts_dst);	
		warpPerspective(img_src, img_trans, H, img_src.size());
		imshow("Projected Image", img_trans);
		k = waitKey(0);
	} while(k!='s'&&k!='S');
	imwrite(filename.substr(0,filename.rfind("."))+"Transformed.jpg",img_trans);
	Mat img_crop;
	img_trans(Rect(472,52,328,848)).copyTo(img_crop); 
	imwrite(filename.substr(0,filename.rfind("."))+"Cropped.jpg",img_crop);
	imshow("Cropped Image", img_crop);
	waitKey(0);
	return 0;
	
}

