#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include "task1.h"

struct defined_structure{
	int NUM_OF_THREADS, THREAD_ID;
	string file_name;
	imgHomography H1;
	ofstream *MyFile;
};
void *queuedensity_dynamicdensity(void *object){
	defined_structure *obj = (defined_structure *)object;
	VideoCapture capture(obj->file_name);
	Ptr<BackgroundSubtractor> pBackSub;
    pBackSub = createBackgroundSubtractorKNN();
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        pthread_exit(NULL);
    }
    Mat frame, fgMask;
    
    for(int i=0; i<20; i++){
        pBackSub->apply(imread("empty1Cropped.png"), fgMask, 0.5);	
    }
    
    Mat frame0, frame0_gray;

	if(obj->THREAD_ID==0){
    		capture >> frame0;
    	}
    for(int i=0; i<obj->THREAD_ID; i++){
    	capture>>frame;
    	capture>>frame;
    	if(i==obj->THREAD_ID-1){
    		capture >> frame0;
    	}
    	capture>>frame;
    }
    Mat frame0_crop =fun2(frame0,obj->H1);
	cvtColor(frame0_crop, frame0_gray, COLOR_BGR2GRAY);
    Mat fr;
    capture>> fr;
    capture>>frame;
    
    while (true) {
        if (frame.empty())
            break;
        //update the background model
        frame=fun2(frame,obj->H1);
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
        
        
        //dynamic part
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
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
        frame0_gray=frame_gray;
        
        //print
        cout<<frameNumberString<<"\t\t"<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<"\t\t"<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        *(obj->MyFile) <<frameNumberString<<","<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<","<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        for(int i=0; i<obj->NUM_OF_THREADS; i++){
    		if(i==obj->NUM_OF_THREADS-1){
    			frame=fun2(frame,obj->H1);
    			Mat temp_frame = frame;
    			Mat temp2_frame;
    			cvtColor(temp_frame, temp2_frame, COLOR_BGR2GRAY);
    			frame0_gray = temp2_frame;
    		}
    		capture>>frame;
    		capture>>frame;
    		capture>>frame;
    	}
    }
    pthread_exit(NULL);
}
void method4 (String file, int NUM_OF_THREADS){
    string out_file_name="out_method4_NUM_THREADS_"+to_string(NUM_OF_THREADS)+".txt";
	ofstream MyFile(out_file_name);
    imgHomography H1 = fun("empty1.png");
    cout<<"framenum"<<"\t"<<"queue density"<<"\t"<<"dynamic density"<<"\n";
    MyFile <<"framenum"<<","<<"queue density"<<","<<"dynamic density"<<"\n";
	pthread_t threads[NUM_OF_THREADS];
    	defined_structure my_structure[NUM_OF_THREADS];
    	int i;
    	int rc;
	for( i = 0; i < NUM_OF_THREADS; i++ ) {
	
	my_structure[i].NUM_OF_THREADS = NUM_OF_THREADS;
    	my_structure[i].file_name = file;
	my_structure[i].THREAD_ID = i;
	my_structure[i].H1 = H1;
	my_structure[i].MyFile = &MyFile;
	rc = pthread_create(&threads[i], NULL, queuedensity_dynamicdensity, (void *)&my_structure[i]);
	if(rc){
		cout<<"Error: Thread Could Not Be Created";
		exit(0);
	}
	}
	for( i = 0; i < NUM_OF_THREADS; i++ ) {
		pthread_join(threads[i], NULL);
	}
	MyFile.close();
}
struct process_frame_structure{
	Mat frame, frame0_gray;
	stringstream ss;
	double queue_density, dynamic_density;
	int width, height, pos;
};
void *process_frame (void *process_frame_structure_object){
	process_frame_structure * my_structure = (process_frame_structure *)process_frame_structure_object;
	Ptr<BackgroundSubtractor> pBackSub;
	pBackSub = createBackgroundSubtractorKNN();
	Mat frame = my_structure->frame;
	Mat fgMask;
	for(int i=0; i<20; i++){
		pBackSub->apply(imread("empty1Cropped.png")(Rect(0,my_structure->pos,my_structure->width,my_structure->height)), fgMask, 0.5);
	}
        pBackSub->apply(frame, fgMask,0.00001);
        //pBackSub->apply(frame, fgMask);
        //get the frame number and write it on the current frame
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        string frameNumberString = my_structure->ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        threshold(fgMask,fgMask,127,255,THRESH_BINARY);
         //dynamic part
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        		
		Mat flow(my_structure->frame0_gray.size(), CV_32FC2);
        calcOpticalFlowFarneback(my_structure->frame0_gray, frame_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
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
        my_structure->frame0_gray=frame_gray;
        
	//print
        my_structure->queue_density = double(countNonZero(fgMask));
        my_structure->dynamic_density = double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols);
        pthread_exit(NULL);
}
void method3 (String file, int NUM_OF_THREADS){
	string out_file_name="out_method3_NUM_THREADS_"+to_string(NUM_OF_THREADS)+".txt";
	ofstream MyFile(out_file_name);
	Ptr<BackgroundSubtractor> pBackSub;
    VideoCapture capture(file);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        return;
    }
    Mat frame, fgMask;
    imgHomography H1 = fun("empty1.png");
    
    Mat frame0, frame0_gray;
    capture >> frame0;
	Mat frame0_crop =fun2(frame0,H1);
	cvtColor(frame0_crop, frame0_gray, COLOR_BGR2GRAY);
    Mat fr;
    capture>> fr;
    
    cout<<"framenum"<<"\t"<<"queue density"<<"\t"<<"dynamic density"<<"\n";
    MyFile <<"framenum"<<","<<"queue density"<<","<<"dynamic density"<<"\n";
    Mat frames[NUM_OF_THREADS];
    fr=fun2(fr,H1);
    int width, height;
        width  = fr.size().width;
        height  = fr.size().height;
        int temp_height = 0;
    for (int i=0; i<NUM_OF_THREADS; i++){
    	frames[i]=frame0_gray(Rect(0,temp_height,width,height/NUM_OF_THREADS));
    	temp_height+=height/NUM_OF_THREADS;
    }
    while(true){
	pthread_t threads[NUM_OF_THREADS];
    	process_frame_structure my_structure[NUM_OF_THREADS];
    	int i;
    	int rc;
    	capture >> frame;
    	if (frame.empty())
            exit(0);
            //update the background model
        frame=fun2(frame,H1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        int width, height;
        width  = frame.size().width;
        height  = frame.size().height;
        int temp_height = 0;
	for( i = 0; i < NUM_OF_THREADS; i++ ) {

	
	my_structure[i].frame = frame(Rect(0,temp_height,width,height/NUM_OF_THREADS));
	my_structure[i].pos = temp_height;
	my_structure[i].width = width;
	my_structure[i].height = height/NUM_OF_THREADS;
	my_structure[i].frame0_gray = frames[i];
	temp_height+=height/NUM_OF_THREADS;
	my_structure[i].ss <<capture.get(CAP_PROP_POS_FRAMES);
	rc = pthread_create(&threads[i], NULL, process_frame, (void *)&my_structure[i]);
	if(rc){
		cout<<"Error: Thread Could Not Be Created";
		exit(0);
	}
	}
	double queue_density = 0.0;
	double dynamic_density = 0.0;
	for( i = 0; i < NUM_OF_THREADS; i++ ) {
		frames[i] = my_structure[i].frame0_gray;
		pthread_join(threads[i], NULL);
		queue_density += my_structure[i].queue_density; 
		dynamic_density += my_structure[i].dynamic_density;
	}
	cout<<frameNumberString<<"\t\t"<<queue_density/double(frame.rows)/double(frame.cols)<<"\t\t"<<dynamic_density/(double)NUM_OF_THREADS<<"\n";
	MyFile<<frameNumberString<<","<<queue_density/double(frame.rows)/double(frame.cols)<<","<<dynamic_density/(double)NUM_OF_THREADS<<"\n";
    	capture >> frame;
    	capture >> frame;
    }
    return;


}

void method1(String file, int x){
	string out_file_name="out_method1_x_"+to_string(x)+".txt";
	ofstream MyFile(out_file_name);
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
        for(int j=0;j<x-1;j++){
        	cout<<stoi(frameNumberString)+(3*(j+1))<<"\t\t"<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<"\t\t"<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        	MyFile <<stoi(frameNumberString)+(3*(j+1))<<","<<double(countNonZero(fgMask))/double(fgMask.rows)/double(fgMask.cols)<<","<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        	capture >> frame;
			capture >> frame;
			capture >> frame;
        }
        //get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    	capture >> frame;
    	capture >> frame;
    }
    MyFile.close();
    return;
}

void method2(String file, int X, int Y){
	string out_file_name="out_method1_XxY_"+to_string(X)+"x"+to_string(Y)+".txt";
	ofstream MyFile(out_file_name);
	Ptr<BackgroundSubtractor> pBackSub;
	pBackSub = createBackgroundSubtractorKNN();
    VideoCapture capture(file);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        return;
    }
    
    //capture.set(CAP_PROP_FRAME_WIDTH,X);
	//capture.set(CAP_PROP_FRAME_HEIGHT,Y);
    
    Mat frame, fgMask;
    imgHomography H1 = fun("empty1.png");
    Mat temp_img=imread("empty1Cropped.png");
    
    resize(temp_img, temp_img, Size(X, Y), 0, 0, INTER_CUBIC);
    
    imshow("Temp Image", temp_img);
    for(int i=0; i<20; i++){
    	//cout<<1<<endl;
        pBackSub->apply(temp_img, fgMask, 0.5);	
    }
    
    Mat frame0, frame0_gray;
    capture >> frame0;
	Mat frame0_crop =fun2(frame0,H1);
	cvtColor(frame0_crop, frame0_gray, COLOR_BGR2GRAY);
	resize(frame0_gray, frame0_gray, Size(X, Y), 0, 0, INTER_CUBIC);
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
        resize(frame, frame, Size(X, Y), 0, 0, INTER_CUBIC);
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
        //resize(frame_gray, frame_gray, Size(X, Y), 0, 0, INTER_CUBIC);
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
        if (keyboard == 'q' || keyboard == 27)
            break;
    	capture >> frame;
    	capture >> frame;
    }
    MyFile.close();
    return;
}

void method_extra(String file){
	ofstream MyFile("out_method_sparse_vs_dense.txt");
    VideoCapture capture(file);
    if (!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video "<< endl;
        return;
    }
    Mat frame;
    Mat frame0, frame0_gray;
    capture >> frame0;
    imgHomography H1 = fun("empty1.png");
	Mat frame0_crop =fun2(frame0,H1);
	cvtColor(frame0_crop, frame0_gray, COLOR_BGR2GRAY);
    Mat fr;
    capture>> fr;
    
    //sparse
    vector<Scalar> colors;
    RNG rng;
    for(int i = 0; i < 100; i++){
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(Scalar(r,g,b));
    }
	vector<Point2f> p0, p1;
	goodFeaturesToTrack(frame0_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
	Mat mask = Mat::zeros(frame0_crop.size(), frame0_crop.type());
    
    
    cout<<"framenum"<<"\t"<<"sparse queue density"<<"\t"<<"dense dynamic density"<<"\n";
    MyFile <<"framenum"<<","<<"sparse queue density"<<","<<"dense dynamic density"<<"\n";
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        frame=fun2(frame,H1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        
        
        //grayscaling
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        imshow("frame", frame_gray);
        
        //sparse dynamic part
		vector<uchar> status;
    	vector<float> err;
    	TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
    	calcOpticalFlowPyrLK(frame0_gray, frame_gray, p0, p1, status, err, Size(15,15), 2, criteria);
    	vector<Point2f> good_new;
    	
    	// Visualization part
    	for(uint i = 0; i < p0.size(); i++){
        // Select good points
        	if(status[i] == 1) {
        		good_new.push_back(p1[i]);
    			// Draw the tracks
      			line(mask,p1[i], p0[i], colors[i], 2);
            	circle(frame, p1[i], 5, colors[i], -1);
			}
 		}
 		
 		Mat img_sp;
    	add(frame, mask, img_sp);
    	imshow("flow", img_sp);


		//dense dynamic part
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
        
        p0=good_new;
        goodFeaturesToTrack(frame0_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
        mask = Mat::zeros(frame.size(), frame.type());
        
        //print
        cout<<frameNumberString<<"\t\t"<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        MyFile <<frameNumberString<<","<<double(countNonZero(magnitude))/double(magnitude.rows)/double(magnitude.cols)<<"\n";
        //get the input from the keyboard
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    	capture >> frame;
    	capture >> frame;
    }
    MyFile.close();
    return;
}

int main(int argc, char* argv[]){
	method1(argv[1],stoi(argv[2]));
	//method2(argv[1],stoi(argv[2]),stoi(argv[3));
	//method3(argv[1], stoi(argv[2]));
	//method4(argv[1], stoi(argv[2]));
	//method_extra(argv[1]);
	return 0;
}

