#pragma once

#include <opencv2/opencv.hpp>

class Frame
{
private:
    cv::Mat image;
    int frameNumber;
    double timestamp;

public:
    Frame();

    Frame(const cv::Mat& img, int number, double time);

    cv::Mat getImage() const;

    int getFrameNumber() const;

    double getTimestamp() const;
};