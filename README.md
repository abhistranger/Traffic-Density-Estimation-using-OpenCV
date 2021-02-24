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
# To Run
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
2.In case you wish to reselect those 4 points then press any button other than "s" or "S". It will open the Original Grayscaled Image window again and you can again proceed same as above.
*You can choose to exit the Original Grayscale Image window anytime by pressing "e" or"E" key on the keyboard.
*All the ouput images will be saved in the same directory.
