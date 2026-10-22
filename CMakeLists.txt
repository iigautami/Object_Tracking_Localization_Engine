cmake_minimum_required(VERSION 3.16)

project(ObjectTrackingEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
set(OpenCV_DIR "C:/opencv/build")

find_package(OpenCV REQUIRED)

# Source files
add_executable(ObjectTrackingEngine
    main.cpp
    Frame.cpp
    BoundingBox.cpp
    TrackedObject.cpp
    MotionDetector.cpp
    Tracker.cpp
    MotionAnalyzer.cpp
    Visualizer.cpp
)

# Include OpenCV headers
target_include_directories(ObjectTrackingEngine PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

# Link OpenCV libraries
target_link_libraries(ObjectTrackingEngine PRIVATE
    ${OpenCV_LIBS}
)