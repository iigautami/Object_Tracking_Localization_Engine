#include "MotionAnalyzer.h"

#include <cmath>

MotionAnalyzer::MotionAnalyzer(double threshold)
{
    movementThreshold = threshold;
}

void MotionAnalyzer::analyze(
    TrackedObject& object,
    double deltaTime)
{
    cv::Point2f previous =
        object.getPreviousCentroid();

    cv::Point2f current =
        object.getCurrentCentroid();

    double dx = current.x - previous.x;
    double dy = current.y - previous.y;

    double distance =
        std::sqrt(dx * dx + dy * dy);

    double speed = 0.0;

    if (deltaTime <= 0.0)
        deltaTime = object.getDeltaTime();

    if (std::isfinite(deltaTime) && deltaTime > 0.0)
    {
        speed = distance / deltaTime;
    }

    // Direction
    std::string direction = "STATIONARY";

    if (std::abs(dx) > std::abs(dy))
    {
        if (dx > movementThreshold)
            direction = "RIGHT";
        else if (dx < -movementThreshold)
            direction = "LEFT";
    }
    else
    {
        if (dy > movementThreshold)
            direction = "DOWN";
        else if (dy < -movementThreshold)
            direction = "UP";
    }

    const std::string status = distance > movementThreshold && speed > 0.0
        ? "MOVING"
        : "STATIONARY";
    if (status == "STATIONARY")
        direction = "STATIONARY";
    object.setMotion(speed, direction, status);
}
