cmake_minimum_required(VERSION 3.20)
project(Day_3)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\opencv\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Day_3 main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(Day_3 ${OpenCV_LIBS})

