#include "task1.h"
#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{   
    Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN();
    VideoCapture capture(argv[1]);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        return 0;
    }
    Mat frame, fgMask;
    imgHomography H1 = fun("empty1.png");
    for(int i=0; i<20; i++){
        pBackSub->apply(imread("empty1Cropped.png"), fgMask, 0.5);	
    }
    cout<<"Frame Number"<<"\t"<<"Queue Density (MAX 100)"<<"\t"<<"Dynamic Density (MAX 100)"<<"\n";
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        //update the background model
        frame=fun2(frame,H1);
        pBackSub->apply(frame, fgMask, 0.00001);
        //get the frame number and write it on the current frame
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //show the current frame and the fg masks
        threshold(fgMask,fgMask,254,255,THRESH_BINARY);
        cout<<frameNumberString<<"\t\t"<<double(countNonZero(fgMask))*100.00/double(fgMask.rows)/double(fgMask.cols)<<"\n";
        imshow("Frame", frame);
        imshow("FG Mask", fgMask);
        //get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    capture >> frame;
    capture >> frame;
    }
    return 0;
}
