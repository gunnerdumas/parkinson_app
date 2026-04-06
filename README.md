# Parkinsons Desktop Applcation
This is the desktop application for the 2026 senior design Parkinsons Team. This is also the final project for the ECE369 computer networks and will handle the FUOTA.

# Setup
The App uses [Qt](https://www.qt.io/) has both the networking and GUI. 

## Workspace
Everybody needs to setup a Github accout. When working on the project, make your own workspace with ```git checkout -b yourname_ws```. This is where you will be doing your work and helps us log whos doing what.

## Linux
Linux will be using VScode. Install CMake and Make along with the **Qt Extension Pack** VScode extension.

1. ```git clone git@github.com:gunnerdumas/parkinson_app.git```
2. Your directory should be as follows 
```
├── CMakeLists.txt
├── include
│   ├── filedownloader.h
│   └── mainwindow.h
├── README.md
└── src
    ├── filedownloader.cpp
    ├── main.cpp
    ├── mainwindow.cpp
    └── mainwindow.ui
```
3. ```mkdir build```
4. ```cd build```
5. ```cmake ..```
6. ```make```
7. ```./parkinson_app```

## Windows
Install the [Qt Creator Community Edition](https://www.qt.io/development/download). Its a standalone IDE and will be able to do everything the linux setup does.
1. ```git clone git@github.com:gunnerdumas/parkinson_app.git```
2. Open in Qt Creator


 
