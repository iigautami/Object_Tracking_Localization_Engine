#pragma once

#include "TrackedObject.h"

#include <vector>
#include <map>

class ObjectTracker
{
private:
    std::map<int, TrackedObject> objects;

    int nextID;

    double maxMatchDistance;
    int maxMissedFrames;

public:
    ObjectTracker(
        double maxDistance = 80.0,
        int maxMissed = 5
    );

    void update(
        const std::vector<BoundingBox>& detections,
        double timestamp = 0.0
    );

    std::map<int, TrackedObject>& getObjects();
};
