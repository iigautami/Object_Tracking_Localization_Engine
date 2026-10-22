#pragma once

#include <opencv2/opencv.hpp>

class BoundingBox
{
private:
    int x;
    int y;
    int width;
    int height;

public:
    BoundingBox();
    BoundingBox(int x, int y, int width, int height);

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

    cv::Point2f getCentroid() const;
    int getArea() const;

    cv::Rect getRect() const;

    // Operator overloading
    BoundingBox operator+(const cv::Point2f& offset) const;
    BoundingBox operator-(const cv::Point2f& offset) const;
};