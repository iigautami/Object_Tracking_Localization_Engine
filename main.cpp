#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <filesystem>

#include "Frame.h"
#include "BoundingBox.h"
#include "TrackedObject.h"
#include "MotionDetector.h"
#include "Tracker.h"
#include "MotionAnalyzer.h"
#include "Visualizer.h"

int main(int argc, char** argv)
{
    const std::filesystem::path videoPath = argc > 1
        ? std::filesystem::path(argv[1])
        : std::filesystem::path("Video.mp4");
    cv::VideoCapture video(videoPath.string());
    if (!video.isOpened())
    {
        std::cerr << "Could not open video: " << videoPath.string() << '\n';
        return -1;
    }
    MotionDetector detector(500);
    ObjectTracker tracker(80.0,5);
    MotionAnalyzer analyzer(2.0);
    Visualizer visualizer;
    int frameNumber = 0;
    const std::string windowName = "Object Tracking Engine";
    //constexpr- constant expression
    constexpr int maxDisplayWidth = 1280;
    constexpr int maxDisplayHeight = 720;
    bool displayWindowSized = false;
    cv::namedWindow(windowName, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);

    while (true){
        cv::Mat image;
        if (!video.read(image))
            break;
        if (image.empty())
            break;
        frameNumber++;
        // Create Frame object
        double timestamp = video.get(cv::CAP_PROP_POS_MSEC) / 1000.0;
        Frame frame(image,frameNumber,timestamp);
        // 1. Detect moving objects and returns list of boxes
        std::vector<BoundingBox> detections =detector.detect(frame);
        // 2. Updates the Tracked objects
        tracker.update(detections, timestamp);
        // 3. Analyze and visualize
        for (auto& pair : tracker.getObjects()){
            TrackedObject& object =pair.second;
            analyzer.analyze(object, object.getDeltaTime());
            visualizer.drawObject(image,object);
            visualizer.drawTrajectory(image,object);
            std::cout << "frame=" << frameNumber
                      << " id=" << object.getID()
                      << " x=" << object.getCurrentCentroid().x
                      << " y=" << object.getCurrentCentroid().y
                      << " speed_px_s=" << object.getSpeed()
                      << " direction=" << object.getDirection()
                      << " status=" << object.getStatus()
                      << " missed=" << object.getMissedFrames() << '\n';
        }
        // 4. Display
        const double displayScale = std::min({
            1.0,
            static_cast<double>(maxDisplayWidth) / image.cols,
            static_cast<double>(maxDisplayHeight) / image.rows
        });
        cv::Mat displayImage;
        if (displayScale < 1.0)
            cv::resize(image, displayImage, cv::Size(), displayScale, displayScale, cv::INTER_AREA);
        else
            displayImage = image;

        if (!displayWindowSized)
        {
            cv::resizeWindow(windowName, displayImage.cols, displayImage.rows);
            displayWindowSized = true;
        }
        cv::imshow(windowName, displayImage);
        // Press Q to quit
        if (cv::waitKey(1) == 'q')
            break;
    }
    video.release();
    cv::destroyAllWindows();
    return 0;
}
