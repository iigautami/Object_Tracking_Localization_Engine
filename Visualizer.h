#pragma once

#include "TrackedObject.h"

#include <opencv2/opencv.hpp>
#include <map>

class Visualizer
{
public:

    void drawObject(
        cv::Mat& frame,
        const TrackedObject& object
    );

    void drawStatistics(
        cv::Mat& frame,
        int objectCount,
        double fps
    );

    void drawTrajectory(
        cv::Mat& frame,
        const TrackedObject& object
    );
};