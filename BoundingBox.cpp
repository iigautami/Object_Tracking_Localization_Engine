#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

BoundingBox::BoundingBox(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int BoundingBox::getX() const
{
    return x;
}

int BoundingBox::getY() const
{
    return y;
}

int BoundingBox::getWidth() const
{
    return width;
}

int BoundingBox::getHeight() const
{
    return height;
}

cv::Point2f BoundingBox::getCentroid() const
{
    return cv::Point2f(
        x + width / 2.0f,
        y + height / 2.0f
    );
}

int BoundingBox::getArea() const
{
    return width * height;
}

cv::Rect BoundingBox::getRect() const
{
    return cv::Rect(x, y, width, height);
}
// Operator overloading: +
BoundingBox BoundingBox::operator+(const cv::Point2f& offset) const
{
    return BoundingBox(
        x + static_cast<int>(offset.x),
        y + static_cast<int>(offset.y),
        width,
        height
    );
}

// Operator overloading: -
BoundingBox BoundingBox::operator-(const cv::Point2f& offset) const
{
    return BoundingBox(
        x - static_cast<int>(offset.x),
        y - static_cast<int>(offset.y),
        width,
        height
    );
}