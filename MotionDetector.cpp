#include "MotionDetector.h"
#include <opencv2/geometry.hpp>
#include <opencv2/imgproc.hpp>
MotionDetector::MotionDetector(int minArea)
{
    minimumArea = minArea;

    backgroundSubtractor = cv::createBackgroundSubtractorMOG2();
}

std::vector<BoundingBox>
MotionDetector::detect(const Frame& frame)
{
    std::vector<BoundingBox> detections;
    const cv::Mat image = frame.getImage();
    if (image.empty() || minimumArea <= 0 || backgroundSubtractor.empty())
        return detections;

    cv::Mat foregroundMask;
    backgroundSubtractor->apply(image, foregroundMask);
    // Remove noise
    cv::threshold(foregroundMask,foregroundMask,200,255,cv::THRESH_BINARY);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(5, 5));
    cv::morphologyEx(foregroundMask, foregroundMask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(foregroundMask, foregroundMask, cv::MORPH_CLOSE, kernel);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(foregroundMask,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : contours)
    {
        double area = cv::contourArea(contour);
        if (area < minimumArea)
            continue;
        cv::Rect rect = cv::boundingRect(contour);
        BoundingBox box(rect.x,rect.y,rect.width,rect.height);

        detections.push_back(box);
    }

    return detections;
}
