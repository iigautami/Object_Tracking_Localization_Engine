cmake_minimum_required(VERSION 3.15)

project(Object_Tracking_Localization_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where OpenCV is installed
set(OpenCV_DIR "D:/opencv/build")

find_package(OpenCV REQUIRED)

add_executable(ObjectTracking main.cpp)

target_include_directories(ObjectTracking PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(ObjectTracking PRIVATE ${OpenCV_LIBS})