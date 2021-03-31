# Traffic-Density-Estimation-using-OpenCV

To run the program:
1. Put all files in one directry
2. open terminal in the current directory
# To Clean 
```bash
make clean
```
# To Compile
```bash
make
```
or
```bash
make all
```
# To Run Task 1 - Camera angle correction and frame cropping
```bash
./task1 <image_name>.jpg
```
For example:
```
./task1 empty.jpg
```
It will open the image <image_name>.jpg (grayscale) in one window. You have to choose the four points in clockwise direction starting from the top-left point. After the four points are selected, it will open a new window with the projected image. 
Now there are two option
1. If satisfied with the result Clicking "s" or "S" button on the keyborad will save the projected image as <image_name>Transformed.jpg and will open a new window with the cropped image which is then saved in the name of <image_name>Cropped.jpg.
2. In case you wish to reselect those 4 points then press any button other than 's' or 'S'. It will open the Original Grayscaled Image window again and you can again proceed same as above.

# To Run Task 2 - Queue and dynamic density estimation from traffic video
```bash
./task2 <video_name>.mp4
```
For example:
```
./task2 trafficvideo.mp4
```
It will firstly execute task1, asking the user to select four points on the image in a clock wise manner. Pressing 's' or 'S' on a satisfactory result of transformmed image, shall save the transformmed and cropped image in the same directory.
After waiting for 3 seconds, the windows displaying the Original Grayscale Image, Transformmed Image and Cropped Image are destroyed, and the execution of program for calculation of queue and dynamic density begins on the input video, processing every 3rd frame of the video.
At the time of execution, each frame being processed is displayed in "frame" window as a grayscale image, along with the frame number at top-left corner. Also corresponding frames for Queue Density and Dynamic Density calculations are shown in windows named "FG Mask" and "frame_gray" respectively. These frames mark the results of Background Subtraction for calculating queue density and Dense Optical Flow for calculating dynamic density respectively.
Queue Density and Dynamic Density as calculated is printed on the terminal with its corresponding frame number, and the same data is stored on a file, namely "out.txt" after successful execution of the program on the entire video.

# To help
```bash
make help
```
If you enter wrong command then the help menu will be opened.

*You can choose to exit the Original Grayscale Image window anytime by pressing 'e' or 'E' key on the keyboard.</br>
*You can choose to quit the execution of the program on the video anytime by pressing 'q' or 'Q' key on the keyboard.</br>
*All the ouput images and text files will be saved in the same directory.</br>

