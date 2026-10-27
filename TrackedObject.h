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
    double previousTimestamp;
    double currentTimestamp;

    std::string direction;
    std::string status;

    int missedFrames;

public:
    TrackedObject(int id, const BoundingBox& box, double timestamp = 0.0);

    void update(const BoundingBox& newBox, double timestamp = 0.0);
    void setMotion(double speed, const std::string& direction, const std::string& status);

    int getID() const;

    BoundingBox getBoundingBox() const;

    cv::Point2f getCurrentCentroid() const;

    cv::Point2f getPreviousCentroid() const;

    double getSpeed() const;
    double getDeltaTime() const;

    std::string getDirection() const;

    std::string getStatus() const;

    const std::vector<cv::Point2f>& getTrajectory() const;

    int getMissedFrames() const;

    void incrementMissedFrames();
    void resetMissedFrames();
};
