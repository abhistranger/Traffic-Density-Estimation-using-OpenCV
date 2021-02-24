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
./task1 image_name
```
For example:
```
./task1 empty.jpg
```

It will open the image empty.jpg in one window, which is converted in grayscale. You have to choose the four points in clockwise direction starting from top-left point. If you don't want to go further and want to end here you can press "e" or "E" to close this image window. So, If you choosed four points then after four points selection, it will open a new window with the projected image. Now there are two option, 
if u click "s" or "S" button on keyborad then it will open a new window with the cropped image and if you think you haven't chossen correct 4 point then press any button other than "s" or "S", it will open apain the original grayscaled image window and you can again process same as above.

# To help
```bash
make help
```
If you enter wrong command then the help menu will be opened.

Note: All the ouput images will be saved in the same directory.
