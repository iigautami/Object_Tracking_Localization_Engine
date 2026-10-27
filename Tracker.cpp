#include "Tracker.h"

#include <cmath>
#include <limits>

ObjectTracker::ObjectTracker(double maxDistance, int maxMissed)
{
    nextID = 1;
    maxMatchDistance = maxDistance;
    maxMissedFrames = maxMissed;
}
void ObjectTracker::update(const std::vector<BoundingBox>& detections, double timestamp){
    std::vector<bool> detectionUsed(detections.size(),false);
    // Match existing objects
    for (auto& pair : objects)
    {
        TrackedObject& object = pair.second;
        double closestDistance =std::numeric_limits<double>::max();
        int closestIndex = -1;
        for (int i = 0;i < detections.size(); i++){
            if (detectionUsed[i])
                continue;
            cv::Point2f objectCenter =object.getCurrentCentroid();
            cv::Point2f detectionCenter =detections[i].getCentroid();
            double dx = objectCenter.x - detectionCenter.x;
            double dy = objectCenter.y - detectionCenter.y;
            double distance = std::sqrt(dx * dx + dy * dy);
            if (distance < closestDistance){
                closestDistance = distance;
                closestIndex = i;
            }
        }
        if (closestIndex != -1 && closestDistance < maxMatchDistance){
            object.update(detections[closestIndex], timestamp);
            detectionUsed[closestIndex] = true;
        }
        else{
            object.incrementMissedFrames();
        }
    }
    // Create new objects
    for (int i = 0; i < detections.size();i++){
        if (!detectionUsed[i])
        {
            TrackedObject object(nextID, detections[i], timestamp);
            objects.emplace(nextID,object);
            nextID++;
        }
    }
    // Remove objects that have been missing too long
    for (auto it = objects.begin();
         it != objects.end();){
        if (it->second.getMissedFrames()> maxMissedFrames){
            it = objects.erase(it);
        }
        else{
            ++it;
        }
    }
}
std::map<int, TrackedObject>& ObjectTracker::getObjects(){
    return objects;
}
