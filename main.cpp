#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;

class Frame{
//responsible for storing image, frame number and timestamp
};

class BoundingBox{
//reprents an objects locatoin
};

class TrackedObjects{
//represents one object being tracked
};

class MotionDetector{
//responsible for finding moving regions
};

class Tracker{
//responsiblities- receive detections->compare with existing objects->match objects->update existing IDs->create IDs for new objects->Handle temporarily missing objects->remove permanently lost objects
};

class MotionAnalyzer{
//reponsible for numerical analysis- position, displacement and speed
};

class Visualizer{
//reponsible for everything drawn on the OpenCV windows
};