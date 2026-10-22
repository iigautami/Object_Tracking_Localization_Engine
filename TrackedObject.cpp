#include "TrackedObject.h"

TrackedObject::TrackedObject(int id, const BoundingBox& box)
{
    this->id = id;
    boundingBox = box;

    currentCentroid = box.getCentroid();
    previousCentroid = currentCentroid;

    trajectory.push_back(currentCentroid);

    speed = 0.0;
    direction = "STATIONARY";
    status = "STATIONARY";

    missedFrames = 0;
}

void TrackedObject::update(const BoundingBox& newBox)
{
    previousCentroid = currentCentroid;

    boundingBox = newBox;

    currentCentroid = newBox.getCentroid();

    trajectory.push_back(currentCentroid);

    missedFrames = 0;
}

int TrackedObject::getID() const
{
    return id;
}

BoundingBox TrackedObject::getBoundingBox() const
{
    return boundingBox;
}

cv::Point2f TrackedObject::getCurrentCentroid() const
{
    return currentCentroid;
}

cv::Point2f TrackedObject::getPreviousCentroid() const
{
    return previousCentroid;
}

double TrackedObject::getSpeed() const
{
    return speed;
}

std::string TrackedObject::getDirection() const
{
    return direction;
}

std::string TrackedObject::getStatus() const
{
    return status;
}

const std::vector<cv::Point2f>& TrackedObject::getTrajectory() const
{
    return trajectory;
}

int TrackedObject::getMissedFrames() const
{
    return missedFrames;
}

void TrackedObject::incrementMissedFrames()
{
    missedFrames++;
}

void TrackedObject::resetMissedFrames()
{
    missedFrames = 0;
}