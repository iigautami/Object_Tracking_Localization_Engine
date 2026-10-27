#include "Visualizer.h"
#include <algorithm>

void Visualizer::drawObject(
    cv::Mat& frame,
    const TrackedObject& object)
{
    BoundingBox box =
        object.getBoundingBox();

    cv::Rect rect = box.getRect();

    // Bounding box
    cv::rectangle(
        frame,
        rect,
        cv::Scalar(0, 255, 0),
        2
    );

    // Centroid
    cv::Point2f center =
        object.getCurrentCentroid();

    cv::circle(
        frame,
        center,
        4,
        cv::Scalar(0, 0, 255),
        -1
    );

    // Object information
    std::string text = "ID: " + std::to_string(object.getID()) +
        " " + object.getStatus() + " " + object.getDirection() +
        " " + std::to_string(static_cast<int>(object.getSpeed())) + " px/s";

    cv::putText(
        frame,
        text,
        cv::Point(
            box.getX(),
            std::max(15, box.getY() - 10)
        ),
        cv::FONT_HERSHEY_SIMPLEX,
        0.6,
        cv::Scalar(255, 255, 255),
        2
    );
}

void Visualizer::drawTrajectory(
    cv::Mat& frame,
    const TrackedObject& object)
{
    const auto& points =
        object.getTrajectory();

    for (size_t i = 1;
         i < points.size();
         i++)
    {
        cv::line(
            frame,
            points[i - 1],
            points[i],
            cv::Scalar(255, 0, 0),
            2
        );
    }
}

