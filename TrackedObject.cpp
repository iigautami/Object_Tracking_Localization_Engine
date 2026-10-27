#include "TrackedObject.h"

TrackedObject::TrackedObject(int id, const BoundingBox& box, double timestamp)
{
    this->id = id;
    boundingBox = box;

    currentCentroid = box.getCentroid();
    previousCentroid = currentCentroid;

    trajectory.push_back(currentCentroid);

    speed = 0.0;
    previousTimestamp = timestamp;
    currentTimestamp = timestamp;
    direction = "STATIONARY";
    status = "STATIONARY";

    missedFrames = 0;
}

void TrackedObject::update(const BoundingBox& newBox, double timestamp)
{
    previousCentroid = currentCentroid;
    previousTimestamp = currentTimestamp;
    currentTimestamp = timestamp;

    boundingBox = newBox;

    currentCentroid = newBox.getCentroid();

    trajectory.push_back(currentCentroid);

    missedFrames = 0;
}

void TrackedObject::setMotion(double newSpeed, const std::string& newDirection, const std::string& newStatus)
{
    speed = newSpeed;
    direction = newDirection;
    status = newStatus;
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

double TrackedObject::getDeltaTime() const
{
    return currentTimestamp - previousTimestamp;
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
