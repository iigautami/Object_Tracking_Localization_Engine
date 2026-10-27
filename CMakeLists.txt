cmake_minimum_required(VERSION 3.16)

project(ObjectTrackingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT MSVC)
    message(FATAL_ERROR "This project must be built with MSVC to match the installed OpenCV binaries.")
endif()

set(OpenCV_DIR "C:/opencv/build" CACHE PATH "OpenCV package configuration directory")

find_package(OpenCV 5 REQUIRED COMPONENTS core geometry imgproc video videoio highgui)

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

# Make the installed OpenCV runtime DLLs available when launching from Visual Studio.
if(WIN32 AND OpenCV_LIB_PATH)
    get_filename_component(OPENCV_RUNTIME_DIR "${OpenCV_LIB_PATH}/../bin" ABSOLUTE)
    set_property(TARGET ObjectTrackingEngine PROPERTY VS_DEBUGGER_ENVIRONMENT
        "PATH=${OPENCV_RUNTIME_DIR};$ENV{PATH}")
    set_property(TARGET ObjectTrackingEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
        "${CMAKE_SOURCE_DIR}")
endif()
