# Virtual Painter
Virtual Painter using OpenCV with C++. This program can detect & virtually paint Pink, Sky Blue & Dark Green color using webcam feed.

* Requirements: OpenCV needs to be installed in your PC. Webcam or some other device(e.g. SmartPhone) is needed for live video feed.

### How to run on Linux
* Using the makefile

1. open terminal in project directory
2. use the following command:

```
$ make
$ ./'Virtual Painter'
```
3. To clean the object files and build the project again from scratch use command  
```
$ make clean
```

* Without using makefile :
```
$ g++ filename.cpp -o filename `pkg-config --cflags --libs opencv4`
$ ./filename 
```
### How to run on Windows
```
$ g++ filename.cpp -o filename `pkg-config --cflags --libs opencv4`
$ filename or $ filename.exe
```

