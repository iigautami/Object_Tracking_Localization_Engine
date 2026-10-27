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

    void drawTrajectory(
        cv::Mat& frame,
        const TrackedObject& object
    );
};
