#include "Frame.h"

Frame::Frame()
{
    frameNumber = 0;
    timestamp = 0.0;
}

Frame::Frame(const cv::Mat& img, int number, double time)
{
    image = img.clone();
    frameNumber = number;
    timestamp = time;
}

cv::Mat Frame::getImage() const
{
    return image;
}

int Frame::getFrameNumber() const
{
    return frameNumber;
}

double Frame::getTimestamp() const
{
    return timestamp;
}