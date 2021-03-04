# Virtual Painter
Virtual Painter using OpenCV with C++. This program virtually paints using webcam feed.

* Requirement: OpenCV needs to be installed in your PC.

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

