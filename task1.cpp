#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

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
	string filename="/home/abhistranger/cpp_files/COP290/Traffic_density_estimator/empty.jpg";
	Mat img = imread(filename, IMREAD_GRAYSCALE);
	if(img.empty()){
		exit(1);
	}
	vector<Point2f> pts_src;
	namedWindow("Original Greyscale Image", WINDOW_AUTOSIZE);
	setMouseCallback("Original Greyscale Image",click_event,&pts_src);
	while(pts_src.size()<4){
		imshow("Original Greyscale Image", img);
		waitKey(50);
	}
	
	/*for(int j=0;j<4;j++){
		cout<<pts_src[j].x<<" "<<pts_src[j].y<<endl;
	}*/
	
	vector<Point2f> pts_dst;
	
	/*int w = (dist(pts_src[0].x,pts_src[0].y,pts_src[1].x,pts_src[1].y)+dist(pts_src[2].x,pts_src[2].y,pts_src[3].x,pts_src[3].y))/2;
	int h = (dist(pts_src[0].x,pts_src[0].y,pts_src[3].x,pts_src[3].y)+dist(pts_src[2].x,pts_src[2].y,pts_src[1].x,pts_src[1].y))/2;
	
	pts_dst.push_back(Point2f(0,0));
	pts_dst.push_back(Point2f(0+w,0));
	pts_dst.push_back(Point2f(0+w,0+h));
	pts_dst.push_back(Point2f(0,0+h));*/
	
	
	pts_dst.push_back(Point2f(472,52));
	pts_dst.push_back(Point2f(800,52));
	pts_dst.push_back(Point2f(800,900));
	pts_dst.push_back(Point2f(472,900));
	
	
	Mat H = findHomography(pts_src,pts_dst);
	
	Mat img_p;
	warpPerspective(img, img_p, H, img.size());
	namedWindow("Projected Image", WINDOW_AUTOSIZE);
	imshow("Projected Image", img_p);
	waitKey();
	
	
}

