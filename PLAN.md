PHASE 1: OOP Foundation
<br>
Create Point Class
<br>
Create BoundingBox Class with encapsulation
<br>
Create Frame Class<br>
Create abstract Detector base class<br>
Create MotionDetector derived class<br>
Create tracker interface/base class<br>
Implement virtual functions and polymorphism<br>

Create Frame Class
Create abstract Detector base class
Create MotionDetector derived class
Create tracker interface/base class
Implement virtual functions and polymorphism

Classes Used:

1. Frame Class: represents video frame and is reponsible for storing image, frame number and timestamp
2. BoundingBox Class: represents an objects location
3. TrackedObject Class: represents one object being tracked
4. MotionDetector Class: reponsible for finding moving regions
5. Tracker Class: responsiblities- receive detections->compare with existing objects->match objects->update existing IDs->create IDs for new objects->Handle temporarily missing objects->remove permanently lost objects.
6. MotionAnalyzer Class: reponsible for numerical analysis- position, displacement and speed
7. Visualizer Class: reponsible for everything drawn on the OpenCV windows
>>>>>>> 74bdbc5 (explained classes which will be used.)
