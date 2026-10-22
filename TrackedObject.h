#pragma once

#include "BoundingBox.h"
#include <vector>
#include <string>

class TrackedObject
{
private:
    int id;

    BoundingBox boundingBox;

    cv::Point2f previousCentroid;
    cv::Point2f currentCentroid;

    std::vector<cv::Point2f> trajectory;

    double speed;

    std::string direction;
    std::string status;

    int missedFrames;

public:
    TrackedObject(int id, const BoundingBox& box);

    void update(const BoundingBox& newBox);

    int getID() const;

    BoundingBox getBoundingBox() const;

    cv::Point2f getCurrentCentroid() const;

    cv::Point2f getPreviousCentroid() const;

    double getSpeed() const;

    std::string getDirection() const;

    std::string getStatus() const;

    const std::vector<cv::Point2f>& getTrajectory() const;

    int getMissedFrames() const;

    void incrementMissedFrames();
    void resetMissedFrames();
};