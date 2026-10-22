#include <opencv2/opencv.hpp>
#include <iostream>

#include "Frame.h"
#include "BoundingBox.h"
#include "TrackedObject.h"
#include "MotionDetector.h"
#include "Tracker.h"
#include "MotionAnalyzer.h"
#include "Visualizer.h"

int main()
{
    cv::VideoCapture video("video.mp4");
    if (!video.isOpened())
    {
        std::cout << "Could not open video.\n";
        return -1;
    }
    MotionDetector detector(500);
    ObjectTracker tracker(80.0,5);
    MotionAnalyzer analyzer(2.0);
    Visualizer visualizer;
    int frameNumber = 0;
    while (true){
        cv::Mat image;
        if (!video.read(image))
            break;
        frameNumber++;
        // Create Frame object
        double timestamp = video.get(cv::CAP_PROP_POS_MSEC) / 1000.0;
        Frame frame(image,frameNumber,timestamp);
        // 1. Detect moving objects
        std::vector<BoundingBox> detections =detector.detect(frame);
        // 2. Track objects
        tracker.update(detections);
        // 3. Analyze and visualize
        for (auto& pair : tracker.getObjects()){
            TrackedObject& object =pair.second;
            analyzer.analyze(object,1.0 / 30.0);
            visualizer.drawObject(image,object);
            visualizer.drawTrajectory(image,object);
        }
        // 4. Draw statistics
        visualizer.drawStatistics(image,tracker.getObjects().size(),30.0);
        // 5. Display
        cv::imshow("Object Tracking Engine",image);
        // Press Q to quit
        if (cv::waitKey(1) == 'q')
            break;
    }
    video.release();
    cv::destroyAllWindows();
    return 0;
}