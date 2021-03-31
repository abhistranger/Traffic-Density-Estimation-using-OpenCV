#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include "task1.h"

using namespace cv;
using namespace std;

void queuedensity_dynamicdensity(String file){
	ofstream MyFile("out.txt");
	Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN();
    VideoCapture capture(file);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        return;
    }
    Mat frame, fgMask;
    imgHomography H1 = fun("empty1.png");
    for(int i=0; i<20; i++){
        pBackSub->apply(imread("empty1Cropped.png"), fgMask, 0.5);	
    }
    
    Mat frame0, frame0_gray;
    capture >> frame0;
	Mat frame0_crop =fun2(frame0,H1);
	cvtColor(frame0_crop, frame0_gray, COLOR_BGR2GRAY);
    Mat fr;
    capture>> fr;
    
    cout<<"framenum"<<"\t"<<"queue density"<<"\t"<<"dynamic density"<<"\n";
    MyFile <<"framenum"<<","<<"queue density"<<","<<"dynamic density"<<"\n";
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        //update the background model
        frame=fun2(frame,H1);
        pBackSub->apply(frame, fgMask,0.00001);
        //pBackSub->apply(frame, fgMask);
        //get the frame number and write it on the current frame
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //show the current frame and the fg masks
        threshold(fgMask,fgMask,127,255,THRESH_BINARY);
        //imshow("frame", frame);
        imshow("FG Mask", fgMask);
        
        
        //dynamic part
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        imshow("frame", frame_gray);
		//Mat frame_crop = fun3(frame_gray,H);
		
		Mat flow(frame0_gray.size(), CV_32FC2);
        calcOpticalFlowFarneback(frame0_gray, frame_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        // visualization
        Mat flow_parts[2];
        split(flow, flow_parts);
        Mat magnitude, angle, magn_norm;
        cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
        normalize(magnitude, magn_norm, 0.0f, 1.0f, NORM_MINMAX);
        angle *= ((1.f / 360.f) * (180.f / 255.f));
        threshold(magnitude,magnitude,10,255,THRESH_BINARY);

        //build hsv image
        Mat _hsv[3], hsv, hsv8, bgr;
        _hsv[0] = angle;
        _hsv[1] = Mat::ones(angle.size(), CV_32F);
        _hsv[2] = magn_norm;
        merge(_hsv, 3, hsv);
        hsv.convertTo(hsv8, CV_8U, 255.0);
        cvtColor(hsv8, bgr, COLOR_HSV2BGR);
        //imshow("ff",magn_norm);
        imshow("frame_gray", magnitude);
        //imshow("frame_hsv",bgr);
        frame0_gray=frame_gray;
        
        //print
        cout<<frameNumberString<<"\t\t"<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<"\t\t"<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        MyFile <<frameNumberString<<","<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<","<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        //get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 'Q')
            break;
    	capture >> frame;
    	capture >> frame;
    }
    MyFile.close();
    return;
}


int main(int argc, char* argv[]){
    queuedensity_dynamicdensity(argv[1]);
    return 0;
}





