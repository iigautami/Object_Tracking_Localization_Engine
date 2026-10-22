#pragma once

#include "TrackedObject.h"

class MotionAnalyzer
{
private:
    double movementThreshold;

public:
    MotionAnalyzer(double threshold = 2.0);

    void analyze(
        TrackedObject& object,
        double deltaTime
    );
};