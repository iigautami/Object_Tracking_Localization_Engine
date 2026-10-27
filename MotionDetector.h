#pragma once

#include "BoundingBox.h"
#include "Frame.h"
#include <opencv2/video/background_segm.hpp>
#include <vector>

class MotionDetector
{
private:
    cv::Ptr<cv::BackgroundSubtractor> backgroundSubtractor;
    int minimumArea;

public:
    MotionDetector(int minArea = 500);

    std::vector<BoundingBox> detect(const Frame& frame);
};
